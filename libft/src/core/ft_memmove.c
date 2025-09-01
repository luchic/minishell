/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:35:21 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/14 09:29:25 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst == src || len == 0)
		return (dst);
	if ((uintptr_t) dst + len <= (uintptr_t) src
		|| (uintptr_t) src + len <= (uintptr_t) dst)
		return (ft_memcpy(dst, src, len));
	while (dst < src && i < len)
	{
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		i++;
	}
	i = len;
	while (src < dst && i > 0)
	{
		i--;
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
	}
	return (dst);
}
