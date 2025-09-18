/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:13:40 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/18 19:39:38 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_internal.h"
#include "ft_printf.h"
#include "parser.h"

static char	*expand_variable_if_need(int index, char *arg, t_command *cmd)
{
	t_cmd_expander	*expander;
	char			*new_arg;

	expander = get_arg_expander(index, cmd->expander);
	if (!expander)
		return (arg);
	new_arg = extract_arg(arg, expander->expand, cmd->mnsh);
	if (!new_arg)
		return (free(arg), NULL);
	free(arg);
	return (new_arg);
}

int	expand_assignments(t_list *assignments, t_minishell *mnsh)
{
	t_list			*current;
	t_assignment	*assignment;
	char			*new_value;

	if (!assignments || !mnsh)
		return (-1);
	current = assignments;
	while (current)
	{
		assignment = (t_assignment *)current->content;
		if (assignment && assignment->value)
		{
			if (assignment->expand)
				new_value = extract_arg(assignment->value, assignment->expand,
						mnsh);
			else
				new_value = ft_strdup(assignment->value);
			if (!new_value)
				return (-1);
			free(assignment->value);
			assignment->value = new_value;
		}
		current = current->next;
	}
	return (0);
}

int	expand_variable(t_list *redirections, t_command *cmd)
{
	t_list			*current;
	t_redirection	*redir;
	char			*new_value;

	if (!redirections || !cmd)
		return (0);
	current = redirections;
	while (current)
	{
		redir = (t_redirection *)current->content;
		if (redir && redir->value)
		{
			if (redir->expander)
				new_value = extract_arg(redir->value, redir->expander,
						cmd->mnsh);
			else
				new_value = ft_strdup(redir->value);
			if (!new_value)
				return (-1);
			free(redir->value);
			redir->value = new_value;
		}
		current = current->next;
	}
	return (0);
}

// TODO: add returning int for error handling
int	run_variable_expander(t_command *cmd)
{
	int		i;
	char	**args;

	if (!cmd || !cmd->args)
		return (0);
	ft_log_fd(LOG_INFO, STDOUT, "Run expand_variable: cmd: %s\n", cmd->name);
	if (!cmd->mnsh)
	{
		ft_log_fd(LOG_DEBUG, STDOUT,
			"expand_variable: minishell: Internal error: mnsh is NULL\n");
		return (0);
	}
	args = cmd->args;
	i = 0;
	while (args && args[++i])
		args[i] = expand_variable_if_need(i, args[i], cmd);
	if (expand_assignments(cmd->assignments, cmd->mnsh) == -1)
		return (-1);
	if (expand_variable(cmd->redirections, cmd) == -1)
		return (-1);
	ft_log_fd(LOG_INFO, STDOUT, "Finished variable expansion\n");
	return (1);
}
