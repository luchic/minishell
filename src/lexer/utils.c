#include "ft_lexer.h"
#include <stdlib.h>

void	free_tokens(void *param)
{
	t_token	*token;

	token = (t_token *)param;
	if (token)
	{
		if (token->value)
			free(token->value);
		free(token);
	}
}

int	is_doble_char_token(const char *str)
{
	if (!str || !str[0] || !str[1])
		return (0);
	if (str[0] == '$' && str[1] == '?')
		return (1);
	return (str[0] == str[1] && (str[0] == '|' || str[0] == '&' || str[0] == '<'
			|| str[0] == '>'));
}

int	is_special_char(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>' || c == '(' || c == ')'
		|| c == ';' || c == ' ' || c == '\'' || c == '\"' || c == '$'
		|| c == '?' || c == '=');
}
