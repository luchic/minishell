/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wld_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:26:22 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/24 15:26:34 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_internal.h"
#include "ft_common.h"
#include "ft_defines.h"
#include "ft_printf.h"
#include "libft.h"

char	*get_slash_after(const char *pattern)
{
	char	*slash;
	char	*star;

	star = ft_strchr_not_escaped(pattern, '*');
	if (!star)
		return (NULL);
	slash = ft_strchr(star, '/');
	if (!slash)
		return ((char *)pattern);
	return (slash + 1);
}

int	ft_fnmatch(char *pattern, const char *filename)
{
	if (*pattern == '\0')
		return (*filename == '\0');
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (*pattern == '\0')
			return (1);
		while (*filename)
		{
			if (ft_fnmatch(pattern, filename))
				return (1);
			filename++;
		}
	}
	if (*pattern == SENTINEL && *filename == '*')
		return (ft_fnmatch(pattern + 1, filename + 1));
	if (*pattern == *filename)
		return (ft_fnmatch(pattern + 1, filename + 1));
	return (0);
}

int	is_wildcard_redirection(t_list *redirection)
{
	t_redirection	*rdir;

	if (!redirection || !redirection->content)
		return (0);
	while (redirection)
	{
		rdir = (t_redirection *)redirection->content;
		if (rdir && rdir->value && is_arg_wildcard(rdir->value))
			return (1);
		redirection = redirection->next;
	}
	return (0);
}

int	is_wildcard(t_command *cmd)
{
	int	i;
	int	j;

	if (!cmd)
		return (0);
	i = -1;
	while (cmd->args[++i])
	{
		j = -1;
		while (cmd->args[i][++j])
		{
			if (cmd->args[i][j] == '*')
				return (1);
		}
	}
	if (is_wildcard_redirection(cmd->redirections))
		return (1);
	return (0);
}

int	is_arg_wildcard(char *arg)
{
	int	i;

	if (!arg)
		return (0);
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '*')
			return (1);
		i++;
	}
	return (0);
}
