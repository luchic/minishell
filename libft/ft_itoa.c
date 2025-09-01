/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:01:53 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/11 12:13:51 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	n_digit(long num)
{
	size_t	i;

	i = 0;
	if (num <= 0)
	{
		num = -1 * num;
		i++;
	}
	while (num != 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	long	num;

	num = (long)n;
	len = n_digit(num);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		num = -1 * (long) n;
	}
	while (num != 0)
	{
		str[len - 1] = num % 10 + '0';
		num = num / 10;
		len--;
	}
	return (str);
}

/* int	main(void)
{
	int	i = -2147483648LL;

	printf("%s ", ft_itoa(i));
} */
