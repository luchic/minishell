
#include "ft_defines.h"
#include "lexer.h"
#include "parser.h"

static int	update_arg_value(int size, char **res, t_list **expander,
		t_token *token)
{
	char	*pos;
	int		exit_status;

	if (ft_append_str(res, token->value) == -1)
		return (-1);
	pos = ft_strchr_not_escaped(token->value, '$');
	while (pos)
	{
		if (handle_var(size, pos, token, expander) == -1)
			return (-1);
		pos = ft_strchr_not_escaped(pos + 1, '$');
	}
	pos = ft_strchr_not_escaped(token->value, '*');
	while (pos)
	{
		if (handle_wildcard(pos - token->value + size, res, token,
				is_single_quoted) == -1)
			return (-1);
		size++;
		pos = ft_strchr_not_escaped(pos + 1, '*');
	}
	return (1);
}

static char	*get_merged_value(t_tokenstream *ts, t_list **node)
{
	char	*merged_value;
	t_token	*token;
	int		size;

	merged_value = NULL;
	size = 0;
	token = ts_peek(ts);
	if (update_arg_value(size, &merged_value, node, token) == -1)
		return (free(merged_value), NULL);
	while (ts_match(ts, WORD))
	{
		token = ts_peek(ts);
		if (!token || token->is_space_after)
			return (ts_advance(ts), merged_value);
		ts_advance(ts);
		token = ts_peek(ts);
		if (!token)
			break ;
		size = ft_strlen(merged_value);
		if (update_arg_value(size, &merged_value, node, token) == -1)
			return (free(merged_value), NULL);
		if (token->is_space_after)
			break ;
	}
	return (merged_value);
}

//===========================================================
//
//===========================================================
static int	set_cmd_expander(t_command *cmd, t_list **expander, int index)
{
	t_cmd_expander	*node;

	if (!expander || !*expander)
		return (1);
	node = ft_calloc(1, sizeof(t_cmd_expander));
	if (!node)
		return (0);
	node->index = index;
	node->expand = *expander;
	*expander = NULL;
	ft_lstadd_back(&cmd->expander, ft_lstnew(node));
	return (1);
}

static int	set_command_args(t_command *cmd, t_tokenstream *ts)
{
	int		argc;
	t_list	*expander;
	t_token	*arg;

	argc = 0;
	expander = NULL;
	while (ts_match(ts, WORD))
	{
		if (realloc_args(cmd, argc + 1) == 0)
			return (0);
		cmd->args[argc++] = get_merged_value(ts, &expander);
		if (!cmd->args[argc - 1])
			return (ft_log_fd(LOG_ERROR, STDERR, "Failed to merge tokens\n"),
				ft_lstclear(&expander, free_expander), 0);
		if (!set_cmd_expander(cmd, &expander, argc - 1))
			return (ft_lstclear(&expander, free_expander), 0);
		if (!set_redirection(cmd, ts))
			return (0);
	}
	if (!realloc_args(cmd, argc + 1))
		return (0);
	cmd->args[argc] = NULL;
	if (!set_redirection(cmd, ts))
		return (0);
	return (1);
}

static int	parse_command_fields(t_command *command, t_tokenstream *ts,
		t_minishell *mnsh)
{
	t_token	*tok_name;

	command->mnsh = mnsh;
	if (create_assignments(ts, &command->assignments) == -1)
		return (0);
	if (!set_redirection(command, ts))
		return (0);
	if (!ts_match(ts, WORD))
		return (msg_unexpected_token(ts_peek(ts)), 0);
	tok_name = ts_peek(ts);
	command->name = ft_strdup(tok_name->value);
	if (!command->name)
		return (0);
	if (!set_command_args(command, ts))
		return (ft_log_fd(LOG_ERROR, STDERR,
				"Failed to set command arguments\n"), 0);
	if (!set_redirection(command, ts))
		return (0);
	return (1);
}

t_ast_node	*parse_simple_command(t_tokenstream *ts, t_minishell *mnsh)
{
	t_command	*command;
	t_ast_node	*ast_node;

	ft_log_fd(LOG_INFO, STDOUT, "Parse simple command\n");
	command = create_command(CMD_EXTERNAL);
	if (!command)
		return (ft_log_fd(LOG_ERROR, STDERR,
				"Parse simple command: create_command failed\n"), NULL);
	if (!parse_command_fields(command, ts, mnsh))
		return (ft_log_fd(LOG_ERROR, STDERR,
				"Parse simple command: parse_command_fields failed\n"),
			free_cmd(command), NULL);
	ast_node = create_ast_node(COMMAND);
	if (!ast_node)
		return (ft_log_fd(LOG_ERROR, STDERR,
				"Parse simple command: create_ast_node failed\n"),
			free_cmd(command), NULL);
	if (is_built_in(command->name))
		command->type = CMD_BUILTIN;
	return (ast_node->command = command, ast_node);
}
