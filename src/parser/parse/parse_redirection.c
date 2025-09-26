/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:02:20 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/26 18:17:09 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "lexer.h"
#include "parser.h"
#include <stdlib.h>

static t_redir_type	get_redir_type(t_token_type type)
{
	if (type == REDIRECT_IN)
		return (REDIR_INPUT);
	else if (type == REDIRECT_OUT)
		return (REDIR_OUTPUT);
	else if (type == REDIRECT_APPEND)
		return (REDIR_APPEND);
	else if (type == HEREDOC)
		return (REDIR_HEREDOC);
	return (-1);
}

static void	set_quoted_status(t_redirection *redir, t_tokenstream *ts)
{
	t_token			*token;
	t_tokenstream	*copy;

	if (!redir || !ts || redir->type != REDIR_HEREDOC)
		return ;
	copy = ts_clone(ts);
	while (ts_match(copy, WORD))
	{
		token = ts_peek(copy);
		if (token && token->quote_status != UNQUOTED)
		{
			redir->is_quoted = 1;
			break ;
		}
		if (token->is_space_after)
			break ;
		ts_advance(copy);
	}
	ts_free(copy);
}

static void	*create_redirection(t_list **lst, t_token_type type,
		t_tokenstream *ts)
{
	t_redirection	*redir;
	t_list			*new_node;

	redir = ft_calloc(1, sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = get_redir_type(type);
	set_quoted_status(redir, ts);
	if (set_merged_value(&redir->value, &redir->expander, ts) == -1)
		return (ft_free_redir(redir), NULL);
	new_node = ft_lstnew(redir);
	if (!new_node)
		return (ft_free_redir(redir), NULL);
	ft_lstadd_back(lst, new_node);
	return (redir);
}

int	cmd_set_redirection(t_command *cmd, t_tokenstream *ts)
{
	t_token	*token;
	void	*redir;

	if (!is_redirection_token(ts))
		return (msg_unexpected_token(ts_peek(ts)), SYNTAX_ERROR);
	redir = NULL;
	token = ts_advance(ts);
	if (!ts_match(ts, WORD))
		return (msg_unexpected_token(ts_peek(ts)), SYNTAX_ERROR);
	redir = create_redirection(&cmd->redirections, token->type, ts);
	if (!redir)
		return (0);
	return (1);
}
