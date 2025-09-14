/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:56:03 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/14 18:58:39 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

t_ast_node *get_script(t_minishell *mnsh)
{
    if (!mnsh || !mnsh->script)
        return (NULL);
    return (mnsh->script->nodes);
}
int run_executor(t_minishell *mnsh)
{
    return (execute_script(mnsh, get_script(mnsh)));
}


int    execute_script(t_minishell *mnsh, t_ast_node *script)
{
    int last_exit_status;

    if (!mnsh || !script)
        return (EXIT_FAILURE);

    init_signal_handler();
    last_exit_status = execute_node(mnsh, script);
    mnsh->last_exit_status = last_exit_status;
    return (EXIT_SUCCESS);
}

int execute_node(t_minishell *mnsh, t_ast_node *node)
{
    if (!node)
        return (EXIT_FAILURE);
    if (node->type == COMMAND)
    {
        return (execute_command(mnsh, node->command));
    }
    else if (node->type == PIPELINE)
    {
        return (execute_pipeline(mnsh, node->pipeline));
    }
    else if (node->type == LOGICAL)
    {
        return (execute_logical(mnsh, node->logical));
    }
    else if (node->type == SUBSHELL)
    {
        return (execute_subshell(mnsh, node->subshell));
    }
    return (EXIT_FAILURE);
}
