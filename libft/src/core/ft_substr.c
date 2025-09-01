/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:04:40 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/14 11:05:52 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*cpy;
	size_t	len_s;
	size_t	i;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start > len_s)
		return (ft_strdup(""));
	cpy = (char *)ft_calloc(ft_min(len_s - start, len) + 1, sizeof(char));
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < len && s[i + start])
	{
		cpy[i] = s[i + start];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

/* #include <stdio.h>
int main()
{
	char *str;

	char *exp  = ft_substr(str, 400, 20);
	printf("Result: %s\n", exp);
} */