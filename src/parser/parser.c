#include "ft_defines.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

t_ast_node *_parse(t_tokenstream *ts);

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

t_ast_node *_parse_subshell(t_tokenstream *ts)
{
	t_subshell	*subshell;
	if (!ts_expect(ts, PAREN_OPEN))
		return (NULL);
	t_ast_node *ast_script = _parse(ts);
	if (!ast_script)
		return (NULL);
	if (!ts_expect(ts, PAREN_CLOSE))
		return (NULL);
	subshell = ft_calloc(1, sizeof(t_subshell));
	if (!subshell)
		return (NULL);
	subshell->script = ast_script;
	t_ast_node *ast_node = create_ast_node(SUBSHELL);
	if (!ast_node)
		return (NULL);
	ast_node->subshell = subshell;
	return (ast_node);
}

t_logical_expression *create_logical_node(t_tokenstream *ts, t_ast_node *left)
{
	t_logical_op op;
	t_logical_expression *expr;

	op = get_logical_op(ts);
	if (op == OP_INVALID)
		return (NULL);
	
	return (create_logical_expression(op, left, NULL));
}

t_ast_node *_parse(t_tokenstream *ts)
{
	t_ast_node	*ast_logical;
	t_ast_node 	*ast_simple_left;
	t_ast_node	*ast_simple_right;
	t_logical_expression	*logical;
	
	if (ts_match(ts, PAREN_OPEN))
		ast_simple_left = _parse_subshell(ts);
	else
		ast_simple_left = parse_pipeline(ts);
	if (!ast_simple_left)
		return (NULL);
	while (ts_match(ts, AND) || ts_match(ts, OR))
	{
		logical = create_logical_node(ts, ast_simple_left);
		if (!logical)
			return (NULL);
		ts_advance(ts);
		if (ts_match(ts, PAREN_OPEN)) // consume AND/OR
			ast_simple_right = _parse_subshell(ts);
		else
			ast_simple_right = parse_pipeline(ts);
		if (!ast_simple_right)
			return (NULL);
		logical->right = ast_simple_right;
		ast_simple_left = create_ast_node(LOGICAL);
		if (!ast_simple_left)
			return (NULL);
		ast_simple_left->logical = logical;
	}
	return (ast_simple_left);
}

t_ast_node	*run_parser(t_list *tokens, char *input)
{
	t_tokenstream	ts;
	t_ast_node	*ast;

	ts.cur = tokens;
	ast = _parse(&ts);
	return (ast);
}
// TODO: After assignments can be command.
