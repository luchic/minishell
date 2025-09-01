/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:56:03 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/01 18:00:22 by mezhang          ###   ########.fr       */
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

    if (!mnsh || !mnsh->script || !mnsh->script->commands)
        return;
    i = 0;
    while (i < mnsh->script->count)
    {
        last_exit_status = execute_node(mnsh, mnsh->script->commands[i]);
        i++;
    }
}

int execute_node(t_minishell *mnsh, ASTNode *node)
{
    int left_status;
    
    if (!node)
        return (0);
    
    if (node->type == NODE_COMMAND)
    {
        return (execute_command(&(node->command)));
    }
    else if (node->type == NODE_PIPELINE)
    {
        return (execute_pipeline(&(node->pipeline)));
    }
    else if (node->type == NODE_LOGICAL)
    {
        if (node->logical.op == OP_AND)
        {
            left_status = execute_node(mnsh, node->logical.left);
            if (left_status == 0)
            {
                return (execute_node(mnsh, node->logical.right));
            }
            return (left_status);
        }
        else if (node->logical.op == OP_OR)
        {
            left_status = execute_node(mnsh, node->logical.left);
            if (left_status != 0)
            {
                return (execute_node(mnsh, node->logical.right));
            }
            return (left_status);
        }
    }
    return (0);
}