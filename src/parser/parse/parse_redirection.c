/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:39:04 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/08 13:21:00 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "lexer.h"
#include "parser.h"
#include <stdlib.h>

static void	*create_redirection(t_redirection **lst, t_redir_type type,
		const char *value)
{
	t_redirection	*redir;

	redir = ft_calloc(1, sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->value = ft_strdup(value);
	if (!redir->value)
		return (free(redir), NULL);
	redir->next = *lst;
	*lst = redir;
	return (redir);
}

int	cmd_set_redirection(t_command *cmd, t_tokenstream *ts)
{
	t_token	*redir_token;
	t_token	*word_token;
	void	*redir;

	if (!is_redirection_token(ts))
		return (0);
	redir_token = ts_advance(ts);
	if (!ts_match(ts, WORD))
		return (0);
	word_token = ts_advance(ts);
	if (redir_token->type == REDIRECT_IN)
		redir = create_redirection(&cmd->redirections, REDIR_INPUT,
				word_token->value);
	else if (redir_token->type == REDIRECT_OUT)
		redir = create_redirection(&cmd->redirections, REDIR_OUTPUT,
				word_token->value);
	else if (redir_token->type == REDIRECT_APPEND)
		redir = create_redirection(&cmd->redirections, REDIR_APPEND,
				word_token->value);
	else if (redir_token->type == HEREDOC)
		redir = create_redirection(&cmd->redirections, REDIR_HEREDOC,
				word_token->value);
	if (!redir)
		return (0);
	return (1);
}
