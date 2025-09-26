/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_subsh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:42:35 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/25 17:12:08 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

int	execute_subshell(t_minishell *mnsh, t_subshell *subsh)
{
	if (!mnsh || !subsh || !subsh->script)
		return (1);
	if (prep_heredoc_node(subsh->script) != EXIT_SUCCESS)
	{
		mnsh->last_exit_status = 1;
		return (EXIT_FAILURE);
	}
	return (execute_script(mnsh, subsh->script));
}
