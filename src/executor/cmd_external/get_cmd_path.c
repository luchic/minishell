/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:44:16 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/28 14:26:44 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

char	**get_cmd_paths(void)
{
	char	**paths;
	char	*env_path;

	env_path = get_env("PATH");
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	free(env_path);
	return (paths);
}

char	*get_cmd_path(char *cmd_name, char **envp)
{
	char	**paths;
	char	*tmp;
	char	*cmd_path;
	int		i;

	if (!cmd_name || !envp)
		return (NULL);
	paths = get_cmd_paths();
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i++], "/");
		if (!tmp)
			return (free_str_array(paths), NULL);
		cmd_path = ft_strjoin(tmp, cmd_name);
		if (!cmd_path)
			return (free(tmp), free_str_array(paths), NULL);
		free(tmp);
		if (access(cmd_path, F_OK) == 0)
			return (free_str_array(paths), cmd_path);
		free(cmd_path);
	}
	return (free_str_array(paths), NULL);
}
