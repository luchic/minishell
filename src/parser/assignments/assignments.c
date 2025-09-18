/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:41:08 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/18 19:52:30 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "parser.h"
#include <stdlib.h>

static int	ft_fetch_value(char *value, t_tokenstream *ts,
		t_assignment *assignment)
{
	int		size;
	char	*res;
	t_token	*token;

	res = NULL;
	if (ft_append_str(&res, value) == -1)
		return (-1);
	while (ts_match(ts, WORD))
	{
		token = ts_peek(ts);
		if (!token || token->is_space_after)
			return (assignment->value = res, ts_advance(ts), 0);
		ts_advance(ts);
		token = ts_peek(ts);
		if (!token || !ts_match(ts, WORD))
			break ;
		size = ft_strlen(res);
		if (ft_append_str(&res, token->value) == -1)
			return (free(res), -1);
		if (handle_expander_if_need(size, token, assignment) == -1)
			return (free(res), -1);
	}
	assignment->value = res;
	return (0);
}

static t_assignment	*get_construct_assignment_value(char *value,
		t_tokenstream *ts)
{
	t_assignment	*assignment;

	if (value == NULL)
		return (NULL);
	assignment = allocate_assignment();
	if (!assignment)
		return (NULL);
	if (ft_fetch_value(value, ts, assignment) == -1)
		return (free_assignment(assignment), NULL);
	return (assignment);
}

static char	*ft_copy_until_equal(t_tokenstream *ts)
{
	t_token	*token;
	char	*res;

	token = ts_peek(ts);
	if (!token || token->type != WORD)
		return (NULL);
	res = ft_strdup(token->value);
	if (!res)
		return (NULL);
	ts_advance(ts);
	token = ts_peek(ts);
	if (!token || token->type != WORD || ft_strcmp(token->value, "=") != 0)
		return (free(res), NULL);
	if (ft_append_str(&res, token->value) == -1)
		return (free(res), NULL);
	return (res);
}

static t_list	*create_assignments_node(t_tokenstream *ts)
{
	t_list			*node;
	t_token			*token;
	t_assignment	*assignment;
	char			*value;

	value = ft_copy_until_equal(ts);
	if (!value)
		return (NULL);
	while (ts_match(ts, WORD))
	{
		token = ts_peek(ts);
		if (!token || token->is_space_after)
			break ;
		assignment = get_construct_assignment_value(value, ts);
	}
	node = ft_lstnew(assignment);
	free(value);
	return (node);
}

int	create_assignments(t_tokenstream *ts, t_list **asgmt)
{
	t_list	*node;

	if (!is_assignment(ts))
		return (0);
	ft_log_fd(LOG_INFO, STDERR, "Create assignments\n");
	while (is_assignment(ts))
	{
		node = create_assignments_node(ts);
		if (!node)
		{
			ft_log_fd(LOG_ERROR, STDERR,
				"Create assignments: create_assignments_node failed\n");
			return (ft_lstclear(asgmt, free_assignment), -1);
		}
		ft_lstadd_back(asgmt, node);
	}
	return (0);
}

// #include "ft_common.h"
// #include "ft_printf.h"
// #include "lexer.h"

// void	print_assignments(t_list *assignments)
// {
// 	t_list			*current;
// 	t_list			*exp_cur;
// 	t_assignment	*assignment;
// 	t_expander		*exp;
// 	t_var_expand	*var;

// 	current = assignments;
// 	while (current)
// 	{
// 		assignment = (t_assignment *)current->content;
// 		if (!assignment)
// 		{
// 			printf("NULL assignment\n");
// 			current = current->next;
// 			continue ;
// 		}
// 		printf("Assignment value: >%s<\n", assignment->value);
// 		exp_cur = assignment->expand;
// 		while (exp_cur)
// 		{
// 			exp = (t_expander *)exp_cur->content;
// 			if (exp->type == VAR)
// 			{
// 				var = exp->var;
// 				if (var)
// 					printf("  Var expander: name: %s, start: %d, end: %d\n",
// 						var->var_name, var->var_start, var->var_end);
// 				else
// 					printf("  Var expander: NULL var\n");
// 			}
// 			else
// 				printf("  Unknown expander type\n");
// 			exp_cur = exp_cur->next;
// 		}
// 		current = current->next;
// 	}
// }

// int	main(int argc, char **argv)
// {
// 	char *input;
// 	if (argc != 2)
// 		input = ft_strdup("ARG1= h$t?");
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

// 	t_list *assignments = create_assignments(&ts);
// 	ft_lstclear(&tokens, free_tokens);
// 	if (!assignments)
// 	{
// 		printf("No assignments found or error occurred\n");
// 		return (1);
// 	}
// 	print_assignments(assignments);
// 	ft_lstclear(&assignments, free_assignment);
// 	// free(value);

// 	return (0);
// }