

#ifndef FT_DEFINES_H
# define FT_DEFINES_H
# include "libft.h"

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
	// CMD_ASSIGNMENT, //if no cmd name, but just assignemnt links
	//CMD_HEREDOC // executor doesn't execute, just handle redirection and tmp file
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
	REDIR_INPUT, // < infile cat
	REDIR_OUTPUT, // cat > outfile
	REDIR_APPEND, // cat >> outfile
	REDIR_HEREDOC // cat << delimiter
} t_redir_type;

typedef struct  s_redirection
{
	t_redir_type				type;
	int							fd;
	char						*value;
} t_redirection;

typedef struct s_command
{
	t_cmd_type					type; // 4 types: Built-in, External(need path to find), Assignment, Special (<<<< here doc)
	int							fd_in; // -1 if no redirection
	int							fd_out; // -1 if no redirection
	char						*name;
	char						**args; //includes name, NULL-terminated
	t_minishell					*mnsh;
	t_list						*redirections; // list of t_redirection
	t_list						*assignments; //list of t_var for assignments
}								t_command;

// Represents a pipeline
typedef struct s_pipeline
{
	struct s_ast_node			**commands; //!! this is s_ast_node, not s_command, to allow subshells in pipeline
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


#endif
