/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:43:37 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/29 13:01:27 by mezhang          ###   ########.fr       */
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

static int	get_digi_pos(const char *str)
{
	int	i;
	int	neg;

	if (!str || !*str)
		return (0);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = 1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (0);
	return (i);
}

static int	is_str_llong(const char *str)
{
	const char	*max;
	const char	*min;
	int			i;
	int			start;

	max = "9223372036854775807";
	min = "9223372036854775808";
	start = get_digi_pos(str);
	if (!ft_isdigit(str[start]))
		return (0);
	i = start;
	while (ft_isdigit(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '\0' || i - start > 19)
		return (0);
	if (i - start < 19)
		return (1);
	if (str[start - 1] == '-')
		return (ft_strncmp(str + start, min, 19) <= 0);
	else
		return (ft_strncmp(str + start, max, 19) <= 0);
}

int	ft_exit(t_command *cmd)
{
	long long	status;
	int			argc;

	argc = count_args(cmd->args);
	if (isatty(STDIN))
		ft_printf_fd(STDOUT, "exit\n");
	if (argc == 1)
		free_and_exit(cmd->mnsh, cmd->mnsh->last_exit_status);
	if (!is_str_llong(cmd->args[1]))
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
	free_and_exit(cmd->mnsh, (unsigned char)(status & 0xFF));
	return (EXIT_SUCCESS);
}
