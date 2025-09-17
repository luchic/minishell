/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:46:46 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/16 15:07:26 by nluchini         ###   ########.fr       */
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

// #include <stdio.h>
// #include <stdlib.h>
// int main(int argc, char **argv)
// {
// 	char *input;
// 	if (argc < 2)
// 	{
// 		input = ft_strdup("echo 2&&echo 3||grep");
// 	}
// 	else
// 	{
// 		input = ft_strdup(argv[1]);
// 	}
// 	t_list *tokens = NULL;
// 	int exit_code = run_lexer(&tokens, input);
// 	free(input);
// 	if (exit_code)
// 	{
// 		printf("Lexer error: %d\n", exit_code);
// 		return 1;
// 	}
// 	t_list *current = tokens;
// 	while (current)
// 	{
// 		t_token *token = (t_token *)current->content;
// 		printf("Token: >%s<, Quote_status: %d\n", token->value,
// 			token->quote_status);
// 		current = current->next;
// 	}
// 	ft_lstclear(&tokens, free_tokens);
// }