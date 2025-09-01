/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_defines.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:40:54 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/01 17:50:36 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEFINES_H
# define FT_DEFINES_H

// Forward declaration
struct ASTNode;

typedef enum
{
	// NODE_SCRIPT,
	NODE_COMMAND,
	NODE_PIPELINE,
	NODE_LOGICAL
}							NodeType;

// Operators for logical expressions
typedef enum
{
	OP_AND,
	OP_OR
}							LogicalOp;

// ---- Structures ----

typedef struct s_var
{
    char					*name;
    char					*value;
    struct s_var			*next;
}							t_var;

typedef struct s_minishell 
{
    struct s_var			*variables;
    t_script				*script;
    int						num_variables;
    int						is_background;
	int						last_exit_status;
}   						t_minishell;

// ---- Executors ----

// Represents a word (like "sleep", "2", etc.)
typedef struct Word
{
	char					*text;
	struct Word				*next;
}							Word;

// Represents a command
typedef struct Command
{
	Word					*name;
	Word					*suffix;
}							Command;

// Represents a pipeline
typedef struct Pipeline
{
	struct ASTNode			**commands;
	int						count;
}							Pipeline;

// Represents a logical expression
typedef struct LogicalExpression
{
	LogicalOp				op;
	struct ASTNode			*left;
	struct ASTNode			*right;
}							LogicalExpression;

// Generic AST node
typedef struct ASTNode
{
	NodeType				type; //0: command, 1: pipeline, 2: logical
	union
	{
		Command				command;
		Pipeline			pipeline;
		LogicalExpression	logical; // AND / OR
	};
}							ASTNode;

// Represents a script (root)
typedef struct s_script
{
	ASTNode					**commands;
	int						count;
}							t_script;

#endif
