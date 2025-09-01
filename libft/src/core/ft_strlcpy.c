/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:45:29 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/08 18:58:24 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	counter;
	size_t	src_size;

	src_size = ft_strlen(src);
	if (dstsize == 0)
		return (src_size);
	counter = 0;
	while (counter < dstsize - 1 && src[counter] != '\0')
	{
		dest[counter] = src[counter];
		counter++;
	}
	dest[counter] = '\0';
	return (src_size);
}

/* #include <string.h>
#include <stdio.h>

int main()
{
	unsigned int const size = 20;
	unsigned int const distsize = 0;
	int len = 0;
	// ============ Check std Strlcpy ===============

	char strl_dest[size] = "hello,-world";
	char strl_src[] = "1234567adsfdsaf";
	
	printf("\n============ Check buildin Strlcpy ============\n");
	len = strlcpy(strl_dest, strl_src, distsize);
	printf("strlcpy: len: %i, str: %s\n", len, strl_dest);

	char strl_dest1[size] = "hello";
	char strl_src1[] = "byby";
	
	len = strlcpy(strl_dest1, strl_src1, distsize);
	printf("strlcpy: len: %i, str: %s\n", len, strl_dest1);
	
	char strl_dest2[size] = "no";
	char strl_src2[] = "yes";
	
	len = strlcpy(strl_dest2, strl_src2, distsize);
	printf("strlcpy: len: %i, str: %s\n", len, strl_dest2);


	// ============ Check custom Strlcpy ===============
	printf("\n============ Check custom Strlcpy ============\n");
	char ft_dest[size] = "hello,-world";
	char ft_tsrc[] = "1234567adsfdsaf";
	
	len = ft_strlcpy(ft_dest, ft_tsrc, distsize);
	printf("ft_strlcpy: len: %i, str: %s\n", len, ft_dest);

	char ft_dest1[size] = "hello";
	char ft_tsrc1[] = "byby";
	
	len = ft_strlcpy(ft_dest1, ft_tsrc1, distsize);
	printf("ft_strlcpy: len: %i, str: %s\n", len, ft_dest1);
	
	char ft_dest2[size] = "no";
	char ft_tsrc2[] = "yes";
	
	len = ft_strlcpy(ft_dest2, ft_tsrc2, distsize);
	printf("ft_strlcpy: len: %i, str: %s\n", len, ft_dest2);
} */