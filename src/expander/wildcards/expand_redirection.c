/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:09:34 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/24 15:09:37 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_internal.h"

static int	set_new_value(t_redirection *redirection, char **new_args,
		t_command *cmd)
{
	if (new_args && count_args(new_args) > 1)
	{
		ft_printf_fd(STDERR, "%s: %s: ambiguous redirection\n", PREFIX,
			redirection->value);
		cmd->mnsh->last_exit_status = EXIT_FAILURE;
		if (!redirection->value)
			return (-1);
	}
	if (new_args && count_args(new_args) == 1)
	{
		free(redirection->value);
		redirection->value = ft_strdup(new_args[0]);
		if (!redirection->value)
			return (-1);
	}
	return (0);
}

static int	expand_redirection_value(t_redirection *redirection, t_command *cmd)
{
	char	**new_args;
	int		status;

	new_args = NULL;
	status = 0;
	new_args = expand_wildcard_internal(redirection->value, &status);
	if (!new_args && status == -1)
	{
		ft_log_fd(LOG_ERROR, STDERR, "expand_wildcard_redirection: %s: %s\n",
			"Failed to expand wildcard", redirection->value);
		return (-1);
	}
	if (set_new_value(redirection, new_args, cmd) == -1)
	{
		free_str_array(new_args);
		return (-1);
	}
	free_str_array(new_args);
	return (0);
}

int	expand_wildcard_redirection(t_list *redir, t_command *cmd)
{
	t_list			*current;
	t_redirection	*redirection;

	if (!redir || !cmd)
		return (0);
	current = redir;
	while (current)
	{
		redirection = (t_redirection *)current->content;
		if (redirection && redirection->value
			&& is_arg_wildcard(redirection->value))
		{
			if (expand_redirection_value(redirection, cmd) == -1)
			{
				return (-1);
			}
		}
		restore_str(redirection->value);
		current = current->next;
	}
	return (0);
}
