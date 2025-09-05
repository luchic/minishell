/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:00:58 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/02 20:53:52 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_defines.h"

void init_minishell(t_minishell *mnsh, int argc, char **argv, char **envp)
{
    int i;

    ft_memset(&mnsh, 0, sizeof(t_minishell));
    
    mnsh->envp = malloc(sizeof(char *) * (count_args(envp) + 1));
    if (!mnsh->envp)
        return;
    for (i = 0; envp[i]; i++)
    {
        mnsh->envp[i] = ft_strdup(envp[i]);
        if (!mnsh->envp[i])
            return;
    }
    mnsh->envp[i] = NULL;
}

int main(int argc, char **argv, char **envp)
{
    t_minishell mnsh;
    char        *input;
    

    init_minishell(&mnsh, argc, argv, envp);
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
