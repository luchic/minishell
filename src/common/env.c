/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 09:16:40 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/28 11:40:00 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "ft_defines.h"
#include "libft.h"

char	*get_env_local(const char *name)
{
	t_list		*node;
	t_minishell	*mnsh;

	mnsh = *get_mnsh();
	if (!mnsh || !name || !mnsh->variables)
		return (NULL);
	node = mnsh->variables;
	while (node)
	{
		if (node && ft_strcmp(((t_var *)node->content)->name, name) == 0)
			return (ft_strdup(((t_var *)node->content)->value));
		node = node->next;
	}
	return (NULL);
}

int	is_var_in_envp(char *env_var, char *name)
{
	int	nlen;
	int	vlen;

	if (!env_var || !name)
		return (0);
	nlen = ft_strlen(name);
	vlen = ft_strlen(env_var);
	if (nlen > vlen)
		return (0);
	if (ft_strncmp(env_var, name, ft_strlen(name)) != 0)
		return (0);
	if (env_var[nlen] == '\0')
		return (1);
	if (env_var[nlen] != '=')
		return (0);
	return (1);
}

char	*get_env(const char *name)
{
	char		**env;
	t_minishell	*mnsh;

	mnsh = *get_mnsh();
	if (!mnsh || !name || !mnsh->envp)
		return (NULL);
	env = mnsh->envp;
	while (*env)
	{
		if (is_var_in_envp(*env, (char *)name))
			return (ft_strdup(*env + ft_strlen(name) + 1));
		env++;
	}
	return (NULL);
}
