/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:33:42 by kvisouth          #+#    #+#             */
/*   Updated: 2023/07/10 15:25:33 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_commands(t_cmd **cmd)
{
	int		count;
	t_cmd	*tmp;

	count = 0;
	tmp = *cmd;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	create_pipes(int pipes[][2], int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(1);
		}
		i++;
	}
}

void	close_unused_pipes(int pipes[][2], int current_pipe, int num_pipes)
{
	int	j;

	j = 0;
	while (j < num_pipes)
	{
		if (j != current_pipe)
		{
			close(pipes[j][0]);
			close(pipes[j][1]);
		}
		j++;
	}
}

// Norm error only on line:63
void	handle_child_process(t_cmd *cmd, int pipes[][2], int pipe_index, int num_pipes, char ***env)
{
	if (pipe_index != 0)
	{
		if (dup2(pipes[pipe_index - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
	if (pipe_index != num_pipes - 1)
	{
		if (dup2(pipes[pipe_index][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
	close_unused_pipes(pipes, num_pipes, pipe_index);
	exec_cmd(&cmd, env);
	exit(1);
}

void	handle_parent_process(int pipes[][2], int pipe_index, int num_pipes)
{
	if (pipe_index != 0)
		close(pipes[pipe_index - 1][0]);
	if (pipe_index != num_pipes - 1)
		close(pipes[pipe_index][1]);
}

void	close_remaining_pipes(int pipes[][2], int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	wait_for_children(int *status)
{
	while (wait(status) > 0)
		;
}

void	exec_pipe(t_cmd **cmd, char ***env)
{
	int	num_cmds = count_commands(cmd);
	int	pipes[num_cmds - 1][2];
	create_pipes(pipes, num_cmds - 1);

	int i = 0;
	t_cmd *tmp = *cmd;
	pid_t pid;
	int status;

	while (tmp)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
			handle_child_process(tmp, pipes, i, num_cmds, env);
		else
		{
			handle_parent_process(pipes, i, num_cmds);
			i++;
			tmp = tmp->next;
		}
	}
	close_remaining_pipes(pipes, num_cmds - 1);
	wait_for_children(&status);
}