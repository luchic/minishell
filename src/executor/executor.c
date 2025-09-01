/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:56:03 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/01 21:54:24 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 // 4. 如果有子进程，在 fork() 后需要特别处理信号
        // pid_t pid = fork();
        // if (pid == 0) { // 子进程
        //     signal(SIGINT, SIG_DFL);  // Ctrl+C 
        //     signal(SIGQUIT, SIG_DFL); // core dump
        //     execve(...)
        // } else { // 父进程
        //     waitpid(pid, &status, 0);
        // }

*/

# include "minishell.h"
# include "ft_defines.h"

void    execute_script(t_minishell *mnsh)
{
    int i;
    int last_exit_status;

    if (!mnsh || !mnsh->script || !mnsh->script->nodes)
        return;
    i = 0;
    while (i < mnsh->script->count)
    {
        last_exit_status = execute_node(mnsh, mnsh->script->nodes[i]);
        mnsh->last_exit_status = last_exit_status;
        i++;
    }
}

// to get the last exit status of the last command executed
// logical->pipeline->command
// subshell contains a whole script AST

int execute_node(t_minishell *mnsh, t_ast_node *node)
{
    int left_status;
    
    if (!node)
        return (0);
    if (node->type == NODE_COMMAND)
    {
        return (execute_command(mnsh, &(node->command)));
    }
    else if (node->type == NODE_PIPELINE)
    {
        return (execute_pipeline(mnsh, &(node->pipeline)));
    }
    else if (node->type == NODE_LOGICAL)
    {
        return (execute_logical(mnsh, &(node->logical)));
    }
    else if (node->type == NODE_SUBSHELL)
    {
        return (execute_subshell(mnsh, &(node->subshell)));
    }
    return (0);
}