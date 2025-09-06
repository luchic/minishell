#include "ft_lexer.h"

static t_token_type	get_type_redirection(const char *value)
{
	if (ft_strcmp(value, "<") == 0)
		return (REDIRECT_IN);
	else if (ft_strcmp(value, ">") == 0)
		return (REDIRECT_OUT);
	else if (ft_strcmp(value, ">>") == 0)
		return (REDIRECT_APPEND);
	else if (ft_strcmp(value, "<<") == 0)
		return (HEREDOC);
	return (WORD);
}

t_token_type	get_token_type(const char *value)
{
	if (ft_strcmp(value, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(value, "$?") == 0)
		return (EXIT_STATUS);
	else if (ft_strcmp(value, "=") == 0)
		return (EQUAL);
	else if (ft_strcmp(value, "&") == 0)
		return (AMPERSAND);
	else if (ft_strcmp(value, "&&") == 0)
		return (AND);
	else if (ft_strcmp(value, "||") == 0)
		return (OR);
	else if (!ft_strcmp(value, "<") || !ft_strcmp(value, ">")
		|| !ft_strcmp(value, ">>") || !ft_strcmp(value, "<<"))
		return (get_type_redirection(value));
	else if (ft_strcmp(value, "(") == 0)
		return (PAREN_OPEN);
	else if (ft_strcmp(value, ")") == 0)
		return (PAREN_CLOSE);
	else if (ft_strcmp(value, ";") == 0)
		return (SEMICOLON);
	return (WORD);
}
