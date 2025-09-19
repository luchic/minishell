/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 21:38:45 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/19 13:24:15 by mezhang          ###   ########.fr       */
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
	UNBALANCED,
}					t_parse_mode;

typedef enum e_merge_mode
{
	COPY,
	MERGE_WORD,
	MERGE_ASSIGNMENT
}					t_merge_mode;

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
}					t_token_type;

typedef enum e_quote_status
{
	UNQUOTED,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	MIXED_QUOTES
}					t_quote_status;

typedef struct s_token
{
	int				is_space_after;
	t_quote_status	quote_status;
	t_token_type	type;
	char			*value;
}					t_token;

// ======================== Lexer ========================
int					run_lexer(t_list **tokens, const char *input);

// ======================== Tokenizer ========================
char				*get_token(const char **input, t_parse_mode *mode,
						t_quote_status *status);
int					ft_split_tokens(t_list **head, const char *input);
t_token_type		get_token_type(const char *value);
int					token_assignment(t_list **token, const char *input);
// t_list				*merge_word_token(t_list *tokens, const char *input);

// ======================== Utils ========================
int					is_double_char_token(const char *str);
int					is_special_char(char c);
void				free_tokens(void *param);
int					is_double_quote(char c, int *escaped);
void				*add_new_token(t_list **head, char *value,
						t_quote_status quote, const char *input);

#endif
