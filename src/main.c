/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:00:58 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/01 18:00:38 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
# include "ft_defines.h"

int main(int argc, char **argv, char **envp)
{
    t_minishell mnsh;
    char        *input;
    
    ft_memset(&mnsh, 0, sizeof(t_minishell));
    init_signal_handler();
    
    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
        {
            printf("exit\n");
            exit(0);
        }
        add_history(input);
        // lexical analysis

        // parsing

        // Execute the command
        execute_script(&mnsh);
        
        free(input);
    }

    return (0);
}
