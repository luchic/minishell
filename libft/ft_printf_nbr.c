/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:42:58 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/13 10:32:13 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*nbr_to_str(long num)
{
	static char	str[15];
	size_t		i;
	char		z;

	i = 0;
	if (num == 0)
		str[i++] = '0';
	z = '-';
	if (num < 0)
	{
		if (write(1, &z, 1) < 0)
			return (NULL);
		num = -1 * num;
	}
	while (num > 0)
	{
		str[i++] = num % 10 + '0';
		num = num / 10;
	}
	str[i] = '\0';
	return (str);
}

int	ft_printf_nbr(int n)
{
	long	num;
	char	*str;
	int		len;

	num = (long)n;
	str = nbr_to_str(num);
	if (str == NULL)
		return (-1);
	len = ft_strlen(str);
	while (len > 0)
	{
		if (write(1, &str[len - 1], 1) < 0)
			return (-1);
		len--;
	}
	if (n < 0)
		return (ft_strlen(str) + 1);
	return (ft_strlen(str));
}

/* int	main(void)
{
	// int	n = 123456; //-2147483648;
	// int	b = ft_printf_nbr(n);
	// printf("~%d", b);
	ft_printf("%d\n", 0);
	printf("%d", 0);

	return (0);
} */
