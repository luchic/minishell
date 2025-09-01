/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:39:16 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/01 15:53:24 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Handle signals for interactive mode in the main function
// 
void    init_signal_handler(void)
{
    signal(SIGINT, handle_signal);  // Ctrl+C
    signal(SIGQUIT, SIG_IGN); // Ctrl+\-> core dump in the child process
    
}

void    handle_signal(int signum)
{
    if (signum == SIGINT) //(Ctrl+C)
    {
        write(1, "\nminishell$ ", 12);
    }
}