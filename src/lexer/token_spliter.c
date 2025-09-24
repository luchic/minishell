/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_spliter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:22:20 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/24 14:58:25 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_printf.h"
#include "lexer.h"
#include "libft.h"
#include <stdlib.h>

int	ft_split_tokens(t_list **head, const char *input)
{
	char			*token;
	t_parse_mode	mode;
	t_quote_status	quote;

	token = NULL;
	mode = NORMAL;
	while (*input)
	{
		if (mode == NORMAL || mode == SINGLE || mode == DOUBLE)
			token = get_token(&input, &mode, &quote);
		if (mode == ERROR)
			return (ft_lstclear(head, free_tokens), FAIL);
		else if (mode == UNBALANCED)
		{
			if (token)
				free(token);
			return (ft_lstclear(head, free_tokens), SYNTAX_ERROR);
		}
		if (token)
		{
			if (!add_new_token(head, token, quote, input))
				return (free(token), ft_lstclear(head, free_tokens), FAIL);
		}
	}
	return (0);
}
