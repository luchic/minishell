/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_defines.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:58:54 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/27 18:22:59 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEFINES_H
# define FT_DEFINES_H

# include "libft.h"
# include <stdio.h>

struct							s_ast_node;
struct							s_script;
typedef struct s_ast_node		t_ast_node;
typedef struct s_script			t_script;

// ---- Enums ----

typedef enum e_node_type
{
	SUBSHELL,
	COMMAND,
	PIPELINE,
	LOGICAL
}								t_node_type;

typedef enum e_logical_op
{
	OP_INVALID,
	OP_AND,
	OP_OR
}								t_logical_op;

typedef enum e_cmd_type
{
	CMD_BUILTIN,
	CMD_EXTERNAL,
}								t_cmd_type;

// ---- Structures ----

typedef struct t_expander
{
	char						*var_name;
	int							var_start;
	int							var_end;
}								t_expander;

typedef struct s_var
{
	char						*name;
	char						*value;
}								t_var;

typedef struct s_minishell
{
	t_list						*variables;
	struct s_script				*script;
	int							num_variables;
	int							is_background;
	int							last_exit_status;
	int							parser_status;
	int							is_tty_out;
	int							is_tty_in;
	int							fd;
	int							is_running;
	FILE						*tty_out;
	FILE						*tty_in;
	char						**envp;
}								t_minishell;

// ---- Executors ----

typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}								t_redir_type;

typedef struct s_redirection
{
	t_redir_type				type;
	int							fd;
	int							is_quoted;
	char						*value;
	t_list						*expander;
}								t_redirection;

typedef struct s_assigment
{
	char						*value;
	int							len;
	t_list						*expand;
}								t_assignment;

typedef struct s_cmd_expander
{
	int							index;
	t_list						*expand;
}								t_cmd_expander;

typedef struct s_command
{
	t_cmd_type					type;
	int							fd_in;
	int							fd_out;
	char						*name;
	char						**args;
	t_list						*expander;
	t_minishell					*mnsh;
	t_list						*redirections;
	t_list						*assignments;
	int							fd_saved[2];
}								t_command;

// Represents a pipeline
typedef struct s_pipeline
{
	struct s_ast_node			**commands;
	int							count;
}								t_pipeline;

// Represents a logical expression
typedef struct s_logical_expression
{
	t_logical_op				op;
	struct s_ast_node			*left;
	struct s_ast_node			*right;
}								t_logical_expression;

// Represents a subshell
typedef struct s_subshell
{
	t_ast_node					*script;
	t_minishell					*mnsh;
}								t_subshell;

// Generic AST node
typedef struct s_ast_node
{
	t_node_type					type;
	union
	{
		t_command				*command;
		t_pipeline				*pipeline;
		t_logical_expression	*logical;
		t_subshell				*subshell;
	};
}								t_ast_node;

typedef struct s_script
{
	t_ast_node					*nodes;
	int							count;
}								t_script;

# define STDERR 2
# define STDOUT 1
# define STDIN 0

# define FAIL 1
# define SYNTAX_ERROR 2

# define CMD_NOT_FOUND 127
# define EXECUTION_ERROR 126
# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

# define PREFIX "minishell"
# define UNEXPECTED_TOKEN "syntax error near unexpected token"
# define UNBALANCED_QUOTES "syntax error: unbalanced quotes"

#endif
