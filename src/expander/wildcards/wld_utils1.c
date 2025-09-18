/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wld_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:10:30 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/18 20:30:30 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "ft_defines.h"
#include "ft_printf.h"
#include "libft.h"
#include <dirent.h>
#include <sys/stat.h>

char	*get_slash_after(const char *pattern)
{
	char	*slash;
	char	*star;

	star = ft_strchr(pattern, '*');
	if (!star)
		return (NULL);
	slash = ft_strrchr(star, '/');
	if (!slash)
		return ((char *)pattern);
	return (slash + 1);
}

int	ft_fnmatch(char *pattern, const char *filename, const char *origin)
{
	char	*tmp;

	if (*pattern == '\0')
		return (*filename == '\0');
	tmp = ft_strchr_not_escaped(pattern, '\\');
	if (*pattern == '\\' && pattern == tmp && *(pattern + 1) != '\0')
	{
		if (*(pattern + 1) == '*' && *filename == '*')
			return (ft_fnmatch(pattern + 2, filename + 1, tmp + 2));
		else if (*(pattern + 1) == '*' && *filename != '*')
			return (0);
		else if (*(pattern + 1) == *filename)
			return (ft_fnmatch(pattern + 2, filename + 1, tmp + 2));
		else
			return (0);
	}
	tmp = ft_strchr_not_escaped(origin, '*');
	if (*pattern == '*' && pattern == tmp)
	{
		while (*pattern == '*')
			pattern++;
		if (*pattern == '\0')
			return (1);
		while (*filename)
		{
			if (ft_fnmatch(pattern, filename, tmp))
				return (1);
			filename++;
		}
	}
	if (*pattern == *filename)
		return (ft_fnmatch(pattern + 1, filename + 1, origin));
	return (0);
}

// TODO: WTF is hier
int	is_wildcard(char **arg)
{
	if (!arg)
		return (0);
	while (*arg)
	{
		if (ft_strchr_not_escaped(*arg, '*'))
			return (1);
		arg++;
	}
	return (0);
}
