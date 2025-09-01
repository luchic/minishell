/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:49:32 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/08 15:46:28 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (sign * res);
}

int	ft_atoi(const char *str)
{
	while (ft_isspace(*str))
		str++;
	return (_atoi(str));
}

/* 
#include <stdio.h>
#include <stdlib.h>
void	ft_atoi_tests(char *cases[])
{
	int repl;
	int std;

	printf("\n============ Testing Function: ft_atoi =============\n");
	while (*cases)
	{
		repl = ft_atoi(*cases);
		std = atoi(*cases);
		if (repl != std)
		{
			printf(
	"Test feild: Value: %s | Res_repl: %d | Res_std: %d\n", *cases, repl, std);
		}
		else
		{
			printf( "Test Passed: Value: %s, | Result: %d\n" , *cases, repl);
		}
		cases++;
	}
}

int main()
{
	char *tatoi[] = {"0", "10", "-10", "2147483647", "-2147483648", NULL};
	ft_atoi_tests(tatoi);
} */