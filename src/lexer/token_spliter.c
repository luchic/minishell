#include "ft_lexer.h"
#include "libft.h"
#include <stdlib.h>

/** Special tokens to handle;
( )

| ||

& &&

< <<

> >>

;
*/

int	is_doble_char_token(const char *str)
{
	return (str[0] == str[1] && (str[0] == '|' || str[0] == '&' || str[0] == '<'
			|| str[0] == '>'));
}

int	is_special_char(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>' || c == '(' || c == ')'
		|| c == ';' || c == ' ' || c == '\'' || c == '\"');
}

char	*get_next_line(char **input, t_parse_mode *mode)
{
	char	*cur_input;
	char	*token;

	if (!*input || !**input)
		return (NULL);
	cur_input = *input;
	while (*cur_input && !is_special_char(*cur_input))
		cur_input++;
	if (is_doble_char_token(cur_input))
		cur_input++;
	token = ft_substr(*input, 0, cur_input - *input + 1);
	if (*cur_input == '\'')
		*mode = SINGLE;
	else if (*cur_input == '\"')
		*mode = DOUBLE;
	*input = cur_input + 1;
	return (token);
}

char	*get_single_quoted_token(char **input, t_parse_mode *mode)
{
	char	*cur_input;
	char	*token;

	if (!*input || !**input)
		return (NULL);
	cur_input = *input;
	while (*cur_input && *cur_input != '\'')
		cur_input++;
	token = ft_substr(*input, 0, cur_input - *input + 1);
	if (*cur_input == '\'')
		*input = cur_input + 1;
	else
		*input = cur_input;
	*mode = NORMAL;
	return (token);
}

char	*get_double_quoted_token(char **input, t_parse_mode *mode)
{
	char	*cur_input;
	char	*token;

	if (!*input || !**input)
		return (NULL);
	cur_input = *input;
	while (*cur_input)
	{
		if ((*cur_input == '\"' && *(cur_input - 1) != '\\'))
			break ;
		cur_input++;
	}
	token = ft_substr(*input, 0, cur_input - *input + 1);
	if (*cur_input == '\"')
		*input = cur_input + 1;
	else
		*input = cur_input;
	*mode = NORMAL;
	return (token);
}

t_list	*fd_split_tokens(char *input)
{
	t_list *head;
	char *token;
	t_parse_mode mode;

	head = NULL;
	token = NULL;
	mode = NORMAL;
	while (*input)
	{
		if (mode == NORMAL)
			token = get_next_token(&input, &mode);
		else if (mode == SINGLE)
			token = get_single_quoted_token(&input, &mode);
		else if (mode == DOUBLE)
			token = get_double_quoted_token(&input, &mode);
		if (token)
		{
			ft_lstadd_back(&head, ft_lstnew(token));
			token = NULL;
		}
		else
		{
			ft_lstclear(&head, free);
			return (NULL);
		}
	}
	return (head);
}

int main()
{
	t_list *tokens;
	char *input = "echo 'Hello World' | grep World && echo \"Done\"";

	tokens = fd_split_tokens(input);
	while (tokens)
	{
		printf("Token: %s\n", (char *)tokens->content);
		tokens = tokens->next;
	}
	return 0;
}