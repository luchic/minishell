/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 18:57:38 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/26 11:44:39 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "ft_executor.h"
#include <readline/readline.h>
#include <readline/history.h>

int	parse(char *input, t_minishell *mnsh)
{
	t_list		*tokens;
	t_ast_node	*ast;
	int			tmp;

	tmp = run_lexer(&tokens, input);
	if (tmp)
	{
		ft_log_fd(LOG_ERROR, STDERR, "Lexer error\n");
		set_exit_code(mnsh, tmp);
		return (-1);
	}
	ast = run_parser(tokens, mnsh);
	mnsh->script->nodes = ast;
	ft_lstclear(&tokens, free_tokens);
	if (mnsh->last_exit_status == SYNTAX_ERROR && !ast)
	{
		ft_log_fd(LOG_ERROR, STDERR, "Parser error\n");
		return (-1);
	}
	return (0);
}

void	execute(t_minishell *mnsh)
{
	int	exec_code;

	if (!mnsh->script)
		exec_code = execute_node(mnsh, NULL);
	else
		exec_code = execute_node(mnsh, mnsh->script->nodes);
	mnsh->last_exit_status = exec_code;
	free_ast_tree(mnsh->script->nodes);
	mnsh->script->nodes = NULL;
}

int	run_loop(t_minishell *mnsh)
{
	char	*input;

	input = ft_read_line(mnsh);
	while (input)
	{
		mnsh->is_running = 1;
		if (mnsh->is_tty_in)
			add_history(input);
		if (parse(input, mnsh) == -1)
		{
			free(input);
			input = ft_read_line(mnsh);
			continue ;
		}
		free(input);
		execute(mnsh);
		mnsh->is_running = 0;
		input = ft_read_line(mnsh);
	}
	if (mnsh->is_tty_in)
		rl_clear_history();
	free_stack_minishell(mnsh);
	return (mnsh->last_exit_status);
}
