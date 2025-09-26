/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:44:09 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/26 18:47:50 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

int	ft_unset(t_command *cmd)
{
	int		i;
	char	***envp;

	if (count_args(cmd->args) < 2)
		return (EXIT_SUCCESS);
	envp = &(cmd->mnsh->envp);
	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_identifier(cmd->args[i]))
			ft_array_remove(envp, cmd->args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
