/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:00:58 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/01 12:11:14 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_minishell mnsh;
    
    // Initialize minishell structure
    ft_memset(&mnsh, 0, sizeof(t_minishell));

    // Load environment variables into the minishell structure
    
}
