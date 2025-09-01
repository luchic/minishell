/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:23:58 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/08 13:27:34 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occurrence;

	last_occurrence = NULL;
	while (*s)
	{
		if (*s == (unsigned char) c)
			last_occurrence = (char *)s;
		s++;
	}
	if (*s == (unsigned char) c)
		return ((char *)s);
	return (last_occurrence);
}

/* 
#include <stdio.h>
#include <string.h>
int main()
{
	char	*src = "there is so \0ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";

	char	*d1 = strrchr(src, '\0');
	char	*d2 = ft_strrchr(src, '\0');
	if(d1 == d2)
		printf("OK\n");
	else
		printf("KO\n");
	
	char *ch = ft_strrchr("hello", '\0');
	printf("Result: %p\n, Value: %d\n", ch, *ch);
} */