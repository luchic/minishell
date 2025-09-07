/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 13:49:24 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/07 13:49:25 by nluchini         ###   ########.fr       */
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
