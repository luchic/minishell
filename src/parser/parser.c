#include "ft_defines.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

t_ast_node	*parse_script(t_tokenstream *ts);
t_ast_node	*parse_logical_node(t_tokenstream *ts);

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
	t_ast_node	*ast_node_subshell;

	if (!ts_expect(ts, PAREN_OPEN))
		return (NULL);
	subshell = ft_calloc(1, sizeof(t_subshell));
	if (!subshell)
		return (NULL);
	subshell->script = parse_script(ts);
	if (!subshell->script)
		return (free(subshell), NULL); // TODO: Change free function
	if (!ts_expect(ts, PAREN_CLOSE))
		return (free(subshell), /* TODO: free AST inside script */ NULL);
	ast_node_subshell = create_ast_node(SUBSHELL);
	if (!ast_node_subshell)
		return (free(subshell), NULL);
	ast_node_subshell->subshell = subshell;
	return (ast_node_subshell);
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


t_ast_node	*parse_logical_left(t_tokenstream *ts)
{
	t_ast_node				*ast_left_node;
	t_ast_node				*ast_cmd_node;
	
	if (ts_match(ts, PAREN_OPEN))
		return (parse_subshell(ts));
	
	ast_cmd_node = parse_pipeline(ts);
	return (ast_cmd_node);
}

t_ast_node	*parse_logical_right(t_tokenstream *ts)
{
		t_ast_node				*ast_right_node;
	t_ast_node					*ast_cmd_node;
	
	if (ts_match(ts, PAREN_OPEN))
		return (parse_subshell(ts));

	ast_cmd_node = parse_logical_node(ts);
	if (!ast_cmd_node)
		return (NULL); // TODO: free l
	return (NULL);
}

t_ast_node	*parse_logical_node(t_tokenstream *ts)
{
	t_ast_node		*script;
	t_ast_node		*left;
	t_ast_node		*right;
	t_logical_expression	*logical;

	if (!is_logical_op_token_in_input(ts))
		return (parse_pipeline(ts));

	t_logical_op op = get_logical_op(ts);
	left = parse_logical_left(ts);
	if (!left)
		return (NULL);
	right = parse_logical_right(ts);
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

t_ast_node	*parse_script(t_tokenstream *ts)
{
	t_ast_node				*ast_node_script;
	t_ast_node				*ast_node;
	t_logical_expression	*logical;

	if (!is_logical_op_token_in_input(ts))
		return (parse_pipeline(ts));

	ast_node = parse_logical_node(ts);
	if (!ast_node)
		return (NULL); // TODO: free left and right nodes
	ast_node_script = create_ast_node(LOGICAL);
	if (!ast_node_script)
		return (NULL);
	ast_node_script->logical = logical;
	return (ast_node_script);
}

t_ast_node	*run_parser(t_list *tokens, char *input)
{
	t_tokenstream	ts;
	t_ast_node	*ast;

	ts.cur = tokens;
	ast = parse_script(&ts);
	return (ast);
}
