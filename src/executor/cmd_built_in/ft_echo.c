/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:43:27 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/25 16:43:29 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

static int	is_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (i > 1);
}

int	ft_echo(t_command *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (cmd->args[i] && is_n_option(cmd->args[i]))
	{
		newline = 0;
		i++;
	}
	while (cmd->args[i])
	{
		ft_printf_fd(STDOUT, "%s", cmd->args[i]);
		if (cmd->args[i + 1])
			ft_printf_fd(STDOUT, " ");
		i++;
	}
	if (newline)
		ft_printf_fd(STDOUT, "\n");
	return (EXIT_SUCCESS);
}

/* int main()
{
	t_command cmd;
	char *args1[] = {"echo", "-n", "-n", "Hello,", "world!", NULL};
	// char  *args[] = {"echo", "\n", NULL};
	char *args2[] = {"echo", "if no -n then closely following the previoius,",
		"world!", NULL};

	// Initialize the command structure properly
	cmd.type = CMD_BUILTIN;
	cmd.fd_in = -1;
	cmd.fd_out = STDOUT_FILENO;  // Use standard output
	cmd.name = "echo";

	cmd.args = args1;
	ft_echo(&cmd);

	// cmd.args = args;
	// ft_echo(&cmd);

	cmd.args = args2;
	ft_echo(&cmd);

	return (0);
} */
