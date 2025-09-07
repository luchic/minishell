#include "ft_defines.h"
#include "lexer.h"
#include "parser.h"
#include <stdlib.h>

int	is_redirection_token(t_tokenstream *ts)
{
	if (ts_match(ts, REDIRECT_IN) || ts_match(ts, REDIRECT_OUT) || ts_match(ts,
			REDIRECT_APPEND) || ts_match(ts, HEREDOC))
		return (1);
	return (0);
}

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
	redir->next = NULL;
	redir->next = *lst;
	*lst = redir;
	return (redir);
}

int	cmd_set_redirection(t_command *cmd, t_tokenstream *ts)
{
	t_token	*redir_token;
	void	*redir;

	if (!is_redirection_token(ts))
		return (0);
	redir_token = ts_advance(ts);
	if (!ts_match(ts, WORD))
		return (0);
	if (redir_token->type == REDIRECT_IN)
		redir = create_redirection(&cmd->redirections, REDIR_INPUT,
				ts_advance(ts)->value);
	else if (redir_token->type == REDIRECT_OUT)
		redir = create_redirection(&cmd->redirections, REDIR_OUTPUT,
				ts_advance(ts)->value);
	else if (redir_token->type == REDIRECT_APPEND)
		redir = create_redirection(&cmd->redirections, REDIR_APPEND,
				ts_advance(ts)->value);
	else if (redir_token->type == HEREDOC)
		redir = create_redirection(&cmd->redirections, REDIR_HEREDOC,
				ts_advance(ts)->value);
	if (!redir)
		return (0);
	return (1);
}
