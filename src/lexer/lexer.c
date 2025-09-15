/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:46:46 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/15 21:04:36 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_printf.h"
#include "lexer.h"

int	run_lexer(t_list **tokens, const char *input)
{
	t_list	*head;
	int		exit_code;

	head = NULL;
	ft_log_fd(LOG_INFO, STDERR, "Run lexer\n");
	if (validate_parantheses(input) == SYNTAX_ERROR)
	{
		return (SYNTAX_ERROR);
	}
	exit_code = token_assignment(&head, input);
	if (exit_code == FAIL)
		return (ft_log_fd(LOG_ERROR, STDERR,
				"minishell: Lexer error (token assignment)\n"), FAIL);
	else if (exit_code == SYNTAX_ERROR)
		return (ft_printf("%s: %s: quote\n", PREFIX, UNEXPECTED_TOKEN),
			SYNTAX_ERROR);
	*tokens = head;
	return (0);
}
