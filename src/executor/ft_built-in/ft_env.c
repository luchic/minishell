
#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"

int	ft_env(t_command cmd)
{
	int		i;

	if (cmd.args[1])
	{
		ft_putstr_fd("env: too many arguments\n", STDERR);
		return (1);
	}
	i = 0;
	while (cmd.mnsh->envp && cmd.mnsh->envp[i])
	{
		if (ft_strchr(cmd.mnsh->envp[i], '='))
		{
			ft_putstr_fd(cmd.mnsh->envp[i], STDOUT);
			ft_putstr_fd("\n", STDOUT);
		}
		i++;
	}
	return (0);
}
