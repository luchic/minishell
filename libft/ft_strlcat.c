/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:57:24 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/14 11:36:38 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	deslen;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	deslen = ft_strlen(dst);
	if (dstsize <= deslen || dstsize == 0)
		return (dstsize + srclen);
	while (src[i] != '\0' && i + deslen < dstsize - 1)
	{
		dst[deslen + i] = src[i];
		i++;
	}
	dst[i + deslen] = '\0';
	if (dstsize < deslen)
		return (dstsize + srclen);
	return (deslen + srclen);
}

/* #include <string.h>
#include <unistd.h>
#include <stdio.h>
int main (void)
{
	char	dest[20] = "";
	char	src[] = "1";

	char	dest1[20] = "";
	char	src1[] = "1";

	printf("\n %s + %zu +%s \n", dest, ft_strlcat(dest, src, 0), dest);
	printf("\n %s + %zu +%s \n", dest1, strlcat(dest1, src1, 0), dest1);
	return 0;
} */
