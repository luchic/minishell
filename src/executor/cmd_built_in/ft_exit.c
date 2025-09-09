
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

/*
 * exit [n]
 * Exit the shell with a status of N. If N is omitted, the exit status
 * is that of the last command executed.
 * If N is not a numeric argument, the exit status is 255.
 * If there are more than one arguments, the exit status is 1.
 */

static int	check_exit(char **args)
{
	int	exit_code;
	int	i;

	if (count_args(args) > 2)
	{
		ft_printf_fd(STDERR, "exit: too many arguments\n");
		return (1);
	}
	i = 0;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]) && !(i == 0 && (args[1][i] == '-' || args[1][i] == '+')))
		{
			ft_printf_fd(STDERR, "exit: numeric argument required\n");
			exit(255);;
		}
		i++;
	}
	exit_code = ft_atoi(args[1]);
	if (exit_code < 0 || exit_code > 255)
		return (0);
	return (1);
}


int	ft_exit(t_command *cmd)
{
	int	status;
	int	i;
	char	**arg;

	ft_printf_fd(cmd->fd_out, "exit\n");
	arg = cmd->args;

	if (count_args(arg) == 1)
		exit(cmd->mnsh->last_exit_status);
	if (!check_exit(arg))
		exit(255);
	status = ft_atoi(arg[1]);
	exit(status);

	return (0);
}
