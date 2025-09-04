/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:46:46 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/04 13:22:15 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_lexer.h"
#include "ft_printf.h"

t_list	*run_lexer(const char *input)
{
	t_list	*tokens;

	if (!validate_parantheses(input))
		return (ft_printf_fd(STDERR, "minishell: Unmatched parentheses\n"),
			NULL);
	tokens = token_assigment(input);
	if (!tokens)
		return (ft_printf_fd(STDERR, "minishell: Lexer error\n"), NULL);
	
	return (tokens);
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
// 	print_tokens(tokens);
// 	ft_lstclear(&tokens, free_tokens);	
// }

// int	main(void)
// {
// 	t_list *tokens;
// 	// char *input = "(echo 'Hello World' | grep World) && echo \"Done\" >> output.txt";
// 	char *input = "echo 2&&echo 3";
// 	char *input2 = "(echo 1&&echo 2)||(echo 3&&echo 4)";
// 	char *input3 = "echo hello>file&&cat<file||echo fail";
// 	char *input4 = "echo 1;((echo nested||echo test)&&echo done)||grep -v \"hello it is \\\"Nik\\\"\"";

// 	// ft_printf("================= Input 1: =================\n");
// 	// split(input);
// 	// ft_printf("================= Input 2: =================\n");
// 	// split(input2);
// 	// ft_printf("================= Input 3: =================\n");
// 	// split(input3);
// 	ft_printf("================= Input 4: =================\n");
// 	split(input4);


// 	return (0);
// }
