#include "../minishell.h"

void	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, 1024))
		printf("%s\n", cwd);
}
