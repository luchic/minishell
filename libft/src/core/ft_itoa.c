/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:46:42 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/13 18:26:58 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size_string(int n)
{
	size_t	size;

	size = 0;
	if (n < 0)
		size++;
	if (n == 0)
		return (1);
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static char	*_itoa(char *res, long n, size_t size)
{
	size_t	iter;

	iter = size;
	if (n < 0)
	{
		res[0] = '-';
		n *= -1;
	}
	while (n)
	{
		res[iter - 1] = n % 10 + '0';
		n /= 10;
		iter--;
	}
	res[size] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	size_t	size;

	size = size_string(n);
	res = (char *)ft_calloc((size + 1), sizeof(char));
	if (!res)
		return (NULL);
	if (n == 0)
	{
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}
	return (_itoa(res, n, size));
}
