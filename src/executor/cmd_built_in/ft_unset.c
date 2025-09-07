
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

int ft_unset(t_command *cmd)
{
	int i;
	char	**args;
	char	**envp;

	if (count_args(cmd->args) < 2)
		return (0);
	args = cmd->args;
	envp = cmd->mnsh->envp;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i])) // simply return (1) if not found
		{
			return (1);
			// ft_putstr_fd("unset: `", 2);
			// ft_putstr_fd(args[i], 2);
			// ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
		{
			ft_array_remove(&envp, args[i]);
			cmd->mnsh->envp = envp; // update envp in mnsh
		}
		i++;
	}
	return (0);
}
