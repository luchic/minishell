/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:43:57 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/25 16:43:58 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

int	ft_pwd(t_command *cmd)
{
	char	cwd[1024];
	char	*info;

	info = getcwd(cwd, sizeof(cwd));
	if (!info)
	{
		ft_printf_fd(STDERR, "pwd: error retrieving current directory: ");
		return (EXIT_FAILURE);
	}
	ft_printf_fd(cmd->fd_out, "%s\n", cwd);
	return (EXIT_SUCCESS);
}
