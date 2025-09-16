/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:41:08 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/16 18:53:23 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ft_common.h"
#include <stdlib.h>

static int is_variable_name(char *name)
{
	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	name++;
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}

int	is_assignment(t_tokenstream *ts)
{
	t_tokenstream	*clone;
	t_token			*token;

	clone = ts_clone(ts);
	if (!clone)
		return (0);
	token = ts_advance(clone);
	if (!token || token->type != WORD || token->quote_status != UNQUOTED
		|| token->is_space_after)
		return (ts_free(clone), 0);
	if (!is_variable_name(token->value))
		return (ts_free(clone), 0);
	token = ts_advance(clone);
	if (!token || token->type != WORD || ft_strcmp(token->value, "=") != 0
		|| token->quote_status != UNQUOTED)
		return (ts_free(clone), 0);
	ts_free(clone);
	return (1);
}

//==============================================================================
//==============================================================================
//==============================================================================

static int	get_assignment_if_exist(t_command *cmd, t_tokenstream *ts)
{
	t_tokenstream	*clone;

	if (!ts_match(ts, WORD))
		return (0);
	clone = ts_clone(ts);
	if (!clone)
		return (-1);
	return (1);
}

static t_assignment *allocate_assignment(void) 
{
	t_assignment	*assignment;

	assignment = ft_calloc(1, sizeof(t_assignment));
	return (assignment);
}


static int add_var_expander(int size, char *begin, char *var_end, t_token *token, t_assignment *assignment)
{
	t_list		*new_node;
	t_expander	*var_exp;

	var_exp = ft_calloc(1, sizeof(t_expander));
	if (!var_exp)
		return (-1);
	new_node = ft_lstnew(var_exp);
	if (!new_node)
		return (free(var_exp), -1);
	var_exp->type = VAR;
	var_exp->var = ft_calloc(1, sizeof(t_var_expand));
	if (!var_exp->var)
		return (free(var_exp), free(new_node), -1);
	var_exp->var->var_name = ft_substr(begin, 1, var_end - begin - 1);
	if (!var_exp->var->var_name)
		return (free(var_exp->var), free(var_exp), free(new_node), -1);
	var_exp->var->var_start = size + (begin - token->value);
	var_exp->var->var_end = size + (var_end - token->value) - 1;
	ft_lstadd_back(&assignment->expand, new_node);
	return (1);
}

static int handle_var(int size, char *var_pos, t_token *token, t_assignment *assignment)
{
	char	*var_end;

	var_end = var_pos + 1;
	if (!var_end || *var_end == '\0')
		return (0);
	if (*var_end == '?')
	{
		if (add_var_expander(size, var_pos, var_end, token, assignment) == -1)
			return (-1);
		return (1);
	}
	if ((!ft_isalpha(*var_end) && *var_end != '_'))
		return (0);
	while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
		var_end++;
	
	if (add_var_expander(size, var_pos, var_end, token, assignment) == -1)
		return (-1);
	return (1);
}

static int handle_expander_if_need(int size, char **res, t_token *token, t_assignment *assignment)
{
	char *value;
	char *var_pos;
	if (token->quote_status == SINGLE_QUOTED)
		return (0);
	value = token->value;
	if (!value)
		return (0);
	var_pos = ft_strchr_not_escaped(value, '$');
	while (var_pos)
	{
		if (handle_var(size, var_pos, token, assignment) == -1)
			return (-1);
		var_pos = ft_strchr_not_escaped(var_pos + 1, '$');
	}
	return (1);
}
static t_assignment	*get_construct_assignment_value(char *value,
		t_tokenstream *ts)
{
	t_token			*token;
	t_assignment	*assignment;
	char			*res;
	int 			size;

	if (value == NULL)
		return (NULL);
	assignment = allocate_assignment();
	if (!assignment)
		return (NULL);
	res = NULL;
	if (ft_append_str(&res, value) == -1)
		return (NULL);
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
		if (ft_append_str(&res, token->value) == -1)
			return (free(res), NULL);
		if (handle_expander_if_need(size, &res, token, assignment) == -1)
			return (free(res), free_assignment(assignment), NULL); // TODO: free assignment
	}
	assignment->value = res;
	return (assignment);
}

static char	*ft_copy_until_equal(t_tokenstream *ts)
{
	t_token	*token;
	char	*res;
	char	*tmp;

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

t_list	*create_assignments_node(t_tokenstream *ts)
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

t_list	*create_assignments(t_tokenstream *ts)
{
	t_list	*head;
	t_list	*node;

	if (!is_assignment(ts))
		return (NULL);
	ft_log_fd(LOG_INFO, STDERR, "Create assignments\n");
	head = NULL;
	while (is_assignment(ts))
	{
		node = create_assignments_node(ts);
		if (!node)
		{
			ft_log_fd(LOG_ERROR, STDERR,
				"Create assignments: create_assignments_node failed\n");
			return (ft_lstclear(&head, free), NULL);
		}
		ft_lstadd_back(&head, node);
	}
	return (head);
}

// #include "lexer.h"
// #include "ft_printf.h"
// #include "ft_common.h"


// void print_assignments(t_list *assignments)
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
// 			continue;
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

// int main(int argc, char **argv)
// {
// 	char *input;
// 	if (argc != 2)
// 		input = ft_strdup("ARG1=h$t?");
// 	else
// 		input = ft_strdup(argv[1]);

// 	t_list *tokens = NULL;
// 	int exit_code = run_lexer(&tokens, input);
// 	if (exit_code)
// 	{
// 		printf("Lexer error: %d\n", exit_code);
// 		return 1;
// 	}
// 	// t_list *current = tokens;
// 	// while (current)
// 	// {
// 	// 	t_token *token = (t_token *)current->content;
// 	// 	printf("Token: >%s<, Is space after: %d\n", token->value, token->is_space_after);
// 	// 	current = current->next;
// 	// }

// 	t_tokenstream ts;
// 	ts.cur = tokens;
// 	// char * value;
// 	// value = ft_copy_until_equal(&ts);
// 	// ft_printf_fd(STDOUT, "Var name = : >%s<\n", value);
	
// 	t_list *assignments = create_assignments(&ts);
// 	ft_lstclear(&tokens, free_tokens);
// 	if (!assignments)
// 	{
// 		printf("No assignments found or error occurred\n");
// 		return 1;
// 	}
// 	print_assignments(assignments);
// 	ft_lstclear(&assignments, free_assignment);
// 	// free(value);
	
// 	return 0;
// }