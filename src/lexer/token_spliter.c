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

static char	*get_next_token(const char **input, t_parse_mode *mode)
{
	const char	*cur_input;
	char		*token;

	if (!*input || !**input)
		return (NULL);
	cur_input = *input;
	while (*cur_input && !is_special_char(*cur_input))
		cur_input++;
	if (is_doble_char_token(cur_input) && cur_input == *input)
		cur_input += 2;
	if (cur_input == *input)
		token = ft_substr(*input, 0, cur_input - *input + 1);
	else 
		token = ft_substr(*input, 0, cur_input - *input);
	if (!token)
		return (*mode = ERROR, NULL);
	if (*cur_input == '\'')
		*mode = SINGLE;
	else if (*cur_input == '\"')
		*mode = DOUBLE;
	if (*cur_input == '\'' || *cur_input == '\"' || cur_input == *input )
		*input = cur_input + 1;
	else
		*input = cur_input;
	if (*mode != NORMAL)
		return (free(token), NULL);
	return (token);
}

static char	*get_single_quoted_token(const char **input, t_parse_mode *mode)
{
	const char	*cur_input;
	char		*token;

	if (!*input || !**input)
		return (NULL);
	cur_input = *input;
	while (*cur_input && *cur_input != '\'')
		cur_input++;
	token = ft_substr(*input, 0, cur_input - *input);
	if (*cur_input == '\'')
		*input = cur_input + 1;
	else
		*input = cur_input;
	*mode = NORMAL;
	return (token);
}

static char	*get_double_quoted_token(const char **input, t_parse_mode *mode)
{
	const char	*cur_input;
	char		*token;
	int i;

	if (!*input || !**input)
		return (NULL);
	cur_input = *input;
	while (*cur_input)
	{
		if ((*cur_input == '\"' && *(cur_input - 1) != '\\'))
			break ;
		cur_input++;
	}
	token = ft_substr(*input, 0, cur_input - *input);
	i = -1;
	while (token && token[++i])
		if (token[i] == '\\' && (token[i + 1] == '\"'))
			ft_memmove(&token[i], &token[i + 1], ft_strlen(&token[i + 1]) + 1);
	if (*cur_input == '\"')
		*input = cur_input + 1;
	else
		*input = cur_input;
	*mode = NORMAL;
	return (token);
}

t_list	*ft_split_tokens(const char *input)
{
	t_list			*head;
	char			*token;
	t_parse_mode	mode;

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
		else if (mode == ERROR)
			return (ft_lstclear(&head, free), NULL);
		if (token)
			ft_lstadd_back(&head, ft_lstnew(token));
		if (*input == ' ')
			input++;
	}
	return (head);
}
