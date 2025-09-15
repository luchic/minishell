/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_spliter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:22:20 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/15 20:22:34 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_defines.h"
#include <stdlib.h>

/** Special tokens to handle;
( )

| ||

& &&

< <<

> >>

;
*/

static char	*get_special_char_token(const char **input, t_parse_mode *mode)
{
	const char	*cur_input;
	char		*token;

	if (!*input || !**input)
		return (NULL);
	cur_input = *input;
	if (is_double_char_token(cur_input))
	{
		token = ft_substr(*input, 0, 2);
		*input += 2;
	}
	else if (is_special_char(*cur_input))
	{
		token = ft_substr(*input, 0, 1);
		*input += 1;
	}
	else
		return (NULL);
	if (!token)
		return (*mode = ERROR, NULL);
	return (token);
}

static char	*get_next_token(const char **input, t_parse_mode *mode,
		t_quote_status *status)
{
	const char	*cur_input;
	char		*token;

	if (!*input || !**input)
		return (NULL);
	while (**input == ' ')
		(*input)++;
	if (!**input)
		return (NULL);
	cur_input = *input;
	*status = UNQUOTED;
	if (*cur_input == '\'')
		return (*mode = SINGLE, NULL);
	else if (*cur_input == '\"')
		return (*mode = DOUBLE, NULL);
	if (is_special_char(*cur_input))
		return (get_special_char_token(input, mode));
	while (*cur_input && !is_special_char(*cur_input) && *cur_input != ' ')
		cur_input++;
	token = ft_substr(*input, 0, cur_input - *input);
	if (!token)
		return (*mode = ERROR, NULL);
	*input = cur_input;
	return (token);
}

static char	*get_single_quoted_token(const char **input, t_parse_mode *mode,
		t_quote_status *status)
{
	const char	*cur_input;
	const char	*start;
	char		*token;

	if (!*input || !**input)
		return (NULL);
	start = *input + 1;
	cur_input = start;
	while (*cur_input && *cur_input != '\'')
		cur_input++;
	if (*cur_input != '\'')
		return (*mode = UNBALANCED, NULL);
	token = ft_substr(start, 0, cur_input - start);
	if (!token)
		return (*mode = ERROR, NULL);
	*input = cur_input + 1;
	*status = SINGLE_QUOTED;
	*mode = NORMAL;
	return (token);
}

static char	*get_double_quoted_token(const char **input, t_parse_mode *mode,
		t_quote_status *status)
{
	const char	*cur_input;
	const char	*start;
	char		*token;
	int			escaped;

	if (!*input || !**input)
		return (NULL);
	start = *input + 1;
	cur_input = start;
	escaped = 0;
	while (*cur_input)
	{
		if (is_double_quote(*cur_input, &escaped))
			break ;
		cur_input++;
	}
	if (*cur_input != '\"')
		return (*mode = UNBALANCED, NULL);
	token = ft_substr(start, 0, cur_input - start);
	if (!token)
		return (*mode = ERROR, NULL);
	*input = cur_input + 1;
	*status = DOUBLE_QUOTED;
	*mode = NORMAL;
	return (token);
}

int	ft_split_tokens(t_list **head, const char *input)
{
	char			*token;
	t_parse_mode	mode;
	t_quote_status	quote;

	token = NULL;
	mode = NORMAL;
	while (*input)
	{
		if (mode == NORMAL)
			token = get_next_token(&input, &mode, &quote);
		else if (mode == SINGLE)
			token = get_single_quoted_token(&input, &mode, &quote);
		else if (mode == DOUBLE)
			token = get_double_quoted_token(&input, &mode, &quote);
		else if (mode == ERROR)
			return (ft_lstclear(head, free_tokens), FAIL);
		if (token && !add_new_token(head, token, quote, input))
			return (free(token), ft_lstclear(head, free_tokens), FAIL);
		if (mode == UNBALANCED)
			return (ft_printf_fd(STDERR, "%s: %s\n", PREFIX, UNBALANCED_QUOTES),
				ft_lstclear(head, free_tokens), SYNTAX_ERROR);
	}
	return (0);
}

// #include <stdio.h>

// int main()
// {
// 	const char *input = "echo 2&&echo 3||grep";
// 	t_list *tokens = NULL;
// 	ft_split_tokens(&tokens, input);
// 	t_list *current = tokens;

// 	t_token *token;
// 	if (!tokens)
// 	{
// 		printf("Lexer error\n");
// 		return 1;
// 	}
// 	while (current)
// 	{
// 		token = (t_token *)current->content;
// 		printf("Token: >%s<, Quote_status: %d\n", token->value,
// token->quote_status);
// 		current = current->next;
// 	}

// 	ft_lstclear(&tokens, free_tokens);
// 	return 0;

// }