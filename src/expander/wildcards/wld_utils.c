/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wld_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:10:26 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/18 10:41:36 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_common.h"
#include "libft.h"
#include <dirent.h>
#include <sys/stat.h>

char	*get_last_slash(const char *pattern)
{
	char	*slash;
	char	*star;

	star = ft_strchr_not_escaped(pattern, '*');
	if (!star)
		return (NULL);
	*star = '\0';
	slash = ft_strrchr(pattern, '/');
	*star = '*';
	if (!slash)
		return ((char *)pattern);
	return (slash + 1);
}

char	*extract_pattern(char *pattern)
{
	char	*start;
	char	*slash;

	start = get_last_slash(pattern);
	if (!start)
		return (ft_strdup(pattern));
	slash = ft_strrchr(start, '/');
	if (!slash)
		slash = ft_strchr(start, '\0');
	return (ft_substr(start, 0, slash - start));
}

char	*get_prefix(char *pattern)
{
	char	*slash;

	slash = get_last_slash(pattern);
	if (!slash || slash == pattern)
		return (ft_strdup(""));
	return (ft_substr(pattern, 0, slash - pattern));
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}

char	*get_current_path(char *format)
{
	char	*star;
	char	*current_path;
	char	*slash;

	star = ft_strchr_not_escaped(format, '*');
	if (!star)
		return (NULL);
	slash = ft_strrchr(format, '/');
	if (!slash)
		return (ft_strdup("."));
	*star = '\0';
	slash = ft_strrchr(format, '/');
	*star = '*';
	if (!slash)
		return (ft_strdup("."));
	current_path = ft_substr(format, 0, slash - format);
	return (current_path);
}
