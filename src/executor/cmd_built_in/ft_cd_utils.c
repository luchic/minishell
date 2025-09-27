/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:43:20 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/27 20:27:12 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

int	ft_cd_home(void)
{
	char	*home;

	home = get_env("HOME");
	if (!home)
	{
		ft_printf_fd(STDERR, "cd: HOME not set\n");
		return (1);
	}
	if (chdir(home) != 0)
	{
		ft_printf_fd(STDERR, "cd: %s: No such file or directory\n", home);
		free(home);
		return (1);
	}
	free(home);
	return (0);
}

int	ft_cd_oldpwd(void)
{
	char	*oldpwd_env;

	oldpwd_env = get_env("OLDPWD");
	if (!oldpwd_env)
	{
		ft_printf_fd(STDERR, "cd: OLDPWD not set\n");
		ft_log_fd(LOG_ERROR, STDERR, "OLDPWD not set in environment\n");
		return (EXIT_FAILURE);
	}
	ft_log_fd(LOG_DEBUG, STDERR, "OLDPWD from env: %s\n", oldpwd_env);
	if (chdir(oldpwd_env) != 0)
	{
		ft_printf_fd(STDERR, "cd: %s: No such file or directory\n", oldpwd_env);
		free(oldpwd_env);
		return (EXIT_FAILURE);
	}
	ft_printf_fd(STDOUT, "%s\n", oldpwd_env);
	free(oldpwd_env);
	return (EXIT_SUCCESS);
}

int	ft_cd_to_path(char *path)
{
	if (path && path[ft_strlen(path) - 1] == '/' && ft_strlen(path) > 1)
		path[ft_strlen(path) - 1] = '\0';
	if (chdir(path) != 0)
	{
		ft_printf_fd(STDERR, "cd: %s: No such file or directory\n", path);
		return (1);
	}
	return (0);
}
