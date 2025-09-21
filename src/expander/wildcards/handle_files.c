/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:11:39 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/21 15:36:27 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_internal.h"
#include "ft_common.h"
#include <dirent.h>
#include <sys/stat.h>

static int	ft_append_file(char *filename, char ***files)
{
	char	**tmp;
	char	*cur_file;

	cur_file = ft_strdup(filename);
	if (!cur_file)
		return (-1);
	tmp = ft_array_append(*files, cur_file);
	if (!tmp)
	{
		free(cur_file);
		return (-1);
	}
	*files = tmp;
	return (0);
}

/// @brief
/// NOTE: don't support hidden files now
static char	**get_current_files(char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**files;

	files = NULL;
	if (!is_directory(path))
		return (NULL);
	dir = opendir(path);
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strncmp(entry->d_name, ".", 1) != 0
			&& ft_append_file(entry->d_name, &files) == -1)
		{
			closedir(dir);
			free_str_array(files);
			return (NULL);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (files);
}


char	**get_matching_files(char *path, char *pattern, int *status)
{
	char	**matched;
	char	**files;
	int		i;

	files = get_current_files(path);
	if (!files)
		return (set_status(status, -1), NULL);
	i = 0;
	matched = NULL;
	while (files[i])
	{
		if (ft_fnmatch(pattern, files[i]))
		{
			if (ft_append_file(files[i], &matched) == -1)
			{
				free_str_array(files);
				free_str_array(matched);
				return (NULL);
			}
		}
		i++;
	}
	free_str_array(files);
	return (matched);
}

char	*get_file_prefix(char *path, char *pattern)
{
	char	*prefix;

	if (path[ft_strlen(path) - 1] != '/')
		prefix = ft_strjoin(path, "/");
	else
		prefix = ft_strdup(path);
	if (ft_strcmp(prefix, "./") == 0 && ft_strncmp(pattern, "./", 2) != 0)
	{
		free(prefix);
		return (ft_strdup(""));
	}
	return (prefix);
}

// #include <stdio.h>
// #include <stdlib.h>

// int main(int argc, char **argv)
// {
// 	char **new_args = NULL;
// 	char *arg;
// 	if (argc != 2)
// 	{
// 		arg = ft_strdup("\\*hello");
// 	}
// 	else
// 	{
// 		arg = ft_strdup(argv[1]);
// 	}
// 	new_args =  get_matching_files(".", arg);
// 	free(arg);
// 	if (!new_args)
// 	{
// 		printf("No matching files\n");
// 		return 0;
// 	}
// 	for(int i = 0; new_args && new_args[i]; i++)
// 	{
// 		printf("new_args[%d]: %s\n", i, new_args[i]);
// 	}
// 	free_str_array(new_args);
// }