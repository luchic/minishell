/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:46:46 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/02 17:06:19 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_lexer.h"
#include "ft_printf.h"

t_list	*run_lexer(const char *input)
{
	t_list	*tokens;

	if (!validate_paratnes(input))
		return (ft_printf_fd(STDERR, "minishell: Unmatched parentheses\n"),
			NULL);
	tokens = token_assigment(input);
	if (!tokens)
		return (ft_printf_fd(STDERR, "minishell: Lexer error\n"), NULL);
	
	return (tokens);
}
