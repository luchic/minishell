/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 23:45:01 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/08 17:59:48 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int					dif;
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	ptr1 = (const unsigned char *)s1;
	ptr2 = (const unsigned char *)s2;
	while (n--)
	{
		dif = *ptr1 - *ptr2;
		if (dif != 0)
			return (dif);
		ptr1++;
		ptr2++;
	}
	return (0);
}

/* #include <stdio.h>
#include <string.h>

int main(void)
{
	const char	s1[] = "12345678";
	const char	s2[] = "12345678";

	printf("%d \n", ft_memcmp(s1, s2, 16));
	printf("%d \n", memcmp(s1, s2, 16));

	return 0;
} */
