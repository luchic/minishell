/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wld_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:24:23 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/24 15:24:31 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_internal.h"
#include "parser.h"

void	restore_str(char *str)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
	{
		if (str[i] == SENTINEL)
			str[i] = '*';
	}
	release_escaped_char(str, '$');
	release_escaped_char(str, '\\');
}

void	restore_str_array(char **args)
{
	int	i;

	if (!args)
		return ;
	i = -1;
	while (args[++i])
		restore_str(args[i]);
}

void	restore_values(t_command *cmd)
{
	t_list			*cur;
	t_redirection	*redir;
	t_assignment	*asgmt;

	restore_str_array(cmd->args);
	cur = cmd->redirections;
	while (cur)
	{
		redir = (t_redirection *)cur->content;
		if (redir)
			restore_str(redir->value);
		cur = cur->next;
	}
	cur = cmd->assignments;
	while (cur)
	{
		asgmt = (t_assignment *)cur->content;
		if (asgmt)
			restore_str(asgmt->value);
		cur = cur->next;
	}
}

void	set_status(int *status, int new_status)
{
	if (status)
		*status = new_status;
}

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
