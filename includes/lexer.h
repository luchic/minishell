/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 21:38:45 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/12 21:38:50 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

typedef enum e_parse_mode
{
	NORMAL,
	DOUBLE,
	SINGLE,
	ERROR,
}						t_parse_mode;

typedef enum e_merge_mode
{
	COPY,
	MERGE_WORD,
	MERGE_ASSIGNMENT
}			t_merge_mode;


typedef enum e_token_type
{
	WORD,
	PIPE,
	AND,
	OR,
	EXIT_STATUS,
	EQUAL,
	AMPERSAND,
	SEMICOLON,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HEREDOC,
	PAREN_OPEN,
	PAREN_CLOSE,
	VARIABLE
}						t_token_type;

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
}						t_token;

// ======================== Lexer ========================
t_list					*run_lexer(const char *input);

// ======================== Tokenizer ========================
t_list					*ft_split_tokens(const char *input);
t_token_type			get_token_type(const char *value);
t_list					*token_assigment(const char *input);
t_list					*merge_word_token(t_list *tokens, const char *input);

// ======================== Utils ========================
int						is_doble_char_token(const char *str);
int						is_special_char(char c);
void					free_tokens(void *param);

// ======================== Validator ========================
int						validate_parantheses(const char *input);

#endif
