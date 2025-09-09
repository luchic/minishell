/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:56:03 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/09 15:33:10 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

void    execute_script(t_minishell *mnsh)
{
    int i;
    int last_exit_status;

    if (!mnsh || !mnsh->script || !mnsh->script->nodes)
        return;
    i = 0;
    while (i < mnsh->script->count)
    {
		init_signal_handler();
        last_exit_status = execute_node(mnsh, &(mnsh->script->nodes[i]));
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
    if (node->type == COMMAND)
    {
        return (execute_command(mnsh, &(node->command)));
    }
    else if (node->type == PIPELINE)
    {
        return (execute_pipeline(mnsh, &(node->pipeline)));
    }
    else if (node->type == LOGICAL)
    {
        return (execute_logical(mnsh, &(node->logical)));
    }
    else if (node->type == SUBSHELL)
    {
        return (execute_subshell(mnsh, &(node->subshell)));
    }
    return (0);
}
