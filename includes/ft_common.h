
#ifndef FT_COMMON_H
# define FT_COMMON_H

#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

// ======================== function utils ========================

char	**ft_array_append(char **arr, char *str);
void	ft_array_remove(char ***array, char *value);
char	**ft_strdup_array(char **array);
void	free_str_array(char **arr);
int		count_args(char **args);

// ======================== memory management ========================
void	free_ast_tree(t_ast_node *node);
void	free_cmd(t_command *cmd);
void	free_pipeline(t_pipeline *pipeline);
void	free_logical(t_logical_expression *logic);
void	free_subshell(t_subshell *subshell);
void	ft_free_redir(void *content);


// ======================== signal handling ========================
void	init_signal_handler(void);
void	handle_signal(int signum);


#endif
