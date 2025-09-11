
#ifndef FT_COMMON_H
# define FT_COMMON_H

# include "ft_defines.h"
# include "ft_printf.h"
# include "libft.h"
# include "minishell.h"

// ======================== function utils ========================

char	**ft_array_append(char **arr, char *str);
void	ft_array_remove(char ***array, char *value);
char	**ft_strdup_array(char **array);
int		count_args(char **args);

// ======================== signal handling ========================
void	init_signal_handler(void);
void	handle_signal(int signum);

// ======================== Free Tools ========================
void	free_cmd(t_command *cmd);
void	free_pipeline(t_pipeline *pipeline);
void	free_ast_tree(t_ast_node *node);
void	free_subshell(t_subshell *subshell);
void	free_str_array(char **arr);
void	free_logical(t_logical_expression *logic);
void	free_script(t_script *script);
void	free_minishell(t_minishell *mnsh);

#endif
