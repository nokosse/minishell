/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:00:28 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/30 16:59:49 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void handle_redirections(t_cmd *cmd) 
{
	for (t_lex *redir = cmd->redir; redir != NULL; redir = redir->next) {
		int fd;
		switch (redir->token) {
			case LEFT1: // <
				fd = open(redir->word, O_RDONLY);
				if (fd == -1) {
					perror("open");
					exit(EXIT_FAILURE);
				}
				dup2(fd, STDIN_FILENO);
				close(fd);
				break;
			case RIGHT1: // >
				fd = open(redir->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd == -1) {
					perror("open");
					exit(EXIT_FAILURE);
				}
				dup2(fd, STDOUT_FILENO);
				close(fd);
				break;
			case LEFT2: // <<
				{
					int pipe_fds[2];
					if (pipe(pipe_fds) == -1) {
						perror("pipe");
						exit(EXIT_FAILURE);
					}

					// Processus enfant pour écrire dans le pipe
					pid_t pid = fork();
					if (pid == -1) {
						perror("fork");
						exit(EXIT_FAILURE);
					} else if (pid == 0) {
						close(pipe_fds[0]); // Fermer l'extrémité de lecture
						char *line;
						while ((line = readline("> ")) != NULL) {
							if (strcmp(line, redir->word) == 0) {
								free(line);
								break;
							}
							write(pipe_fds[1], line, strlen(line));
							write(pipe_fds[1], "\n", 1);
							free(line);
						}
						close(pipe_fds[1]);
						exit(EXIT_SUCCESS);
					} else {
						close(pipe_fds[1]); // Fermer l'extrémité d'écriture
						dup2(pipe_fds[0], STDIN_FILENO);
						close(pipe_fds[0]);
						waitpid(pid, NULL, 0); // Attendre que le processus enfant termine
					}
				}
				break;
			// <<
			case RIGHT2: // >>
				fd = open(redir->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd == -1) {
					perror("open");
					exit(EXIT_FAILURE);
				}
				dup2(fd, STDOUT_FILENO);
				close(fd);
				break;

			// Ajoutez un cas pour chaque type de token non traité pour éviter les erreurs
			case WORD:
			case PIPE:
			case DQUOTE:
				// Pas d'action nécessaire pour ces cas
				break;
			default:
				// Vous pouvez gérer une erreur inattendue ici
				break;
		}
	}
}


// Exécute une commande individuelle.
int	exec_cmd( t_mini *shell, t_cmd *cmd)
{
	int		i;
	int		j;
	int		k;
	char	*ret;
	char	**f;

	handle_redirections(cmd);
	j = 0;
	i = -1;
	f =  cmd->cmd;//ft_split(cmd->str, ' ');
	f[0] = ft_strjoin("/",f[0]);
	while (shell->env[++i] != NULL && shell->env)
	{
		ret = ft_substr(shell->env[i], 0, 5);
		if (ft_same_str(ret, "PATH=", 5) == 1)
		{
			j = 5;

			while (shell->env[i][j] && shell->env[i][++j] != '\0' && shell->env)
			{
				k = j;
				while (shell->env[i][j] != ':' && shell->env[i][j] && shell->env)
					j++;
				ret = ft_strjoin_free1(ft_substr(shell->env[i], k, ((j) - k)), f[0]);

				if (shell->env[i][j] == ':')
					if (access(ret, F_OK) == 0)
						execve(ret, f, shell->env);

			}
		}
	}
	return 0;
}

char	*ft_strjoin_free1(char const *s1, char const *s2)
{
	char	*dest;
	size_t	len;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	len = (ft_strlen(s1) + ft_strlen(s2));
	dest = malloc(len + 1 * sizeof(char));
	if (!dest)
		return (NULL);
	while (s1 && s1[i] && dest)
		dest[k++] = s1[i++];
	while (s2 && s2[j] && dest)
		dest[k++] = s2[j++];
	dest[k] = '\0';
	free((void *)s1);
	return (dest);
}

int	ft_same_str(char *str1, char *str2, size_t n)
{
	int	i;

	i = -1;
	while ((++i < (int)n) && str1 && str2)
	{
		if (str1[i] != str2[i])
		{
			free(str1);
			return (0);
		}
	}
	free(str1);
	return (1);
}

int	init_pipes(t_mini *shell, int *pipe_fds)
{
	int		i;

	i = 0;
	while (i < shell->nb_pipes)
	{
		if (pipe(pipe_fds + i * 2) < 0)
		{
			perror("pipe");
			return (0);
		}
		i++;
	}
	return (1);
}

int executor(t_mini *shell)
{
	int pipe_fds[2 * shell->nb_pipes];
	int i = 0;
	pid_t pid;

	// Initialisation des pipes si nécessaire
	if (shell->nb_pipes > 0)
	{
		if (!init_pipes(shell, pipe_fds))
			return (0);
	}

	t_cmd *current_cmd = shell->cmd;
	i = 0;
	while (current_cmd != NULL) {
			pid = fork();
			if (pid == -1) {
				perror("fork");
				exit(EXIT_FAILURE);
			} else if (pid == 0) { // Processus enfant
				if (i != 0) { // Si ce n'est pas la première commande
					dup2(pipe_fds[(i - 1) * 2], STDIN_FILENO);
				}
				if (i < shell->nb_pipes * 2) { // Si ce n'est pas la dernière commande
					dup2(pipe_fds[i * 2 + 1], STDOUT_FILENO);
				}

				// Fermeture des descripteurs de fichier de pipe dans le processus enfant
				for (int j = 0; j < 2 * shell->nb_pipes; j++) {
					close(pipe_fds[j]);
				}

				exec_cmd(shell, current_cmd);
				exit(EXIT_FAILURE); // Si exec_cmd retourne
			}

			current_cmd = current_cmd->next;
			i++;
	}
	// Fermeture des descripteurs de fichier de pipe dans le processus parent
	for (i = 0; i < 2 * shell->nb_pipes; i++) {
		close(pipe_fds[i]);
	}
	// Attente des processus enfants
	while ((pid = wait(NULL)) > 0);

	return 1;
}
