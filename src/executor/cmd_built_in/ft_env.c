
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

int	ft_env(t_command *cmd)
{
	int		i;

	if (cmd->args[1])
	{
		ft_printf_fd(STDERR, "env: '%s' No such file or directory\n", cmd->args[1]);
		return (127);
	}
	i = 0;
	while (cmd->mnsh->envp && cmd->mnsh->envp[i])
	{
		if (ft_strchr(cmd->mnsh->envp[i], '='))
		{
			ft_printf_fd(STDOUT, "%s\n", cmd->mnsh->envp[i]);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
