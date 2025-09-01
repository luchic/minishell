/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:39:27 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/09 22:48:54 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	str[15];
	long	num;

	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	num = (long)n;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num = -1 * num;
	}
	i = 0;
	while (num > 0)
	{
		str[i++] = num % 10 + '0';
		num = num / 10;
	}
	while (--i >= 0)
		ft_putchar_fd(str[i], fd);
}

/* int	main(void)
{
	int	n = -2147483648LL; //-2147483648;
	int	fd = 2;

	ft_putnbr_fd(n, fd);
	return (0);
} */
