/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:46:46 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/01 20:37:53 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

static char **fd_split_tokens(char *input)
{
    char *copy;

    copy = ft_strdup(input);
    return (copy);
}

static t_token	*create_token(const char *value)
{
    t_token	*token

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    if (ft_strcmp(value, "|") == 0)
        token->type = PIPE;
    else if (ft_strcmp(value, "&&") == 0)
        token->type = AND;
    else if (ft_strcmp(value, "||") == 0)
        token->type = OR;
    else if (ft_strcmp(value, "<") == 0)
        token->type = REDIRECT_IN;
    else if (ft_strcmp(value, ">") == 0)
        token->type = REDIRECT_OUT;
    else if (ft_strcmp(value, ">>") == 0)
        token->type = REDIRECT_APPEND;
    else if (ft_strcmp(value, "<<") == 0)
        token->type = HEREDOC;
    else if (ft_strcmp(value, "(") == 0)
        token->type = PAREN_OPEN;
    else if (ft_strcmp(value, ")") == 0)
        token->type = PAREN_CLOSE;
    else
    {
        token->type = WORD;
        token->value = ft_strdup(value);
        return (token);
    }
    token->value = ft_strdup(value);
    return (token);
}




t_token *get_next_line(char **input)
{
	t_token	*token;

	token = create_token(*input);
	(*input)++;
	return (token);
}

t_list	*lexer(const char *input)
{
	t_list	*tokens;
	t_token	*token;

	tokens = NULL;
	while (*input)
	{
		token = get_next_token(&input);
		if (token)
			ft_lstadd_back(&tokens, ft_lstnew(token));
	}
	return (tokens);
}
