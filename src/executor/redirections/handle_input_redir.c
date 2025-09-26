/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:51:19 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/25 16:51:21 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int	open_input_file(const char *path, t_command *cmd)
{
	int	fd;

	close_previous_fd(cmd->fd_in);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_fd(STDERR, "%s: %s\n", path, strerror(errno));
		return (EXIT_FAILURE);
	}
	cmd->fd_in = fd;
	return (EXIT_SUCCESS);
}
