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
		|| c == '?');
}

static char	*get_next_token(char **input, t_parse_mode *mode)
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
	if (!token)
		return (*mode = ERROR, NULL);
	if (*cur_input == '\'')
		*mode = SINGLE;
	else if (*cur_input == '\"')
		*mode = DOUBLE;
	if (*cur_input == '\0')
		*input = cur_input;
	else
		*input = cur_input + 1;
	if (*mode != NORMAL)
		return (free(token), NULL);
	return (token);
}

static char	*get_single_quoted_token(char **input, t_parse_mode *mode)
{
	char	*cur_input;
	char	*token;

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

static char	*get_double_quoted_token(char **input, t_parse_mode *mode)
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
	token = ft_substr(*input, 0, cur_input - *input);
	if (*cur_input == '\"')
		*input = cur_input + 1;
	else
		*input = cur_input;
	*mode = NORMAL;
	return (token);
}

t_list	*ft_split_tokens(char *input)
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

// #include <stdio.h>

// int	main(void)
// {
// 	t_list *tokens;
// 	char *input = "echo 'Hello World' | grep World
// 		&& echo \"Done\" > output.txt";

// 	tokens = fd_split_tokens(input);
// 	while (tokens)
// 	{
// 		printf("Token: %s\n", (char *)tokens->content);
// 		tokens = tokens->next;
// 	}
// 	return (0);
// }