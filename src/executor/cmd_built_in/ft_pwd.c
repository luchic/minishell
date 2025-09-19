
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"


int	ft_pwd(t_command *cmd)
{
	char	cwd[1024];
	char	*info;

	info = getcwd(cwd, sizeof(cwd));
	if (!info)
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	// cmd->fd_out = STDOUT_FILENO;  // should use the stored fd_out
	ft_printf_fd(cmd->fd_out, "%s\n", cwd);
	return (EXIT_SUCCESS);
}

/* int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	main(void)
{
	t_command	cmd;

	cmd.type = CMD_BUILTIN;
	cmd.fd_in = -1;
	cmd.fd_out = STDOUT_FILENO;
	cmd.name = "pwd";
	cmd.args = (char *[]){"pwd", NULL};
	return (ft_pwd(&cmd));
}
 */
