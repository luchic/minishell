/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:13:41 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/13 10:32:08 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lower_hex(unsigned int num)
{
	char	*hex;
	size_t	i;
	char	buffer[32];
	int		count;

	hex = "0123456789abcdef";
	i = 0;
	if (num == 0)
		buffer[i++] = '0';
	while (num > 0)
	{
		buffer[i++] = hex[num % 16];
		num = num / 16;
	}
	buffer[i] = '\0';
	count = 0;
	while (i > 0)
	{
		if (write(1, &buffer[i - 1], 1) < 0)
			return (-1);
		count++;
		i--;
	}
	return (count);
}

static int	upper_hex(unsigned int num)
{
	char	*hex;
	size_t	i;
	char	buffer[32];
	int		count;

	hex = "0123456789ABCDEF";
	i = 0;
	if (num == 0)
		buffer[i++] = '0';
	while (num > 0)
	{
		buffer[i++] = hex[num % 16];
		num = num / 16;
	}
	buffer[i] = '\0';
	count = 0;
	while (i > 0)
	{
		if (write(1, &buffer[i - 1], 1) < 0)
			return (-1);
		count++;
		i--;
	}
	return (count);
}

int	ft_printf_hex(int n, char c)
{
	unsigned int	num;

	num = (unsigned int)n;
	if (c == 'x')
		return (lower_hex(num));
	else
		return (upper_hex(num));
}

/* int	main(void)
{
	// long	b = ft_printf_hex(-18, 'X');
	ft_printf("%x\n", 10);
	printf("%x", 10);
	return (0);
} */
