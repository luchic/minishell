#include "ft_lexer.h"
#include <stdlib.h>

// TODO: Where I should handle variables assigments like ARG=value

static t_token	*get_next_token(char *str_token)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(str_token);
	token->type = get_token_type(str_token);
	return (token);
}

t_list	*token_assigment(char *input)
{
	t_list	*head;
	t_list	*new_node;
	t_list	*splits;
	t_token	*token;

	head = NULL;
	splits = ft_split_tokens(input);
	while (splits)
	{
		token = get_next_token((char *)splits->content);
		if (!token)
			return (ft_lstclear(splits, free), ft_lstclear(head, free_tokens),
				NULL);
		new_node = ft_lstnew(token);
		if (!new_node)
			return (free_tokens(token), ft_lstclear(splits, free),
				ft_lstclear(head, free_tokens), NULL);
		ft_lstadd_back(&head, new_node);
		splits = splits->next;
	}
	return (head);
}
