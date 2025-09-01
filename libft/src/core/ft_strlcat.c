/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:55:21 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/15 09:13:42 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	counter;
	size_t	size_dest;
	size_t	size_src;

	size_src = ft_strlen(src);
	if (dstsize == 0)
		return (size_src);
	size_dest = ft_strlen(dest);
	counter = 0;
	while (dest[counter] != '\0')
		counter++;
	while (*src != '\0' && counter < dstsize - 1)
	{
		dest[counter] = *src;
		counter++;
		src++;
	}
	dest[counter] = '\0';
	if (dstsize < size_dest)
		return (size_src + dstsize);
	return (size_dest + size_src);
}

/* #include <string.h>
#include <stdio.h>

int main()
{	
	unsigned int const size = 20;
	unsigned int const distsize = 20;
	int len = 0;


	// ============ Check std Strlcpy ===============
	char strl_dest[size] = "1234";
	char strl_src[] = "567890";
	printf("\n============ Check buildin Strlcat ============\n");
	len = strlcat(strl_dest, strl_src, distsize);
	printf("strlcpy: len: %i, str: %s\n", len, strl_dest);

	char strl_dest1[size] = "hellof";
	char strl_src1[] = "byby";
	
	len = strlcat(strl_dest1, strl_src1, distsize);
	printf("strlcpy: len: %i, str: %s\n", len, strl_dest1);
	
	char strl_dest2[size] = "no";
	char strl_src2[] = "yeshelloby";
	
	len = strlcat(strl_dest2, strl_src2, distsize);
	printf("strlcpy: len: %i, str: %s\n", len, strl_dest2);


	// ============ Check custom Strlcat ===============
	printf("\n============ Check custom Strlcat ============\n");
	char ft_dest[size] = "1234";
	char ft_tsrc[] = "567890";
	
	len = ft_strlcat(ft_dest, ft_tsrc, distsize);
	printf("ft_strlcpy: len: %i, str: %s\n", len, ft_dest);

	char ft_dest1[size] = "hellof";
	char ft_tsrc1[] = "byby";
	
	len = ft_strlcat(ft_dest1, ft_tsrc1, distsize);
	printf("ft_strlcpy: len: %i, str: %s\n", len, ft_dest1);
	
	char ft_dest2[size] = "no";
	char ft_tsrc2[] = "yeshelloby";
	
	len = ft_strlcat(ft_dest2, ft_tsrc2, distsize);
	printf("ft_strlcpy: len: %i, str: %s\n", len, ft_dest2);
}  */