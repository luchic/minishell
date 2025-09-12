
#include "expander.h"
#include "ft_defines.h"
#include "ft_printf.h"
#include "libft.h"
#include "parser.h"
#include <dirent.h>

char	*get_current_path(char *format)
{
	char	*star;
	char	*current_path;
	char	*slash;

	star = ft_strchr(format, '*');
	slash = ft_strrchr(format, '/');
	if (!slash)
		return (ft_strdup("."));
	*star = '\0';
	slash = ft_strrchr(format, '/');
	if (!slash)
		return (NULL);
	*star = '*';
	current_path = ft_substr(format, 0, slash - format);
	return (current_path);
}

char *get_last_slash(const char *pattern)
{
	char *slash;
	char *star;

	star = ft_strchr(pattern, '*');
	if (!star)
		return (NULL);
	*star = '\0';
	slash = ft_strrchr(pattern, '/');
	if (!slash)
		return (pattern);
	*star = '*';
	return (slash + 1);
}

int ft_fnmatch(const char *pattern, const char *string)
{
	char *start;
	char *star;
	start = get_last_slash(pattern);
	if (!start)
		return (0);
	star = ft_strchr(start, '*');
	if (!star)
		return (0);
	int matched = ft_strncmp(start, string, star - start);
	while (*start && *start !=  '*')
	{
		if (*start != *string)
			return (0);
		start++;
		string++;
	}
	if (*start == '*')
		start++;
	return (1);
}

/// @brief
/// NOTE: don't support hidden files now
char **get_current_files(char *pattern)
{
	DIR *dir;
	struct dirent *entry;
	char **files;
	char **tmp;
	char *cur_file;
	char *cur_path;

	cur_path = get_current_path(pattern);
	if (!cur_path)
		return (NULL);
	dir = opendir(cur_path);
	if (!dir)
		return (NULL);
	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_strncmp(entry->d_name, ".", 1) == 0)
			continue ;
		cur_file = ft_strdup(entry->d_name);
		if (!cur_file)
		{
			closedir(dir);
			free_str_array(files);
			return (NULL);
		}
		tmp = ft_array_append(files, cur_file);
		if (!tmp)
		{
			closedir(dir);
			free_str_array(files);
			free(cur_file);
			return (NULL);
		}
		files = tmp;
	}
	closedir(dir);
	return (files);
}

char	**get_matching_files(char *pattern)
{
	char **matched = NULL;
	char **tmp;
	char **files;
	int i;
	char *cur_file;

	files = get_current_files(pattern);
	if (!files)
		return (NULL);
	i = 0;
	while (files[i])
	{
		if (ft_fnmatch(pattern, files[i]))
		{
			cur_file = ft_strdup(files[i]);
			if (!cur_file)
			{
				free_str_array(matched);
				return (NULL);
			}
			tmp = ft_array_append(matched, cur_file);
			if (!tmp)
			{
				free_str_array(matched);
				free(cur_file);
				return (NULL);
			}
			matched = tmp;
		}
	}
	free_str_array(files);
	return (matched);
}

char **expand_wildcard_recursive(char **matched, char *pattern)
{
	char **expanded;
	int i;

	expanded = get_matching_files(pattern);
	// while (matched && matched[i])
	// {
	// 	expanded = ft_array_append(expanded, ft_strdup(matched[i]));
	// 	if (!expanded)
	// 	{
	// 		free_str_array(matched);
	// 		return (NULL);
	// 	}
	// 	i++;
	// }
	// free_str_array(matched);
	return (expanded);
}

int expand_wildcard(char ***new_args, char *arg, t_command *cmd)
{
	char **matched;
	char **tmp;
	int i;

	matched = NULL;
	matched = expand_wildcard_recursive(matched, arg);
	if (!matched)
		return (-1);
	i = 0;
	while (matched[i])
	{
		tmp = ft_array_append(*new_args, ft_strdup(matched[i]));
		if (!tmp)
			return (free_str_array(matched), -1);
		*new_args = tmp;
		i++;
	}
	return (0);
}

int	expand_wildcard_if_need(char ***new_arg, char *arg, t_command *cmd)
{
	int		count;
	char	*copy_arg;
	char	**tmp;

	if (ft_strchr(arg, '*'))
	{
		return (expand_wildcard(new_arg, arg, cmd));
	}
	copy_arg = ft_strdup(arg);
	if (!copy_arg)
		return (-1);
	tmp = ft_array_append(*new_arg, copy_arg); // inside will be freed
	if (!tmp)
		return (free(copy_arg), -1);
	*new_arg = tmp;
	return (0);
}

int is_wildcard(char **arg)
{
	while (**arg)
	{
		if (ft_strchr(*arg, '*'))
			return (1);
		arg++;
	}
	return (0);
}

int	run_wildcards_expander(t_command *cmd)
{
	char	**args;
	char	**new_args;
	int		i;

	if (is_wildcard(cmd->args) == 0)
		return (0);
	i = 0;
	args = cmd->args;
	new_args = NULL;
	while (args && args[i])
	{
		if (expand_wildcard_if_need(&new_args, args[i], cmd) == -1)
		{
			ft_log_fd(LOG_ERROR, STDERR_FILENO,
				"expand_wildcards: Failed to expand wildcard: %s\n", args[i]);
			if (new_args)
				free_str_array(new_args);
			return (-1);
		}
		i++;
	}
	free_str_array(cmd->args);
	cmd->args = new_args;
	return (0);
}

// DIR *dir;
// struct dirent *entry;

// dir = opendir("./");
// if (!dir)
// 	return (-1);
// while ((entry = readdir(dir)) != NULL)
// {
// 	ft_printf("Found file: %s\n", entry->d_name);
// }
// return (0);
// ft_log_fd(LOG_INFO, STDOUT, "Run expand_variable: cmd: %s\n", cmd->name);
// if (!cmd->mnsh)
// {
// 	ft_log_fd(LOG_DEBUG, STDOUT,
// 		"expand_variable: minishell: Internal error: mnsh is NULL\n");
// 	return ;
// }
// args = (cmd->args + 1);
// for (i = 0; args && args[i]; i++)
// {
// 	args[i] = expand_variable_if_need(args[i], cmd->mnsh);
// }
// }
