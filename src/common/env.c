/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 09:16:40 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/26 09:16:42 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "libft.h"

static char	*get_internal_env(t_minishell *mnsh, const char *name)
{
	t_var	*vars;

	if (!mnsh || !name || !mnsh->variables)
		return (NULL);
	vars = mnsh->variables;
	while (vars)
	{
		if (vars && ft_strcmp(vars->name, name) == 0)
			return (ft_strdup(vars->value));
		vars = vars->next;
	}
	return (NULL);
}

int	is_valid_name(char *variable, char *name)
{
	int	nlen;
	int	vlen;

	if (!variable || !name)
		return (0);
	nlen = ft_strlen(name);
	vlen = ft_strlen(variable);
	if (nlen > vlen)
		return (0);
	if (ft_strncmp(variable, name, ft_strlen(name)) != 0)
		return (0);
	if (variable[nlen] == '\0')
		return (1);
	if (variable[nlen] != '=')
		return (0);
	return (1);
}

char	*get_env(t_minishell *mnsh, const char *name)
{
	char	**env;

	if (!mnsh || !name || !mnsh->envp)
		return (NULL);
	env = mnsh->envp;
	while (*env)
	{
		if (is_valid_name(*env, (char *)name))
			return (ft_strdup(*env + ft_strlen(name) + 1));
		env++;
	}
	return (get_internal_env(mnsh, name));
}
