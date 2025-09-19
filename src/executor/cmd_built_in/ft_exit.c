
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

static int is_numeric_str(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit(t_command *cmd)
{
	int	status;
	int	argc;

	ft_printf_fd(cmd->fd_out, "exit\n");
	argc = count_args(cmd->args);

	if (argc == 1)
		exit(cmd->mnsh->last_exit_status);
	if (!is_numeric_str(cmd->args[1]))
	{
		ft_printf_fd(STDERR, " numeric argument required\n", cmd->args[1]); // bash: "exit: %s: numeric argument required\n"
		exit(2);
	}
	if (argc > 2)
	{
		ft_printf_fd(STDERR, "exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	status = ft_atoi(cmd->args[1]);
	// ft_printf_fd(cmd->fd_out, "Exiting with code %u\n", (unsigned char)status); ///to delete --- IGNORE ---
	exit((unsigned char)status);

	return (EXIT_SUCCESS);
}
