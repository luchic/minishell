/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:50:07 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/11 13:40:08 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

/* #include <stdio.h>
#include <string.h>

int main(void)
{
	char	dest[10] = "hello";
	char	src[] = "123456";
	char	dest1[10] = "hello";
	char	src1[] = "123456";

	printf("%s %lu\n", src, ft_strlcpy(dest, "", 8));
	printf("%s\n", dest);
	printf("%s %lu\n", src1, strlcpy(dest1, "", 8));
	printf("%s\n", dest1);
	return 0;
} */
