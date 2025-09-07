#include "ft_defines.h"
#include "ft_lexer.h"
#include "ft_parser.h"
#include <stdio.h>
#include <stdlib.h>

int	set_redirection(t_command *cmd, t_tokenstream *ts)
{
	while (is_redirection_token(ts))
	{
		if (!cmd_set_redirection(cmd, ts))
			return (0);
	}
	return (1);
}

t_ast_node	*parse_simple_command(t_tokenstream *ts)
{
	t_command	*command;
	t_ast_node	*ast_node;
	int			argc;
	t_token		*token;
	t_token		*tok_name;
	t_token		*arg;

	argc = 0;
	// VAR=value as a standalone assignment command
	if (ts_match(ts, VARIABLE))
	{
		return (create_assignments_node(ts));
	}
	command = create_command(CMD_EXTERNAL);
	if (!command)
		return (NULL);
	// Allow leading redirections before command word
	if (!set_redirection(command, ts))
		return (free_cmd(command), NULL);
	// Require a command WORD
	if (!ts_match(ts, WORD))
		return (free_cmd(command), NULL);
	tok_name = ts_peek(ts);
	command->name = ft_strdup(tok_name->value);
	if (!command->name)
		return (free_cmd(command), NULL);
	while (ts_match(ts, WORD))
	{
		arg = ts_advance(ts);
		command->args = ft_realloc(command->args, sizeof(char *) * argc, sizeof(char *) * (argc + 1));
		if (!command->args)
			return (free_cmd(command), NULL);
		command->args[argc++] = ft_strdup(arg->value);
		if (!command->args[argc - 1])
			return (free_cmd(command), NULL);
	}
	command->args = ft_realloc(command->args, sizeof(char *) * argc, sizeof(char *) * (argc + 1));
	if (!command->args)
		return (free_cmd(command), NULL);
	command->args[argc] = NULL;
	if (!set_redirection(command, ts))
		return (free_cmd(command), NULL);
	ast_node = create_ast_node(COMMAND);
	if (!ast_node)
		return (free_cmd(command), NULL);
	ast_node->command = command;
	return (ast_node);
}

