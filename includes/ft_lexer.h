/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:46:00 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/01 21:30:54 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEXER_H
# define FT_LEXER_H

# include "libft.h"

typedef enum e_parse_mode
{
    NORMAL,
    DOUBLE,
    SINGLE,
}						t_parse_mode;

typedef enum e_token_type
{
	WORD,
	PIPE,
	AND,
	OR,
	// SEMICOLON,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HEREDOC,
	PAREN_OPEN,
	PAREN_CLOSE,
	EOF // End of File
}						t_token_type;

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
}						t_token;

t_list					*lexer(const char *input);
void					free_tokens(t_token *head);

#endif