
#include "expander.h"
#include "expander_internal.h"
#include "ft_defines.h"
#include "ft_printf.h"
#include "libft.h"
#include "parser.h"
#include <dirent.h>
#include <sys/stat.h>

// =============================================================================
// =============================== CORE Expander ===============================
// =============================================================================

char	**expand_wildcard_internal(char *pattern, int *status)
{
	char	*curr_path;
	char	**matched;
	char	**tmp;

	curr_path = get_current_path(pattern);
	if (!curr_path)
	{
		ft_log_fd(LOG_DEBUG, STDERR_FILENO,
			"expand_wildcards: Internal error: failed to \
			get current path from pattern: %s\n", pattern);
		if (status)
			*status = -1;
		return (NULL);
	}
	matched = expand_wildcard_recursive(curr_path, pattern, status);
	free(curr_path);
	return (matched);
}

int	expand_wildcard_if_not_matched(char ***new_args, char *arg)
{
	char	*matched_file;
	char	**tmp;

	matched_file = ft_strdup(arg);
	if (!matched_file)
		return (-1);
	tmp = ft_array_append(*new_args, matched_file);
	if (!tmp)
		return (free(matched_file), -1);
	*new_args = tmp;
	return (0);
}

int	expand_wildcard(char ***new_args, char *arg, t_command *cmd)
{
	char	*matched_file;
	char	**matched;
	char	**tmp;
	int		status;
	int		i;

	status = 0;
	matched = expand_wildcard_internal(arg, &status);
	if (!matched && status == -1)
		return (-1);
	else if (!matched)
		return (expand_wildcard_if_not_matched(new_args, arg));
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
	return (free_str_array(matched), 0);
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

int	run_wildcards_expander(t_command *cmd)
{
	char	**args;
	char	**new_args;
	int		i;

	if (!cmd || !cmd->args)
		return (-1);
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
	return (cmd->args = new_args, 0);
}
