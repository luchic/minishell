/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:29:02 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/13 18:27:20 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		byte;
	const unsigned char	*memory;

	byte = c;
	memory = s;
	i = 0;
	while (i < n)
	{
		if (*(memory + i) == byte)
			return ((void *)(memory + i));
		i++;
	}
	return (NULL);
}
