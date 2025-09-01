/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:57:32 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/14 10:03:39 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include "libft.h"

static int	putnbr(long nb, int fd)
{
	char	out;
	int		res;

	if (nb / 10 == 0)
	{
		out = nb + '0';
		return (write(fd, &out, 1));
	}
	out = nb % 10 + '0';
	nb = nb / 10;
	res = putnbr(nb, fd);
	if (res == -1)
		return (-1);
	if (write(fd, &out, 1) == -1)
		return (-1);
	return (res + 1);
}

int	ft_putnbr_fd(int n, int fd)
{
	long	new_int;
	int		res;

	new_int = n;
	if (new_int < 0)
	{
		if (write(fd, "-", 1) == -1)
			return (-1);
		res = putnbr(new_int * -1, fd);
		if (res == -1)
			return (-1);
		return (res + 1);
	}
	else
		return (putnbr(new_int, fd));
}
