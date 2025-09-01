/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:01:20 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/14 09:29:52 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*copy;

	size = ft_strlen(s1);
	copy = (char *)malloc((size + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	ft_memcpy(copy, s1, size);
	copy[size] = '\0';
	return (copy);
}

/* #include <stdio.h>
#include <string.h>
int main()
{
	char *str = "hello, world\n";
	char *cpy = ft_strdup(str);
	printf("%s", cpy);

	char *str1 = "hello, world\n";
	char *cpy1 = strdup(str1);
	if(cpy1[strlen(cpy1)] == '\0')
		printf("OK\n");
	else
		printf("KO\n");
} */