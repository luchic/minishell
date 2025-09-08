/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 12:55:44 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/07 12:55:45 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_PARSER_H
# define FT_PARSER_H

# include "ft_defines.h"
# include "lexer.h"

typedef struct s_tokenstream
{
	t_list				*cur;
}						t_tokenstream;

// ======================== Token stream ========================
t_token					*ts_peek(t_tokenstream *ts);
t_token					*ts_advance(t_tokenstream *ts);
int						ts_match(t_tokenstream *ts, t_token_type type);
int						ts_expect(t_tokenstream *ts, t_token_type type);
t_tokenstream			*ts_clone(t_tokenstream *src);
void					ts_free(t_tokenstream *ts);

// ======================== AST Nodes ========================
t_ast_node				*create_ast_node(t_node_type type);
t_command				*create_command(t_cmd_type type);
t_ast_node				*create_assignments_node(t_tokenstream *ts);
int						is_redirection_token(t_tokenstream *ts);
int						cmd_set_redirection(t_command *cmd, t_tokenstream *ts);

// ======================== t_command ========================
void					free_cmd(t_command *cmd);

// ======================== Nodes ========================
t_logical_expression	*create_logical_expression(t_logical_op op,
							t_ast_node *left, t_ast_node *right);
// ======================== Parser ========================
t_ast_node				*run_parser(t_list *tokens, char *input);

#endif