/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:33:38 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/11 10:32:16 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long	get_cur_long(const unsigned char *src, size_t i)
{
	unsigned long	value;

	value = 0;
	value |= (unsigned long)(*(src + i + 4)) << 0;
	value |= (unsigned long)(*(src + i + 5)) << 8;
	value |= (unsigned long)(*(src + i + 6)) << 16;
	value |= (unsigned long)(*(src + i + 7)) << 24;
	value <<= 32;
	value |= (unsigned long)(*(src + i + 0)) << 0;
	value |= (unsigned long)(*(src + i + 1)) << 8;
	value |= (unsigned long)(*(src + i + 2)) << 16;
	value |= (unsigned long)(*(src + i + 3)) << 24;
	return (value);
}

static size_t	fill_long(void *dst, void *src, size_t len)
{
	size_t			i;
	unsigned long	value;
	unsigned long	*dst_long;

	i = 0;
	dst_long = (unsigned long *) dst;
	while (i + 8 < len)
	{
		value = get_cur_long((unsigned char *)src, i);
		*dst_long = value;
		++dst_long;
		i += 8;
	}
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*byte_dst;
	const unsigned char	*byte_src;

	if (!dst && !src)
		return (NULL);
	byte_dst = dst;
	byte_src = src;
	i = fill_long(dst, (void *)src, n);
	while (i < n)
	{
		*(byte_dst + i) = *(byte_src + i);
		++i;
	}
	return (dst);
}

/* #include <stdio.h>
int main()
{
	void *res = ft_memcpy(NULL, NULL , 0);
	printf("Res NULL: %p\n", res);
} */