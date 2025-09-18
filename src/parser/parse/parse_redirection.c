
#include "ft_common.h"
#include "lexer.h"
#include "parser.h"
#include <stdlib.h>

static int	update_redirection_value(int size, char **res, t_redirection *redir,
		t_token *token)
{
	char	*pos;
	int		exit_status;

	if (ft_append_str(res, token->value) == -1)
		return (-1);
	pos = ft_strchr_not_escaped(token->value, '$');
	while (pos)
	{
		exit_status = handle_var(size, pos, token, &redir->expander);
		if (exit_status == -1)
			return (-1);
		pos = ft_strchr_not_escaped(pos + 1, '$');
	}
	pos = ft_strchr_not_escaped(token->value, '*');
	while (pos)
	{
		if (handle_wildcard(pos - token->value + size, res, token,
				is_single_quoted) == -1)
			return (-1);
		pos = ft_strchr_not_escaped(pos + 1, '*');
	}
	return (1);
}

static int	set_redirection_value(t_redirection *redir, t_tokenstream *ts)
{
	t_token	*token;
	char	*res;
	int		size;

	token = ts_peek(ts);
	if (!token)
		return (0);
	res = NULL;
	size = 0;
	if (update_redirection_value(size, &res, redir, token) == -1)
		return (free(res), -1);
	while (ts_match(ts, WORD))
	{
		token = ts_peek(ts);
		if (!token || token->is_space_after)
			break ;
		ts_advance(ts);
		token = ts_peek(ts);
		if (!token)
			break ;
		size = ft_strlen(res);
		if (update_redirection_value(size, &res, redir, token) == -1)
			return (free(res), -1);
	}
	return (redir->value = res, 1);
}

static void	*create_redirection(t_list **lst, t_redir_type type,
		t_tokenstream *ts)
{
	t_redirection	*redir;
	t_list			*new_node;

	redir = ft_calloc(1, sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = type;
	if (!set_redirection_value(redir, ts))
		return (free(redir), NULL);
	new_node = ft_lstnew(redir);
	if (!new_node)
		return (free(redir->value), free(redir), NULL);
	ft_lstadd_front(lst, new_node);
	return (redir);
}

int	cmd_set_redirection(t_command *cmd, t_tokenstream *ts)
{

	t_token	*redir_token = NULL;
	// t_token	*word_token;
	void	*redir = NULL;

	if (!is_redirection_token(ts))
		return (msg_unexpected_token(ts_peek(ts)), SYNTAX_ERROR);
	redir = NULL;
	redir_token = ts_advance(ts);
	if (!ts_match(ts, WORD))
		return (msg_unexpected_token(ts_peek(ts)), SYNTAX_ERROR);
	if (redir_token->type == REDIRECT_IN)
		redir = create_redirection(&cmd->redirections, REDIR_INPUT, ts);
	else if (redir_token->type == REDIRECT_OUT)
		redir = create_redirection(&cmd->redirections, REDIR_OUTPUT, ts);
	else if (redir_token->type == REDIRECT_APPEND)
		redir = create_redirection(&cmd->redirections, REDIR_APPEND, ts);
	else if (redir_token->type == HEREDOC)
		redir = create_redirection(&cmd->redirections, REDIR_HEREDOC, ts);
	if (!redir)
		return (0);
	return (1);
}

// #include "ft_printf.h"
// #include <stdio.h>

// void	print_wildcard(char *str)
// {
// 	char	*pos;

// 	pos = ft_strchr_not_escaped(str, '*');
// 	if (!pos)
// 	{
// 		printf("No wildcards found in string: >%s<\n", str);
// 		return ;
// 	}
// 	while (pos)
// 	{
// 		printf("Wildcard at position: %ld\n", pos - str);
// 		pos = ft_strchr_not_escaped(pos + 1, '*');
// 	}
// }

// void	print_expander(t_list *expander)
// {
// 	t_list		*current;
// 	t_expander	*exp;

// 	current = expander;
// 	while (current)
// 	{
// 		if (current->content == NULL)
// 		{
// 			printf("NULL content in expander list\n");
// 			current = current->next;
// 			continue ;
// 		}
// 		exp = (t_expander *)current->content;
// 		if (!exp)
// 		{
// 			printf("NULL expander\n");
// 			current = current->next;
// 			continue ;
// 		}
// 		if (exp->var_name)
// 			printf("  Var expander: name: %s, start: %d, end: %d\n",
// 				exp->var_name, exp->var_start, exp->var_end);
// 		else
// 			printf("  Var expander: NULL var_name\n");
// 		current = current->next;
// 	}
// }

// void	pirnt_redirection(t_command *cmd)
// {
// 	t_list			*current;
// 	t_redirection	*redir;

// 	current = cmd->redirections;
// 	while (current)
// 	{
// 		redir = (t_redirection *)current->content;
// 		if (!redir)
// 		{
// 			printf("NULL redirection\n");
// 			current = current->next;
// 			continue ;
// 		}
// 		printf("Redirection type: %d, value: >%s<\n", redir->type,
// 			redir->value);
// 		print_expander(redir->expander);
// 		print_wildcard(redir->value);
// 		current = current->next;
// 	}
// }

// int	main(int argc, char **argv)
// {
// 	char *input;
// 	t_command cmd;
// 	ft_bzero(&cmd, sizeof(t_command));
// 	if (argc != 2)
// 		input = ft_strdup("< END'*'");
// 	else
// 		input = ft_strdup(argv[1]);

// 	t_list *tokens = NULL;
// 	int exit_code = run_lexer(&tokens, input);
// 	if (exit_code)
// 	{
// 		printf("Lexer error: %d\n", exit_code);
// 		return (1);
// 	}

// 	t_tokenstream ts;
// 	ts.cur = tokens;

// 	if (!cmd_set_redirection(&cmd, &ts))
// 	{
// 		ft_lstclear(&tokens, free_tokens);
// 		printf("Failed to set redirections\n");
// 		return (1);
// 	}
// 	ft_lstclear(&tokens, free_tokens);
// 	pirnt_redirection(&cmd);
// 	ft_lstclear(&cmd.redirections, ft_free_redir);
// 	// free(value);

// 	return (0);
// }
