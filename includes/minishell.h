/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:58:32 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/26 18:58:34 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_defines.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// ======================== read.c ========================
char	*ft_read_line(t_minishell *mnsh);

// ======================== run.c ========================
int		run_loop(t_minishell *mnsh);

// ======================== setup.c ========================
int		init_minishell(t_minishell *mnsh, char **envp);
void	close_tty(t_minishell *mnsh);
#endif
