
#ifndef FT_COMMON_H
# define FT_COMMON_H

#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

// ======================== function utils ========================

char	**ft_array_append(char **arr, char *str);
void	ft_array_remove(char ***array, char *value);
void	free_str_array(char **arr);
int count_args(char **args);


// ======================== signal handling ========================
void    init_signal_handler(void);
void    handle_signal(int signum);


#endif
