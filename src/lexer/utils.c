/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 13:49:24 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/15 20:01:53 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
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

int	is_double_char_token(const char *str)
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
	return ((c == '|' || c == '&' || c == '<' || c == '>' || c == '('
			|| c == ')' || c == ';' || c == '\'' || c == '\"' /* || c == '$'*/
			|| c == '?' /* || c == '=' */));
}

int	is_double_quote(char c, int *escaped)
{
	if (c == '\\' && !*escaped)
		*escaped = 1;
	else if (c == '\"' && !*escaped)
		return (1);
	else
		*escaped = 0;
	return (0);
}

void	*add_new_token(t_list **head, char *value, t_quote_status quote,
		const char *input)
{
	t_list	*new_node;
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	if (*input == ' ' || *input == '\0')
		token->no_space_before = 0;
	else
		token->no_space_before = 1;
	token->quote_status = quote;
	token->value = value;
	new_node = ft_lstnew(token);
	if (!new_node)
		return (NULL);
	ft_lstadd_back(head, new_node);
	return (new_node);
}
