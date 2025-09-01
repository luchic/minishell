
#ifndef FT_DEFINES_H
# define FT_DEFINES_H

// Abstract Syntax Tree Node (ast node)
struct s_ast_node;
struct s_script;

typedef enum e_node_type
{
	NODE_SUBSHELL,
	NODE_COMMAND,
	NODE_PIPELINE,
	NODE_LOGICAL
}								t_node_type;

// Operators for logical expressions
typedef enum e_logical_op
{
	OP_AND,
	OP_OR
}								t_logical_op;

// ---- Structures ----

typedef struct s_var
{
	char						*name;
	char						*value;
	struct s_var				*next;
}								t_var;

typedef struct s_minishell
{
	struct s_var				*variables;
	struct s_script				*script;
	int							num_variables;
	int							is_background;
	int							last_exit_status;
}								t_minishell;

// ---- Executors ----
// Represents a word (like "sleep", "2", etc.)
typedef struct s_word
{
	char						*text;
	struct s_word				*next;
}								t_word;

// Represents a command
typedef struct s_command
{
	int							type; // 4 types: Built-in, External(need path to find), Assignment, Special (<<<< here doc)
	t_word						*name;
	t_word						*suffix;
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
	t_script					*script;
}								t_subshell;

// Generic AST node
typedef struct s_ast_node
{
	t_node_type					type;
	union
	{
		t_command				command;
		t_pipeline				pipeline;
		t_logical_expression	logical;
		t_subshell				subshell;
	};
}								t_ast_node;

// Represents a script (root)
typedef struct s_script
{
	t_ast_node					**nodes; //to avoid confusion from pipeline->commands
	int							count;
}								t_script;

#endif
