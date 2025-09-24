/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 23:23:00 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/24 14:57:53 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_printf.h"
#include "lexer.h"
#include "libft.h"
#include <stdlib.h>

char	*get_special_char_token(const char **input, t_parse_mode *mode)
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

char	*get_next_token(const char **input, t_parse_mode *mode,
		t_quote_status *status)
{
	const char	*cur_input;
	char		*token;

	if (!*input || !**input)
		return (NULL);
	skip_ifs_spaces(input);
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
	while (*cur_input && !is_special_char(*cur_input)
		&& !is_ifs_space(*cur_input))
		cur_input++;
	token = ft_substr(*input, 0, cur_input - *input);
	if (!token)
		return (*mode = ERROR, NULL);
	*input = cur_input;
	return (token);
}

char	*get_single_quoted_token(const char **input, t_parse_mode *mode,
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

char	*get_double_quoted_token(const char **input, t_parse_mode *mode,
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

char	*get_token(const char **input, t_parse_mode *mode,
		t_quote_status *status)
{
	char	*token;

	token = NULL;
	if (*mode == NORMAL)
		token = get_next_token(input, mode, status);
	else if (*mode == SINGLE)
		token = get_single_quoted_token(input, mode, status);
	else if (*mode == DOUBLE)
		token = get_double_quoted_token(input, mode, status);
	return (token);
}
