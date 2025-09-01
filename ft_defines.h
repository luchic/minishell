/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_defines.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:40:54 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/01 14:08:20 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEFINES_H
# define FT_DEFINES_H

// Forward declaration
struct ASTNode;

typedef enum
{
	NODE_SCRIPT,
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
	NodeType				type;
	union
	{
		Command				command;
		Pipeline			pipeline;
		LogicalExpression	logical;
	};
}							ASTNode;

// Represents a script (root)
typedef struct s_script
{
	ASTNode					**commands;
	int						count;
}							Script;

#endif
