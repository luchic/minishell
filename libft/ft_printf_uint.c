/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:44:07 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/13 10:32:26 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_uint(unsigned int num)
{
	size_t	i;
	char	buffer[32];
	int		count;

	i = 0;
	if (num == 0)
		buffer[i++] = '0';
	while (num > 0)
	{
		buffer[i] = num % 10 + '0';
		num = num / 10;
		i++;
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

/* int	main(void)
{
	int b = ft_printf_uint(0);
	printf("\n%d", b);
	printf(" %u ", 0);
	return (0);
} */
