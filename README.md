# Minishell

A fully functional shell written in C as part of the 42 curriculum. Minishell replicates core Bash behavior including pipes, redirections, logical operators, subshells, variable expansion, and wildcard globbing.

## Build

```bash
make        # compile
make debug  # compile with address sanitizer
make re     # full rebuild
```

Requires **GNU Readline** (`-lreadline`) and the bundled **libft**.

## Architecture

The shell follows a classic three-stage pipeline:

```
Input (readline) ──> Lexer ──> Parser (AST) ──> Executor
```

### Lexer (`src/lexer/`)

The lexer tokenizes raw input into a flat list of `t_token` structs. Each token carries its **type** (WORD, PIPE, AND, OR, REDIRECT_IN, HEREDOC, etc.) and **quote status** (UNQUOTED, SINGLE_QUOTED, DOUBLE_QUOTED, MIXED_QUOTES).

Quote status is tracked per token so the expander knows where to suppress variable expansion (single quotes) and where to allow it (double quotes / unquoted).

```
echo "hello $USER" | wc -l
  │       │           │  │
  WORD  WORD(DQ)    PIPE WORD
```

### Parser (`src/parser/`)

A **recursive descent parser** consumes the token stream and builds an **Abstract Syntax Tree (AST)**. The grammar hierarchy mirrors operator precedence:

```
parse_script        ──  top-level, handles && and ||
  └─ parse_pipeline       ──  handles |
       └─ parse_simple_command  ──  command + args + redirections
            └─ parse_subshell        ──  ( grouped commands )
```

The token stream abstraction (`t_tokenstream`) provides `peek`, `advance`, `match`, and `expect` operations, keeping the parser clean.

### AST

AST nodes use a **tagged union** so a single `t_ast_node` can represent any construct:

```c
typedef struct s_ast_node {
    t_node_type type;           // COMMAND | PIPELINE | LOGICAL | SUBSHELL
    union {
        t_command            *command;
        t_pipeline           *pipeline;
        t_logical_expression *logical;
        t_subshell           *subshell;
    };
} t_ast_node;
```

| Node type | Contains |
|-----------|----------|
| `COMMAND` | name, args, redirections list, assignments list, expander info |
| `PIPELINE` | array of command nodes + count |
| `LOGICAL` | operator (AND/OR) + left/right child nodes |
| `SUBSHELL` | nested script (recursive AST) |

### Executor (`src/executor/`)

The executor walks the AST recursively:

- **COMMAND** -- expand variables/wildcards, apply redirections, then dispatch to builtin or `fork`+`execve`.
- **PIPELINE** -- fork each command, connect them with `pipe()` file descriptors, wait for all children.
- **LOGICAL** -- short-circuit: run left first, then conditionally run right based on exit code.
- **SUBSHELL** -- execute the nested script in a child context.

Heredocs are **preprocessed** into temp files before execution begins, so all `<<` delimiters are read upfront (matching Bash behavior).

### Expander (`src/expander/`)

Expansion runs between parsing and execution:

1. **Variable expansion** -- replaces `$VAR` and `$?` with their values, respecting quote context.
2. **Wildcard expansion** -- expands `*` glob patterns against the filesystem (skipped inside quotes).

The parser attaches `t_expander` metadata to tokens that need expansion, so the expander knows exactly which parts of a token to process.

## Features

| Feature | Details |
|---------|---------|
| Pipes | `cmd1 \| cmd2 \| cmd3` with proper fd management |
| Logical operators | `&&` and `\|\|` with short-circuit evaluation |
| Redirections | `<` input, `>` output, `>>` append |
| Heredoc | `<< DELIM`, quoted delimiter disables expansion |
| Subshells | `(cmd1 && cmd2) \| cmd3` |
| Variable expansion | `$VAR`, `$?` (last exit status) |
| Wildcards | `*.c`, pattern matching against directory entries |
| Quoting | Single quotes (literal), double quotes (allow `$` expansion) |
| Assignments | `VAR=value cmd` (command-scoped) and `VAR=value` (shell-scoped) |
| Signals | Ctrl+C handled gracefully in interactive and execution modes |

## Builtins

| Command | Notes |
|---------|-------|
| `echo` | supports `-n` flag |
| `cd` | supports `~`, `-`, no-arg (goes to `$HOME`) |
| `pwd` | prints working directory |
| `export` | set/list environment variables |
| `unset` | remove environment variables |
| `env` | display environment |
| `exit` | exit with optional status code |

## Project Structure

```
src/
├── main.c              # entry point
├── core/               # REPL loop, readline, initialization
├── lexer/              # tokenization
├── parser/
│   ├── parse/          # recursive descent (script, pipeline, cmd, redir, subshell)
│   ├── token_stream/   # peek/advance/match abstraction
│   ├── assignments/    # variable assignment extraction
│   └── utils/          # AST node constructors
├── executor/
│   ├── cmd_built_in/   # builtin implementations
│   ├── cmd_external/   # fork + execve
│   ├── redirections/   # fd management, heredoc
│   └── pipe_utils/     # pipeline forking
├── expander/
│   ├── variable/       # $VAR and $? expansion
│   └── wildcards/      # glob pattern matching
└── common/             # env, signals, memory cleanup, utils
```
