/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 23:56:48 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/14 12:07:34 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j] && i + j < len)
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}

/* #include <stdio.h>
#include <string.h>

int main(void)
{
	const char *largestring = "lorem ipsum dolor sit amet ";
	const char *smallstring = "o";
	size_t		n = 0;

	printf("%s \n",ft_strnstr(largestring, smallstring,n));
	printf("%s \n",strnstr(largestring, smallstring,n));

	return 0;
} */
