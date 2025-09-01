/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:01:14 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/01 14:09:31 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "libft.h"

typedef struct s_var
{
    char			*name;
    char			*value;
    struct s_var	*next;
}	t_var;

typedef struct s_minishell
{
    struct s_var    *variables;
    struct s_var    *pipelines;
    int             num_variables;
    int             num_pipelines;
    int             is_background;
}   t_minishell;

// enum e_ending
// {
//     START,
//     //PIPE,  // not sure if we need this. also do we need brackets?
//     AND,
//     OR
// };

// typedef struct s_pipeline
// {
//     struct s_command    *cmds;
//     enum e_ending       ending;
//     int                 num_cmds;
//     struct s_pipeline   *next;
// }   t_pipeline;

typedef struct s_command
{
    char                **args;
    int                 num_args;
	int                 is_builtin; //maybe not needed
	struct s_redir      *redirs;
}   t_command;

typedef struct s_redir
{
    char            *file;
    int             type; // < 0, > 1, >> 2, << 3, <<< 4
    struct s_redir  *next;
}   t_redir;

#endif