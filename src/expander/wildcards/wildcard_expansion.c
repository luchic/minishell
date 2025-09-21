
#include "expander_internal.h"
#include "ft_defines.h"
#include "ft_printf.h"
#include "libft.h"
#include "parser.h"
#include <dirent.h>
#include <sys/stat.h>

char	**expand_wildcard_internal(char *pattern, int *status)
{
	char	*curr_path;
	char	**matched;

	curr_path = get_current_path(pattern);
	if (!curr_path)
	{
		set_status(status, -1);
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
	restore_str(matched_file);
	if (!matched_file)
		return (-1);
	tmp = ft_array_append(*new_args, matched_file);
	if (!tmp)
		return (free(matched_file), -1);
	*new_args = tmp;
	return (0);
}

int	expand_wildcard(char ***new_args, char *arg)
{
	char	*matched_file;
	char	**matched;
	char	**tmp;
	int		status;
	int		i;

	status = 0;
	matched = expand_wildcard_internal(arg, &status);
	if (!matched && status == -1)
		return (restore_str(arg), ft_log_fd(LOG_ERROR, STDERR,
				"expand_wildcards: status is -1: %s\n", arg), -1);
	else if (!matched)
		return (expand_wildcard_if_not_matched(new_args, arg));
	i = -1;
	while (matched[++i])
	{
		matched_file = ft_strdup(matched[i]);
		if (!matched_file)
			return (free_str_array(matched), -1);
		tmp = ft_array_append(*new_args, matched_file);
		if (!tmp)
			return (free_str_array(matched), free(matched_file), -1);
		*new_args = tmp;
	}
	return (free_str_array(matched), 0);
}

int	expand_wildcard_if_need(char ***new_arg, char *arg)
{
	char	*copy_arg;
	char	**tmp;

	if (is_arg_wildcard(arg))
		return (expand_wildcard(new_arg, arg));
	copy_arg = ft_strdup(arg);
	restore_str(copy_arg);
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

	ft_log_fd(LOG_DEBUG, STDERR, "run_wildcards_expander: %s: %s\n",
		"Expanding wildcards for command", cmd->name);
	if (!cmd || !cmd->args)
		return (-1);
	if (!is_wildcard(cmd))
		return (restore_values(cmd), 0);
	args = cmd->args;
	new_args = NULL;
	i = -1;
	while (args && args[++i])
	{
		ft_log_fd(LOG_DEBUG, STDERR,
			"run_wildcards_expander: Processing arg[%d]: %s\n", i, args[i]);
			/// to delete --- IGNORE ---
		if (expand_wildcard_if_need(&new_args, args[i]) == -1)
		{
			ft_log_fd(LOG_ERROR, STDERR_FILENO,
				"expand_wildcards: Failed to expand wildcard: %s\n", args[i]);
			if (new_args)
				free_str_array(new_args);
			return (-1);
		}
	}
	if (expand_wildcard_redirection(cmd->redirections, cmd) == -1)
	{
		ft_log_fd(LOG_ERROR, STDERR_FILENO,
			"expand_wildcards: Failed to expand wildcard in redirection\n");
		return (free_str_array(new_args), -1);
	}
	return (free_str_array(cmd->args), cmd->args = new_args, 0);
}

// #include <stdio.h>
// #include <stdlib.h>

// int main(int argc, char **argv)
// {
// 	char **new_args = NULL;
// 	char *arg;
// 	if (argc != 2)
// 	{
// 		arg = ft_strdup("*");0
// 		arg = ft_strdup(argv[1]);
// 	}
// 	// new_args = calloc(3, sizeof(char *));
// 	// new_args[0] = strdup("file1.txt");
// 	// new_args[1] = strdup("*");
// 	expand_wildcard_if_need(&new_args, arg);

// 	for(int i = 0; new_args && new_args[i]; i++)
// 	{
// 		printf("new_args[%d]: %s\n", i, new_args[i]);
// 	}
// }