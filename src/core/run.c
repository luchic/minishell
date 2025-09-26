/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 18:57:38 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/26 11:39:50 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "ft_executor.h"
#include <readline/readline.h>
#include <readline/history.h>

void print_expander(t_list *expander)
{
	t_list		*current;
	t_expander	*exp;

	current = expander;
	while (current)
	{
		if (current->content == NULL)
		{
			printf("NULL content in expander list\n");
			current = current->next;
			continue ;
		}
		exp = (t_expander *)current->content;
		if (!exp)
		{
			printf("NULL expander\n");
			current = current->next;
			continue ;
		}
		if (exp->var_name)
			printf("  Var expander: name: %s, start: %d, end: %d\n",
				exp->var_name, exp->var_start, exp->var_end);
		else
			printf("  Var expander: NULL var_name\n");
		current = current->next;
	}
}

void print_cmd_expander(t_list *cmd_exp)
{
	if (!cmd_exp)
	{
		printf("NULL cmd_expander\n");
		return ;
	}
	t_cmd_expander *expander;
	while (cmd_exp)
	{
		expander = (t_cmd_expander *)cmd_exp->content;
		if (expander)
		{
			printf("  Command Expander [%d]:\n", expander->index);
			print_expander(expander->expand);
		}
		else
		{
			printf("  NULL command expander\n");
		}
		cmd_exp = cmd_exp->next;
	}
}

void print_command(t_command *cmd)
{
	if (!cmd)
	{
		printf("NULL command\n");
		return ;
	}
	printf("Command: %s\n", cmd->name ? cmd->name : "NULL");
	if (cmd->args)
	{
		printf("Arguments:\n");
		for (int i = 0; cmd->args[i]; i++)
			printf("  arg[%d]: %s\n", i, cmd->args[i]);
	}
	else
	{
		printf("No arguments\n");
	}
	if (cmd->redirections)
	{
		printf("Redirections:\n");
		t_list *redir = cmd->redirections;
		while (redir)
		{
			t_redirection *r = (t_redirection *)redir->content;
			if (r)
			{
				printf("  Type: %d, Value: %s\n", r->type, r->value ? r->value : "NULL");
			}
			else
			{
				printf("  NULL redirection\n");
			}
			print_expander(r->expander);
			redir = redir->next;
		}
	}
	else
	{
		printf("No redirections\n");
	}
	if (cmd->assignments)
	{
		printf("Assignments:\n");
		t_list *assign = cmd->assignments;
		while (assign)
		{
			t_assignment *a = (t_assignment *)assign->content;
			if (a)
			{
				printf("  Value: %s\n", a->value ? a->value : "NULL");
			}
			else
			{
				printf("  NULL assignment\n");
			}
			print_expander(a->expand);
			assign = assign->next;
		}
	}
	else
	{
		printf("No assignments\n");
	}
	if (cmd->expander)
	{
		printf("Command Expander:\n");
		print_cmd_expander(cmd->expander);
	}
	else
	{
		printf("No command expander\n");
	}
}

void print_node(t_ast_node *node)
{
	if (!node)
	{
		printf("NULL node\n");
		return ;
	}
	if (node->type == COMMAND && node->command)
	{
		print_command(node->command);
	}
	else if (node->type == PIPELINE && node->pipeline)
	{
		printf("Pipeline with %d commands\n", node->pipeline->count);
		for (int i = 0; i < node->pipeline->count; i++)
		{
			printf(" Command %d:\n", i);
			print_node(node->pipeline->commands[i]);
		}
	}
	else if (node->type == SUBSHELL && node->subshell)
	{
		printf("Subshell\n");
		print_node(node->subshell->script);
	}
	else if (node->type == LOGICAL && node->logical)
	{
		printf("Logical Expression: %d\n", node->logical->op);
		printf(" Left:\n");
		print_node(node->logical->left);
		printf(" Right:\n");
		print_node(node->logical->right);
	}
	else
	{
		printf("Unknown node type or NULL content\n");
	}
}

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
