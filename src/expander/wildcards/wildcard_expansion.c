/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:10:07 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/24 15:24:01 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_internal.h"
#include "ft_defines.h"
#include "ft_printf.h"
#include "libft.h"
#include "parser.h"
#include <dirent.h>
#include <sys/stat.h>

static int	expand_wildcard_if_not_matched(char ***new_args, char *arg)
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

static int	expand_wildcard(char ***new_args, char *arg)
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

static int	expand_wildcard_if_need(char ***new_arg, char *arg)
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

static int	expand_wildcards_args(t_command *cmd)
{
	char	**args;
	char	**new_args;
	int		i;

	args = cmd->args;
	new_args = NULL;
	i = -1;
	while (args && args[++i])
	{
		ft_log_fd(LOG_DEBUG, STDERR,
			"run_wildcards_expander: Processing arg[%d]: %s\n", i, args[i]);
		if (expand_wildcard_if_need(&new_args, args[i]) == -1)
		{
			ft_log_fd(LOG_ERROR, STDERR_FILENO,
				"expand_wildcards: Failed to expand wildcard: %s\n", args[i]);
			if (new_args)
				free_str_array(new_args);
			return (-1);
		}
	}
	free_str_array(cmd->args);
	cmd->args = new_args;
	return (0);
}

int	run_wildcards_expander(t_command *cmd)
{
	ft_log_fd(LOG_DEBUG, STDERR, "run_wildcards_expander: %s: %s\n",
		"Expanding wildcards for command", cmd->name);
	if (!cmd || !cmd->args)
		return (-1);
	if (!is_wildcard(cmd))
		return (restore_values(cmd), 0);
	if (expand_wildcards_args(cmd) == -1)
	{
		ft_log_fd(LOG_ERROR, STDERR_FILENO,
			"expand_wildcards: Failed to expand wildcard in args\n");
		return (-1);
	}
	if (expand_wildcard_redirection(cmd->redirections, cmd) == -1)
	{
		ft_log_fd(LOG_ERROR, STDERR_FILENO,
			"expand_wildcards: Failed to expand wildcard in redirection\n");
		return (-1);
	}
	return (0);
}
