/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:43:15 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/27 18:37:41 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

static char	*get_new_envp_var(char *name, char *value)
{
	char	*new;
	char	*new_name;
	size_t	new_size;

	new_name = ft_strjoin(name, "=");
	if (!new_name)
		return (NULL);
	new_size = ft_strlen(new_name) + ft_strlen(value) + 1;
	new = (char *)malloc(new_size);
	if (!new)
	{
		free(new_name);
		return (NULL);
	}
	ft_strlcpy(new, new_name, new_size);
	ft_strlcat(new, value, new_size);
	free(new_name);
	return (new);
}

void	change_env_var(const char *name, char *value, t_command *cmd)
{
	char	*new;
	char	*new_name;
	int		i;
	char	**tmp;

	new = get_new_envp_var((char *)name, value);
	if (!new)
		return ;
	new_name = ft_strjoin((char *)name, "=");
	if (!new_name)
		return (free(new));
	i = -1;
	while (cmd->mnsh->envp[++i])
	{
		if (ft_strncmp(cmd->mnsh->envp[i], new_name, ft_strlen(new_name)) == 0)
			return (free(cmd->mnsh->envp[i]), cmd->mnsh->envp[i] = new,
				free(new_name));
	}
	tmp = ft_realloc(cmd->mnsh->envp, sizeof(char *) * (i + 1), sizeof(char *)
			* (i + 2));
	if (!tmp)
		return (free(new), free(new_name));
	return (cmd->mnsh->envp = tmp, cmd->mnsh->envp[i] = new,
		cmd->mnsh->envp[i + 1] = NULL, free(new_name));
}

int	ft_cd(t_command *cmd)
{
	char	pwd[1024];
	char	oldpwd[1024];
	int		status;

	getcwd(oldpwd, sizeof(oldpwd));
	if (count_args(cmd->args) > 2)
	{
		ft_printf_fd(STDERR, "cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
		status = ft_cd_home();
	else if (cmd->args[1] && ft_strcmp(cmd->args[1], "-") == 0)
		status = ft_cd_oldpwd();
	else
		status = ft_cd_to_path(cmd->args[1]);
	if (status != 0)
		return (status);
	getcwd(pwd, sizeof(pwd));
	change_env_var("OLDPWD", oldpwd, cmd);
	change_env_var("PWD", pwd, cmd);
	return (status);
}

/* int main(void)
{
	t_command cmd;
	t_minishell mnsh;

	ft_memset(&mnsh, 0, sizeof(t_minishell));
	mnsh.envp = malloc(sizeof(char *) * (count_args(environ) + 1));
	if (!mnsh.envp)
		return (1);
	int i = 0;
	while (environ[i])
	{
		mnsh.envp[i] = ft_strdup(environ[i]);
		if (!mnsh.envp[i])
		{
			while (i > 0)
				free(mnsh.envp[--i]);
			free(mnsh.envp);
			return (1);
		}
		i++;
	}
	mnsh.envp[i] = NULL;

	cmd.type = CMD_BUILTIN;
	cmd.fd_in = -1;
	cmd.fd_out = STDOUT_FILENO;
	cmd.name = "cd";
	cmd.mnsh = &mnsh;

	cmd.args = malloc(sizeof(char *) * 3);
	cmd.args[0] = "cd";
	cmd.args[1] = "..";
	cmd.args[2] = NULL;

	ft_cd(&cmd);
	free(cmd.args);
	free(mnsh.envp);
	return (0);
} */
