/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 12:55:44 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/23 21:22:12 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ft_common.h"
# include "ft_defines.h"
# include "lexer.h"

# define SENTINEL '\x07'

typedef struct s_tokenstream
{
	t_list				*cur;
}						t_tokenstream;

typedef struct s_var_handle
{
	int					size;
	char				*begin;
	char				*var_end;
}						t_var_handle;

typedef struct s_exp_info
{
	int					size;
	char				*res;
	t_list				**expand;
}						t_exp_info;

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
// t_list					*create_assignments_node(t_tokenstream *ts);
int						is_redirection_token(t_tokenstream *ts);
int						cmd_set_redirection(t_command *cmd, t_tokenstream *ts);

// ======================== Nodes ========================
t_logical_expression	*create_logical_expression(t_logical_op op,
							t_ast_node *left, t_ast_node *right);
// ======================== Parser ========================
/**
 * @note Not clean tokens after parsing.
 */
t_ast_node				*run_parser(t_list *tokens, t_minishell *mnsh);
t_ast_node				*parse_simple_command(t_tokenstream *ts,
							t_minishell *mnsh);
t_ast_node				*parse_pipeline(t_tokenstream *ts, t_minishell *mnsh);
t_ast_node				*parse_subshell(t_tokenstream *ts, t_minishell *mnsh);
t_ast_node				*parse_script(t_tokenstream *ts, t_minishell *mnsh);

// ======================== Utils ========================
int						is_redirection_token(t_tokenstream *ts);
int						set_redirection(t_command *cmd, t_tokenstream *ts);
int						realloc_args(t_command *cmd, int new_size);
t_command				*create_command(t_cmd_type type);
int						create_assignments(t_tokenstream *ts, t_list **asgmt);
t_logical_op			get_logical_op(t_tokenstream *ts);
int						is_assignment(t_tokenstream *ts);
t_assignment			*allocate_assignment(void);
// int						handle_wildcard(int count, t_token *token,
// 							t_list **expand, int (*is_quoted)(t_quote_status));
int						is_built_in(char *cmd_name);

// ======================== Assignments ========================
int						handle_expander_if_need(int size, t_token *token,
							t_assignment *assignment);

// ======================== Expander ========================
int						handle_var(int size, char *var_pos, t_token *token,
							t_list **expand);
int						update_wildcard_expander(t_exp_info *info,
							t_token *token, int (*is_qted)(t_quote_status));
int						set_merged_value(char **value, t_list **expander,
							t_tokenstream *ts);
void					release_escaped_char(char *str, char c);

#endif