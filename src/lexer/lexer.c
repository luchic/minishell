/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:46:46 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/09 12:19:17 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_printf.h"
#include "lexer.h"

t_list	*run_lexer(const char *input)
{
	t_list	*tokens;
	t_list	*merged;

	if (!validate_parantheses(input))
		return (ft_printf_fd(STDERR, "minishell: Unmatched parentheses\n"),
			NULL);
	tokens = token_assigment(input);
	if (!tokens)
		return (ft_printf_fd(STDERR,
				"minishell: Lexer error (token assignment)\n"), NULL);
	merged = merge_word_token(tokens, input);
	if (!merged)
		return (ft_printf_fd(STDERR, "minishell: Lexer error (merge)\n"), NULL);
	ft_lstclear(&tokens, free_tokens);
	return (merged);
}
