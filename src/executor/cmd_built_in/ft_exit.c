/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:43:37 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/27 16:53:55 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "ft_defines.h"
#include "ft_executor.h"
#include "libft.h"
#include "minishell.h"
#include <limits.h>

static long long	ft_strtoll(const char *str, char **endptr)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}

static int	is_valid_num_arg(const char *str)
{
	int			i;
	char		*endptr;

	if (!str || !*str)
		return (0);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	errno = 0;
	ft_strtoll(str, &endptr);
	while (*endptr && ft_isspace(*endptr))
		endptr++;
	if (*endptr != '\0')
		return (0);
	if (errno == ERANGE)
		return (0);
	return (1);
}

int	ft_exit(t_command *cmd)
{
	int	status;
	int	argc;

	argc = count_args(cmd->args);
	if (isatty(STDIN))
		ft_printf_fd(STDOUT, "exit\n");
	if (argc == 1)
		free_and_exit(cmd->mnsh, cmd->mnsh->last_exit_status);
	if (!is_valid_num_arg(cmd->args[1]))
	{
		ft_printf_fd(STDERR, "%s: exit: %s: numeric argument required\n",
			PREFIX, cmd->args[1]);
		free_and_exit(cmd->mnsh, 2);
	}
	if (argc > 2)
	{
		ft_printf_fd(STDERR, "%s: exit: too many arguments\n", PREFIX);
		return (EXIT_FAILURE);
	}
	status = ft_strtoll(cmd->args[1], NULL);
	free_and_exit(cmd->mnsh, (unsigned char)status);
	return (EXIT_SUCCESS);
}
