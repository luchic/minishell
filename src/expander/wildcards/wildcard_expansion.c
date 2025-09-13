
#include "expander.h"
#include "ft_defines.h"
#include "ft_printf.h"
#include "libft.h"
#include "parser.h"
#include <sys/stat.h>
#include <dirent.h>

// =============================================================================
// ============================== UTILS functions ==============================
// =============================================================================

char *get_last_slash(const char *pattern)
{
	char *slash;
	char *star;

	star = ft_strchr(pattern, '*');
	if (!star)
		return (NULL);
	*star = '\0';
	slash = ft_strrchr(pattern, '/');
	*star = '*';
	if (!slash)
		return ((char *)pattern);
	return (slash + 1);
}

char *extract_pattern(char *pattern)
{
	char *start = get_last_slash(pattern);
	if (!start)
		return ft_strdup(pattern);
	char *slash = ft_strrchr(start, '/');
	if (!slash)
		slash = ft_strchr(start, '\0');
	return (ft_substr(start, 0, slash - start));
}

char *get_prefix(char *pattern)
{
	char *slash = get_last_slash(pattern);
	if (!slash || slash == pattern)
		return (ft_strdup(""));
	return (ft_substr(pattern, 0, slash - pattern));
}

int is_directory(const char *path)
{

	struct stat path_stat;
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

	star = ft_strchr(format, '*');
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



char *get_slash_after(const char *pattern)
{
	char *slash;
	char *star;

	star = ft_strchr(pattern, '*');
	if (!star)
		return (NULL);
	slash = ft_strrchr(star, '/');
	if (!slash)
		return ((char *)pattern);
	return (slash + 1);
}

int ft_fnmatch(char *pattern, const char *filename)
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
	if (*pattern == *filename)
		return (ft_fnmatch(pattern + 1, filename + 1));
	return (0);
}

// =============================================================================
// =============================== CORE Expander ===============================
// =============================================================================

/// @brief
/// NOTE: don't support hidden files now
char **get_current_files(char *path)
{
	DIR *dir;
	struct dirent *entry;
	char **files = NULL;
	char **tmp;
	char *cur_file;

	if (!is_directory(path))
		return (NULL);
	dir = opendir(path);
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



char	**get_matching_files(char *path, char *pattern)
{
	char **matched = NULL;
	char **tmp;
	char **files;
	char *cur_file;
	int i;

	i = 0;
	files = get_current_files(path);
	if (!files)
		return (NULL);
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
		i++;
	}
	free_str_array(files);
	return (matched);
}

char *get_file_prefix(char *path, char *pattern)
{
	char *prefix;

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

char **expand_wildcard_recursive(char *path, char *pattern, int *status)
{
	char **expanded = NULL;
	char **matched = NULL;
	char *joined;
	char *prefix;
	char *extracted_pattern;
	int i;

	// NOTE: what if '.src/*/common/tmp.h' ?
	extracted_pattern = extract_pattern(pattern);
	if (!extracted_pattern)
	{
		if (status)
			*status = -1;
		return (NULL);
	}
	matched = get_matching_files(path, extracted_pattern);
	free(extracted_pattern);
	if (!matched)
	{
		if (status)
			*status = -1;
		return (NULL);
	}
	prefix = get_file_prefix(path, pattern);
	if (!prefix)
	{
		if (status)
			*status = -1;
		free_str_array(matched);
		return (NULL);
	}
	i = 0;
	while (matched && matched[i])
	{

		joined = ft_strjoin(prefix, matched[i]);
		if (!joined)
		{
			if (status)
				*status = -1;
			free(prefix);
			free_str_array(matched);
			return (NULL);
		}
		// NOTE: memory leak here possibly
		expanded = ft_array_append(expanded, joined);
		if (!expanded)
		{	
			if (status)
				*status = -1;
			free(prefix);
			free_str_array(matched);
			free(joined);
			return (NULL);
		}
		i++;
	}
	free(prefix);
	free_str_array(matched);
	char *last_slash = get_slash_after(pattern);
	if (!last_slash  || last_slash == pattern)
	{
		if (status)
			*status = 0;
		return (expanded);
	}

	char *new_pattern = ft_strdup(last_slash);
	if (!new_pattern)
	{
		if (status)
			*status = -1;
		return (free_str_array(expanded), NULL);
	}
	i = 0;
	char **new_expanded = NULL;
	while (expanded	&& expanded[i])
	{
		char **sub_matched = expand_wildcard_recursive(expanded[i], new_pattern, status);
		if (!sub_matched)
		{
			i++;
			continue;
		}
		int j = 0;
		while (sub_matched[j])
		{
			char **tmp = ft_array_append(new_expanded, ft_strdup(sub_matched[j]));
			if (!tmp)
			{
				if (status)
					*status = -1;
				if (new_expanded)
					free_str_array(new_expanded);
				free_str_array(sub_matched);
				free(new_pattern);
				free_str_array(expanded);
				return (NULL);
			}
			new_expanded = tmp;
			j++;
		}
		free_str_array(sub_matched);
		i++;
	}	

	free(new_pattern);
	free_str_array(expanded);
	if (status)
		*status = 0;
	return (new_expanded);
}

char **expand_wildcard_internal(char *pattern, int *status)
{
	char *curr_path;
	char **matched;
	char **tmp;

	curr_path = get_current_path(pattern);
	if (!curr_path)
	{
		ft_log_fd(LOG_DEBUG, STDERR_FILENO,
			"expand_wildcards: Internal error: failed to get current path from pattern: %s\n", pattern);
		if (status)
			*status = -1;
		return (NULL);
	}
	matched = expand_wildcard_recursive(curr_path, pattern, status);
	free(curr_path);
	return (matched);
}

int expand_wildcard(char ***new_args, char *arg, t_command *cmd)
{
	char *matched_file;
	char **matched;
	char **tmp;
	int status;
	int i;

	matched = expand_wildcard_internal(arg, &status);
	if (!matched && status == -1)
		return (-1);
	else if (!matched)
	{
		matched_file = ft_strdup(arg);
		if (!matched_file)
			return (-1);
		tmp = ft_array_append(*new_args, matched_file);
		if (!tmp)
			return (free(matched_file), -1);
		*new_args = tmp;
		return (0);
	}
	i = 0;
	while (matched[i])
	{
		matched_file = ft_strdup(matched[i]);
		if (!matched_file)
			return (free_str_array(matched), -1);
		tmp = ft_array_append(*new_args, matched_file);
		if (!tmp)
			return (free_str_array(matched), free(matched_file), -1);
		*new_args = tmp;
		i++;
	}
	free_str_array(matched);
	return (0);
}

int	expand_wildcard_if_need(char ***new_arg, char *arg, t_command *cmd)
{
	char	*copy_arg;
	char	**tmp;

	if (ft_strchr(arg, '*'))
		return (expand_wildcard(new_arg, arg, cmd));
	copy_arg = ft_strdup(arg);
	if (!copy_arg)
		return (-1);
	tmp = ft_array_append(*new_arg, copy_arg);
	if (!tmp)
		return (free(copy_arg), -1);
	*new_arg = tmp;
	return (0);
}

int is_wildcard(char **arg)
{
	if (!arg)
	{
		ft_log_fd(LOG_DEBUG, STDERR_FILENO,
			"expand_wildcards: Internal error: args is NULL\n");
		return (0);
	}
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
