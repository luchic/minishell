/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:52:59 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/07 12:44:10 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_printf.h"
#include <stdlib.h>


static int	is_to_merge_mode(t_list *current)
{
	t_token	*cur;
	t_token	*next;

	if (!current || !current->next)
		return (0);
	cur = (t_token *)current->content;
	next = (t_token *)current->next->content;
	if (cur->type == WORD && next->type == WORD)
		return (1);
	return (0);
}

static int	is_to_merge_assignment(t_list *current, const char *input)
{
	t_token	*cur;
	t_token	*next;
	t_token	*next_next;

	if (!current || !current->next || !current->next->next)
		return (0);
	if (*input == ' ')
		return (0);
	if (*(input + 2) == ' ')
		return (0);
	cur = (t_token *)current->content;
	next = (t_token *)current->next->content;
	next_next = (t_token *)current->next->next->content;

	if (cur->type == WORD && next->type == EQUAL && next_next->type == WORD)
		return (1);
	return (0);
}

static int	ft_copy_node(t_list **merged, const t_token *src)
{
	t_list	*new_node;
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (0);
	new_token->type = src->type;
	new_token->value = ft_strdup(src->value);
	if (!new_token->value)
		return (free(new_token), 0);
	new_node = ft_lstnew(new_token);
	if (!new_node)
		return (free(new_token->value), free(new_token), 0);
	ft_lstadd_back(merged, new_node);
	return (1);
}

// NOTE: If token is in qutes ("ARG"=VALUE) it shouldn't be VARIABLE
int	merge_tokens_assignment(t_list **merged, t_list *current, char *input)
{
	t_list	*lst;
	t_token	*last_token;
	t_token	*cur_token;
	char	*new_value;

	if (!ft_copy_node(merged, (t_token *)current->content))
		return (0);
	lst = ft_lstlast(*merged);
	last_token = (t_token *)lst->content;
	new_value = ft_strjoin(last_token->value, "=");
	if (!new_value)
		return (0);
	free(last_token->value);
	last_token->value = new_value;
	current = current->next->next;
	cur_token = (t_token *)current->content;
	new_value = ft_strjoin(last_token->value, cur_token->value);
	if (!new_value)
		return (0);
	free(last_token->value);
	last_token->value = new_value;
	last_token->type = WORD;
	if (*(input - 1) != '\'' && *(input - 1) != '\"')
		last_token->type = VARIABLE;
	return (1);
}

int	merge_tokens(t_list **merged, t_list *current)
{
	t_list	*lst;
	t_token	*last_token;
	t_token	*cur_token;
	char	*new_value;

	lst = ft_lstlast(*merged);
	if (!lst)
		return (ft_copy_node(merged, (t_token *)current->content));
	last_token = (t_token *)lst->content;
	cur_token = (t_token *)current->content;
	new_value = ft_strjoin(last_token->value, cur_token->value);
	if (!new_value)
		return (0);
	free(last_token->value);
	last_token->value = new_value;
	return (1);
}

static void cleanup(t_list **tokens, t_list **merged)
{
	ft_lstclear(merged, free_tokens);
	ft_lstclear(tokens, free_tokens);
}

// NOTE: Merge a assignment tokens (e.g., ARG=VALUE)
// It can cause errors if i get "HELLO"=WORLD
t_list	*merge_word_token(t_list *tokens, const char *input)
{
	char			*tmp;
	t_list			*current;
	t_list			*merged;
	t_token			*token;
	t_merge_mode	mode;

	current = tokens;
	merged = NULL;
	if (!current)
		return (NULL);
	mode = COPY;
	while (current)
	{
		token = (t_token *)current->content;
		tmp = ft_strstr(input, token->value);
		if (!tmp)
			return (ft_lstclear(&tokens, free_tokens), NULL);
		tmp += ft_strlen(token->value);
		if (*tmp == '\'' || *tmp == '\"')
			tmp++;

		if (is_to_merge_assignment(current, tmp))
			mode = MERGE_ASSIGNMENT;
		if (mode == COPY)
		{
			if (!ft_copy_node(&merged, token))
				return (cleanup(&tokens, &merged), NULL);
		}
		else if (mode == MERGE_WORD)
		{
			if (!merge_tokens(&merged, current))
				return (cleanup(&tokens, &merged), NULL);
		}
		else if (mode == MERGE_ASSIGNMENT)
		{
			if (!merge_tokens_assignment(&merged, current, tmp))
				return (cleanup(&tokens, &merged), NULL);
			current = current->next->next;
		}
		if (*tmp != ' ' && is_to_merge_mode(current))
			mode = MERGE_WORD;
		else
			mode = COPY;
		input = tmp;
		current = current->next;
	}
	return (merged);
}
