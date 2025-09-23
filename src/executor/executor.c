/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:56:03 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/22 22:04:11 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"


int    execute_script(t_minishell *mnsh, t_ast_node *script)
{
    int last_exit_status;

    if (!script)
        return (EXIT_FAILURE);
    ft_log_fd(LOG_INFO, STDERR, "Starting script execution...\n"); ///to delete --- IGNORE ---
    // init_signal_handler();
    
    if (script->type != COMMAND && script->type != PIPELINE
        && script->type != LOGICAL && script->type != SUBSHELL)
    {
        ft_log_fd(LOG_ERROR, STDERR, "Invalid script node type: %d\n", script->type); ///to delete --- IGNORE ---
        return (EXIT_FAILURE);
    }
    if (script->type == COMMAND)
        ft_log_fd(LOG_INFO, STDERR, "Executing command: %s\n", script->command->name); ///to delete --- IGNORE ---
    else if (script->type == PIPELINE)
        ft_log_fd(LOG_INFO, STDERR, "Executing pipeline\n"); ///to delete --- IGNORE ---
    else if (script->type == LOGICAL)
        ft_log_fd(LOG_INFO, STDERR, "Executing logical expression\n"); ///to delete --- IGNORE ---
    else if (script->type == SUBSHELL)
        ft_log_fd(LOG_INFO, STDERR, "Executing subshell\n"); ///to delete --- IGNORE ---

    last_exit_status = execute_node(mnsh, script);
    mnsh->last_exit_status = last_exit_status;
    return (last_exit_status); //modified to actual last_exit_status
}

int execute_node(t_minishell *mnsh, t_ast_node *node)
{
    if (!node)
        return (EXIT_FAILURE);
    if (node->type == COMMAND)
    {
       ft_log_fd(LOG_INFO, STDERR, "Executing command %s for type COMMAND\n", node->command->name); ///to delete --- IGNORE ---
        return (execute_command(mnsh, node->command));
    }
    else if (node->type == PIPELINE)
    {
        ft_log_fd(LOG_INFO, STDERR, "Executing pipeline  for type PIPELINE\n"); ///to delete --- IGNORE ---
        return (execute_pipeline(mnsh, node->pipeline));
    }
    else if (node->type == LOGICAL)
    {
        ft_log_fd(LOG_INFO, STDERR, "Executing logical expression for type LOGICAL\n"); ///to delete --- IGNORE ---
        return (execute_logical(mnsh, node->logical));
    }
    else if (node->type == SUBSHELL)
    {
        ft_log_fd(LOG_INFO, STDERR, "Executing subshell for type SUBSHELL\n"); ///to delete --- IGNORE ---
        return (execute_subshell(mnsh, node->subshell));
    }
    return (EXIT_FAILURE);
}
