/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __main__.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:00:58 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/21 13:59:24 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "expander.h"
#include <readline/history.h>
#include <readline/readline.h>

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


void	init_minishell(t_minishell *mnsh, int argc, char **argv, char **envp)
{
	int	i;
	int	size;

	(void)argc;
	(void)argv;

	ft_memset(mnsh, 0, sizeof(t_minishell));
	size = count_args(envp);
	mnsh->envp = ft_calloc((size + 1), sizeof(char *));
	if (!mnsh->envp)
		return ;
	for (i = 0; envp[i]; i++)
	{
		mnsh->envp[i] = ft_strdup(envp[i]);
		if (!mnsh->envp[i])
			return ;
	}
	mnsh->envp[i] = NULL;
	mnsh->script = ft_calloc(1, sizeof(t_script));
	if (!mnsh->script)
		return ;
}

int set_script(t_minishell *mnsh, t_ast_node *script)
{
	if (!mnsh || !script)
		return (-1);
	if (!mnsh->script)
		return (-1);
	mnsh->script->nodes = script;
	mnsh->script->count = 0; // TODO: set correct count
	return (0);
}


// TODO: handle minishell> kkjhg execve: No such file or directory
// TODO: change error messages to match bash ones

void tmp_expander(t_ast_node *node)
{	
	ft_log_fd(LOG_DEBUG, STDERR,
		"tmp_expander: Expanding node type: %d\n", node->type);
	if (!node)
		return ;
	if (node->type == COMMAND && node->command)
	{	
		if (run_variable_expander(node->command) == -1)
		{
			ft_log_fd(LOG_ERROR, STDERR, "Variable expander error\n");
			return ;
		}
		if (run_wildcards_expander(node->command) == -1)
		{
			ft_log_fd(LOG_ERROR, STDERR, "Wildcards expander error\n");
			return ;
		}
	}
	else if (node->type == PIPELINE && node->pipeline)
	{
		for (int i = 0; i < node->pipeline->count; i++)
			tmp_expander(node->pipeline->commands[i]);
	}
	else if (node->type == SUBSHELL && node->subshell)
	{
		tmp_expander(node->subshell->script);
	}
	else if (node->type == LOGICAL && node->logical)
	{
		tmp_expander(node->logical->left);
		tmp_expander(node->logical->right);
	}
}


void	ft_run_minishell(t_minishell *mnsh, int argc, char **argv, char **envp)
{
	char		*input;
	int 		 exit_code;
	t_list		*tokens;
	t_ast_node	*ast;

	(void)argc;
	(void)argv;
	(void)envp;
	while ((input = readline("minishell> ")))
	{
		// if (!input)
		// 	continue;
		// if (input && input[0] == '\0')
		// {
		// 	free(input);
		// 	continue ;
		// }
		if (ft_strcmp(input, "echo $?") == 0)
		{	
			add_history(input);
			ft_printf_fd(STDOUT, "exit status: %d\n", mnsh->last_exit_status);
			free(input);
			continue ;
		}
		exit_code = run_lexer(&tokens, input);
		if (exit_code)
		{	
			ft_log_fd(LOG_INFO, STDERR, "Lexer failed: %d\n", exit_code);
			ft_log_fd(LOG_INFO, STDERR, "Exit code: %d\n", mnsh->last_exit_status);
			add_history(input);
			free(input);
			continue ;
		}
		ast = run_parser(tokens, mnsh);
		if (!ast)
		{
			ft_log_fd(LOG_ERROR, STDERR, "Parser error\n");
			ft_log_fd(LOG_INFO, STDERR, "Exit code: %d\n", mnsh->last_exit_status);
			add_history(input);
			free(input);
			ft_lstclear(&tokens, free_tokens);
			continue ;
			// return ;
		}
		
		// print_node(ast);
		
		if (set_script(mnsh, ast) == -1)
		{
			ft_printf_fd(STDERR, "Set script error\n");
			free(input);
			ft_lstclear(&tokens, free_tokens);
			free_ast_tree(ast);
			continue ;
			// return ;
		}

		ft_lstclear(&tokens, free_tokens);
		add_history(input);
		free(input);
		// print_node(ast);
		mnsh->last_exit_status = run_executor(mnsh);
		free_ast_tree(ast);
	}
	rl_clear_history();
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_minishell mnsh;
// 	char *input;
// 	if (argc != 2)
// 		input = ft_strdup("ls | cat -e");
// 	else
// 		input = ft_strdup(argv[1]);
// 	init_minishell(&mnsh, argc, argv, envp);

// 	t_list		*tokens;
// 	t_ast_node	*ast;
// 	int exit_code;

// 	exit_code = run_lexer(&tokens, input);
// 	if (exit_code)
// 	{	
// 		ft_log_fd(LOG_INFO, STDERR, "Lexer failed: %d\n", exit_code);
// 		free(input);
// 		return 1;
// 	}
// 	ast = run_parser(tokens, &mnsh);
// 	if (!ast)
// 	{
// 		ft_log_fd(LOG_ERROR, STDERR, "Parser error\n");
// 		free(input);
// 		ft_lstclear(&tokens, free_tokens);
// 		return 1;
// 	}
// 	// print_node(ast);
// 	// print_node(ast);
// 	mnsh.script->nodes = ast;
// 	mnsh.last_exit_status = run_executor(&mnsh);
// 	print_node(ast);
// 	tmp_expander(ast);
// 	ft_printf("\nAfter expansion:\n");
// 	print_node(ast);
// 	ft_lstclear(&tokens, free_tokens);
// 	free(input);
// 	free_stack_minishell(&mnsh);
// }

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mnsh;

	init_minishell(&mnsh, argc, argv, envp);
	// init_signal_handler();
	ft_run_minishell(&mnsh, argc, argv, envp);
	return (0);
}
