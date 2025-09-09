


#ifndef FT_DEFINES_H
# define FT_DEFINES_H

# include "libft.h"
// Forward declarations
struct s_ast_node;
struct s_script;
typedef struct s_ast_node t_ast_node;
typedef struct s_script t_script;

typedef enum e_node_type
{
	SUBSHELL,
	COMMAND,
	PIPELINE,
	LOGICAL
}								t_node_type;

// Operators for logical expressions
typedef enum e_logical_op
{
	OP_INVALID,
	OP_AND,
	OP_OR
}								t_logical_op;

// ---- Command Types ----

typedef enum e_cmd_type
{
	CMD_BUILTIN,
	CMD_EXTERNAL,
	CMD_ASSIGNMENT,
	CMD_HEREDOC
}								t_cmd_type;

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
	char						**envp;
}								t_minishell;

// ---- Executors ----

// Represents a command
typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
} t_redir_type;

typedef struct  s_redirection
{
	t_redir_type				type;
	char						*value;
	struct s_redirection		*next;
} t_redirection;

typedef struct s_command
{
	t_cmd_type					type; // 4 types: Built-in, External(need path to find), Assignment, Special (<<<< here doc)
	int							fd_in; // -1 if no redirection
	int							fd_out; // -1 if no redirection	
	char						*name; 
	char						**args; //includes name, NULL-terminated
	t_list 						*assignments;
	t_minishell					*mnsh;
	t_redirection				*redirections;
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
typedef struct s_compound_list
{
	struct s_ast_node			**nodes;
	int							count;
}								t_compound_list;

typedef struct s_subshell
{	
	t_ast_node					*script;
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

// Represents a script (root)
typedef struct s_script
{
	t_ast_node					*nodes; //to avoid confusion from pipeline->commands
	int							count;
}								t_script;

# define STDERR 2
# define STDOUT 1
# define STDIN 0


// execution functions

int execute_command(t_minishell *mnsh, t_command *cmd);
int execute_pipeline(t_minishell *mnsh, t_pipeline *pipeline);
int execute_logical(t_minishell *mnsh, t_logical_expression *logic);
int execute_subshell(t_minishell *mnsh, t_subshell *subsh);
int execute_node(t_minishell *mnsh, t_ast_node *node);
void execute_script(t_minishell *mnsh);

//// built-in functions
int ft_echo(t_command *cmd);

#endif
