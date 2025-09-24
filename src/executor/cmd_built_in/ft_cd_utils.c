
#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

int	ft_cd_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_printf_fd(STDERR, "cd: HOME not set\n");
		return (1);
	}
	if (chdir(home) != 0)
	{
		ft_printf_fd(STDERR, "cd: %s: No such file or directory\n", home);
		return (1);
	}
	return (0);
}

int	ft_cd_oldpwd(char *oldpwd, char *pwd)
{
	if (!oldpwd)
	{
		ft_printf_fd(STDERR, "cd: OLDPWD not set\n");
		return (1);
	}
	if (chdir(oldpwd) != 0)
	{
		ft_printf_fd(STDERR, "cd: %s: No such file or directory\n", oldpwd);
		return (1);
	}
	pwd = getenv("PWD");
	if (pwd)
		ft_printf_fd(STDOUT, "%s", pwd);
	ft_printf_fd(STDOUT, "\n");
	return (0);
}

int	ft_cd_to_path(char *path)
{
	if (chdir(path) != 0)
	{
		ft_printf_fd(STDERR, "cd: %s: No such file or directory\n", path);
		return (1);
	}
	return (0);
}