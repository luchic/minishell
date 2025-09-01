/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:23:27 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/14 12:07:46 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	else
		return (0);
}

static int	is_nbr(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	sum;

	i = 0;
	sign = 1;
	sum = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (is_nbr(str[i]) == 1)
	{
		sum = sum * 10 + str[i] - '0';
		i++;
	}
	return (sum * sign);
}

/* #include <string.h>
#include <stdio.h>

int	main (void)
{
	int		nbr;
	char	*str = NULL;

	nbr = ft_atoi(str);
	printf("%d", nbr);
	return (nbr);
} */
