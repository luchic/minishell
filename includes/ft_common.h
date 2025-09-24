
#ifndef FT_COMMON_H
# define FT_COMMON_H

# include "ft_defines.h"
# include "ft_printf.h"
# include "lexer.h"
# include "libft.h"
# include "minishell.h"
# include "parser.h"

// ======================== function utils ========================

/// @brief Appends a string to a dynamically allocated array of strings.
/// @note It move only pointer's of the original strings.
/// It dosen't duplicate them. It free only the original array of pointers.
/// @param arr The original array of strings.
/// @param str The string to append.
/// @return The new array of strings, or NULL on failure.
char		**ft_array_append(char **arr, char *str);
void		ft_array_remove(char ***array, char *value);
char		**ft_strdup_array(char **array);
int			count_args(char **args);
int			ft_append_str(char **dest, const char *src);

/**
 * @brief Inserts a string into another string at a specified position.
 * @note It's not free str and insert, you have to free the original string.
 * @param str The original string.
 * @param insert The string to insert.
 * @param pos The position to insert the string at.
 * @return char* The new string with the inserted value, or NULL on failure.
 */
char		*ft_insert(char *str, char *insert, int pos);
char		*ft_replace(char *str, char *insert, int pos, int end);
char		*ft_strchr_escaped(const char *s, int c);
char		*ft_strchr_not_escaped(const char *s, int c);
void		set_exit_code(t_minishell *mnsh, int code);
int			is_single(t_quote_status status);
int			is_double(t_quote_status status);
int			is_single_or_double(t_quote_status status);
t_minishell	**get_mnsh(void);

// ================================ Signal Handling ============================
void		signal_check(void);
void		init_signal_handler(void);
void		handle_signal(int signum);

// ================================ Free Tools =================================
void		free_cmd(t_command *cmd);
void		free_pipeline(t_pipeline *pipeline);
void		free_ast_tree(t_ast_node *node);
void		free_subshell(t_subshell *subshell);
void		free_str_array(char **arr);
void		free_logical(t_logical_expression *logic);
void		free_script(t_script *script);
void		free_stack_minishell(t_minishell *mnsh);
void		ft_free_redir(void *content);
void		free_expander(void *param);
void		free_assignment(void *param);
void		free_cmd_expander(void *param);
void		free_and_exit(t_minishell *mnsh, int exit_code);

// ================================ Error Messages =============================
void		msg_unexpected_token(t_token *token);
void		msg_unexpected_token_type(t_token_type type);

// ================================ Env ========================================
char		*get_env(t_minishell *mnsh, const char *name);
int			is_valid_name(char *variable, char *name);

// ================================ Dirs utils ================================
int			is_directory(const char *path);
#endif
