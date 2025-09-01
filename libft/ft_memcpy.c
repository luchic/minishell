/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:01:10 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/14 20:19:14 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*ptr1;
	const unsigned char	*ptr2;

	i = 0;
	if (!dst && !src)
		return (NULL);
	ptr1 = (unsigned char *)dst;
	ptr2 = (const unsigned char *)src;
	while (i < n)
	{
		ptr1[i] = ptr2[i];
		i++;
	}
	return (dst);
}

/* int	main(void)
{
	// char			*dst1 = NULL;
	// char			*dst2 = NULL;
	// const char		src[20]= "abcd";
	// size_t		n = 3;

	printf("%s \n", ft_memcpy(((void *)0), "src",0));
	ft_putchar_fd('\n', 1);
	printf("%s \n", memcpy(((void *)0), "src",0));
} */
