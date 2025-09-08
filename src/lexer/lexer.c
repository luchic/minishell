/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:46:46 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/07 13:49:15 by nluchini         ###   ########.fr       */
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

// #include <stdio.h>
// #include <stdlib.h>

// void print_tokens(t_list *tokens)
// {
// 	while (tokens)
// 	{
// 		ft_printf("Token: %s\n", ((t_token *)tokens->content)->value);
// 		tokens = tokens->next;
// 	}
// }

// void split(char *input)
// {
// 	t_list	*tokens;

// 	tokens = run_lexer(input);
// 	if (!tokens)
// 	{
// 		ft_printf("Lexer error\n");
// 		return ;
// 	}
// 	print_tokens(tokens);
// 	ft_lstclear(&tokens, free_tokens);
// }

// int	main(int argc, char **argv)
// {

// 	// t_list *tokens;
// 	// char *input = "(echo 'Hello World' | grep World)
		&& echo \"Done\" >> output.txt";
// 	char *input = "ARG=HELLo && TMP=WORLD";
// 	// char *input2 = "(echo 1&&echo 2)||(echo 3&&echo 4)";
// 	// char *input3 = "echo hello>file&&cat<file||echo fail";
// 	// char *input4 = "echo 1;((echo nested||echo test)&&echo done)||grep
		-v \"hello it is \\\"Nik\\\"\"";

// 	// ft_printf("================= Input 1: =================\n");
// 	split(input);
// 	// ft_printf("================= Input 2: =================\n");
// 	// split(input2);
// 	// ft_printf("================= Input 3: =================\n");
// 	// split(input3);
// 	// ft_printf("================= Input 4: =================\n");
// 	// split(input4);

// 	return (0);
// }
