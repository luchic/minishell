
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

int ft_unset(t_command *cmd)
{
	int i;
	int status;
	char	**envp;

	if (count_args(cmd->args) < 2)
		return (EXIT_FAILURE);
	envp = cmd->mnsh->envp;
	i = 1;
	status = EXIT_SUCCESS;
	while (cmd->args[i])
	{
		if (!is_valid_identifier(cmd->args[i]))
		{
			//ft_printf_fd(STDERR, "unset: `%s': not a valid identifier\n", cmd->args[i]); // seems not printing
			status = EXIT_FAILURE;
		}
		else
		{
			ft_array_remove(&envp, cmd->args[i]);
			//cmd->mnsh->envp = envp;
		}
		i++;
	}
	return (status);
}
