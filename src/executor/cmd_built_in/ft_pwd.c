
#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"


int	ft_pwd(t_command *cmd)
{
	char	cwd[1024];
	char	*info;

	info = getcwd(cwd, sizeof(cwd));
	if (!info)
	{
		perror("pwd");
		return (1);
	}
	// cmd->fd_out = STDOUT_FILENO;  // should use the stored fd_out
	ft_putstr_fd(cwd, cmd->fd_out);
	ft_putstr_fd("\n", cmd->fd_out);
	return (0);
}

/* int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putstr_fd(char *s, int fd)
{
	int	res;

	res = 0;
	if (!s)
		return (-1);
	while (*s)
	{
		if (ft_putchar_fd(*s++, fd) == -1)
			return (-1);
		res++;
	}
	return (res);
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
