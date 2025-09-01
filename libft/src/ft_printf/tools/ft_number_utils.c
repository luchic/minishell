/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 11:58:26 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/29 13:39:43 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defs.h"

int	ft_getsize_unsigned(unsigned long num, int base)
{
	int	res;

	res = 0;
	if (base <= 1)
		return (0);
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= base;
		res++;
	}
	return (res);
}

int	ft_getsize_signed(long num, int base)
{
	unsigned long	unum;

	unum = num;
	if (num < 0)
	{
		unum = (unsigned long)(-(num + 1) + 1);
		return (ft_getsize_unsigned(unum, base) + 1);
	}
	return (ft_getsize_unsigned(unum, base));
}

unsigned int	ft_unsigned(int num)
{
	if (num >= 0)
		return ((unsigned int)num);
	return ((unsigned int)(-(num + 1) + 1));
}

int	ft_getsize_numformat(unsigned int unum, t_format *cur)
{
	if (cur->format == 'x' || cur->format == 'X')
		return (ft_getsize_unsigned(unum, 16));
	else
		return (ft_getsize_unsigned(unum, 10));
}
