/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:16:21 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/08 15:46:13 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	I've noticed when I make like this(byte is unsigned char): byte << 24,
	then unsigne long fill with ones I got 0xffffffff80808080 that value.
	
*/

static size_t	fill_long(void *b, int c, size_t len)
{
	size_t			i;
	unsigned long	byte;
	unsigned long	value;
	unsigned long	*memory;

	i = 0;
	byte = c & 0xFF;
	value = ((byte | (byte << 8) | (byte << 16) | (byte << 24)));
	value |= value << 32;
	memory = (unsigned long *) b;
	while (i + 8 < len)
	{
		*memory = value;
		++memory;
		i += 8;
	}
	return (i);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	val;
	unsigned char	*mem;

	i = fill_long(b, c, len);
	val = (unsigned char)c;
	mem = (unsigned char *)(b + i);
	while (i < len)
	{
		*mem = val;
		++mem;
		++i;
	}
	return (b);
}