t_ast_node	*parse_pipeline(t_tokenstream *ts)
{
	t_pipeline	*pipeline;
	t_ast_node	*ast_node_pipeline;
	t_ast_node	*ast_node_cmd;

	ast_node_cmd = parse_simple_command(ts);
	if (!ast_node_cmd)
		return (NULL);
	if (!ts_match(ts, PIPE))
		return (ast_node_cmd);
	pipeline = ft_calloc(1, sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->count = 0; // TODO: Check on memory leaks
	pipeline->commands = ft_realloc(pipeline->commands, sizeof(t_ast_node *) * pipeline->count,
			sizeof(t_ast_node *) * (pipeline->count + 1));
	pipeline->commands[pipeline->count++] = ast_node_cmd;
	while (ts_expect(ts, PIPE))
	{
		ast_node_cmd = parse_simple_command(ts);
		if (!ast_node_cmd)
			return (NULL);
		pipeline->commands = ft_realloc(pipeline->commands, sizeof(t_ast_node *) * pipeline->count,
				sizeof(t_ast_node *) * (pipeline->count + 1));
		pipeline->commands[pipeline->count++] = ast_node_cmd;
	}
	ast_node_pipeline = create_ast_node(PIPELINE);
	if (!ast_node_pipeline)
		return (NULL);
	ast_node_pipeline->pipeline = pipeline;
	return (ast_node_pipeline);
}

static t_ast_node	*parse_sequence(t_tokenstream *ts)
{
	return (parse_pipeline(ts));
}

t_ast_node	*parse_subshell(t_tokenstream *ts)
{
	t_subshell	*subshell;
	t_ast_node	*node;

	if (!ts_expect(ts, PAREN_OPEN))
		return (NULL);
	subshell = ft_calloc(1, sizeof(t_subshell));
	if (!subshell)
		return (NULL);
	// Subshell is a full sequence, not only a pipeline
	subshell->script = parse_sequence(ts);
	if (!subshell->script)
		return (free(subshell), NULL); // TODO: Change free function
	if (!ts_expect(ts, PAREN_CLOSE))
		return (free(subshell), /* TODO: free AST inside script */ NULL);
	// create_ast_node takes a single type; set payload
	node = create_ast_node(SUBSHELL);
	if (!node)
		return (free(subshell), NULL);
	node->subshell = subshell;
	return (node);
}

int	is_logical_op_token_in_input(t_tokenstream *ts)
{
	t_tokenstream	*clone;

	clone = ts_clone(ts);
	while (ts_peek(clone))
	{
		if (ts_match(clone, AND) || ts_match(clone, OR))
		{
			ts_free(clone);
			return (1);
		}
		ts_advance(clone);
	}
	ts_free(clone);
	return (0);
}

t_ast_node	*parse_logical_expression(t_tokenstream *ts)
{
	// t_ast_node			*left;
	// t_ast_node			*right;
	// t_logical_expression	*logical;
	// t_logical_op		op;

	// left = parse_pipeline(ts);
	// if (!left)
	// 	return (NULL);
	// if (!ts_match(ts, AND) && !ts_match(ts, OR))
	// 	return (left);
	// logical = ft_calloc(1, sizeof(t_logical_expression));
	// if (!logical)
	// 	return (NULL);
	// logical->left = left;
	// while (ts_match(ts, AND) || ts_match(ts, OR))
	// {
	// 	if (ts_match(ts, AND))
	// 		op = LOGICAL_AND;
	// 	else
	// 		op = LOGICAL_OR;
	// 	ts_advance(ts); // consume AND/OR
	// 	right = parse_pipeline(ts);
	// 	if (!right)
	// 		return (/* TODO: free logical */ NULL);
	// 	logical->op = op;
	// 	logical->right = right;
	// 	left = create_ast_node(LOGICAL);
	// 	if (!left)
	// 		return (/* TODO: free logical */ NULL);
	// 	left->logical = logical;
	// 	logical = ft_calloc(1, sizeof(t_logical_expression));
	// 	if (!logical)
	// 		return (/* TODO: free left AST */ NULL);
	// 	logical->left = left;
	// }
	// free(logical); // Last allocated but not used
	// return (left);
	return (NULL);
}

t_logical_op get_logical_op(t_tokenstream *ts)
{
	t_tokenstream	*clone;

	clone = ts_clone(ts);
	while (ts_peek(clone))
	{
		if (ts_match(clone, AND))
		{
			ts_free(clone);
			return (OP_AND);
		}
		if (ts_match(clone, OR))
		{
			ts_free(clone);
			return (OP_OR);
		}
		ts_advance(clone);
	}
	ts_free(clone);
	return (OP_INVALID); // Invalid
}



t_ast_node	*parse_script(t_tokenstream *ts)
{
	t_ast_node		*script;
	t_ast_node		*left;
	t_ast_node		*right;
	t_logical_expression	*logical;

	if (!is_logical_op_token_in_input(ts))
		return (parse_pipeline(ts));

	t_logical_op op = get_logical_op(ts);
	left = parse_logical_expression(ts);
	if (!left)
		return (NULL);
	right = parse_logical_expression(ts);
	if (!right)
		return (NULL);
	logical = create_logical_expression(op, left, right);
	if (!logical)
		return (NULL);
	script = create_ast_node(LOGICAL);
	if (!script)
		return (NULL);
	script->logical = logical;
	return (script);
}


t_ast_node	*run_parser(t_list *tokens, char *input)
{
	t_tokenstream	ts;
	t_ast_node	*ast;

	ts.cur = tokens;
	ast = parse_script(&ts);
	return (ast);
}

void print_tokens(t_list *tokens)
{
	while (tokens)
	{
		printf("Token: %s\n", ((t_token *)tokens->content)->value);
		tokens = tokens->next;
	}
}

void print_ast_tree(t_ast_node *node)
{
	if (!node)
		return;
	if (node->type == COMMAND)
	{
		t_command *cmd = node->command;
		if (cmd)
		{
			if (cmd->type == CMD_ASSIGNMENT)
			{
				printf("Assignment Command:\n");
				t_list *assign = cmd->assignments;
				while (assign)
				{
					printf("  - %s\n", (char *)assign->content);
					assign = assign->next;
				}
				return;
			}
			printf("Command: %s\n", cmd->name);
			if (cmd->args)
			{
				printf("Arguments:\n");
				for (int i = 0; cmd->args[i]; i++)
					printf("  - %s\n", cmd->args[i]);
			}
			else
			{
				printf("No arguments\n");
			}
			t_redirection *redir = cmd->redirections;
			if (!redir)
			{
				printf("No redirections\n");
			}
			else
			{
				printf("Redirections:\n");
				while (redir)
				{
					printf("  - %s\n", redir->value);
					redir = redir->next;
				}
			}
		}
	}
	else if (node->type == PIPELINE)
	{
		t_pipeline *pipeline = node->pipeline;
		if (pipeline && pipeline->commands)
		{
			printf("Pipeline with %d commands:\n", pipeline->count);
			for (int i = 0; i < pipeline->count; i++)
			{
				print_ast_tree(pipeline->commands[i]);
			}
		}
	}
	else if (node->type == LOGICAL)
	{
		t_logical_expression *logical = node->logical;
		if (logical)
		{
			printf("Logical Expression: %s\n",
				   logical->op == OP_AND ? "AND" : "OR");
			printf("Left:\n");
			print_ast_tree(logical->left);
			printf("Right:\n");
			print_ast_tree(logical->right);
		}
	}
	else if (node->type == SUBSHELL)
	{
		t_subshell *subshell = node->subshell;
		if (subshell && subshell->script)
		{
			printf("Subshell:\n");
			print_ast_tree(subshell->script);
		}
	}
}

int	main(int argc, char **argv)
{
	char *input;

	// input = "< infile echo hello > outfile | grep h | wc -l";
	input = "ARG=\"Hello world\" HEllO=42";
	t_list *tokens = run_lexer(input);
	print_tokens(tokens);

	t_ast_node *ast = run_parser(tokens, input);

	print_ast_tree(ast);

	return (0);
}