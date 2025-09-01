/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:24:21 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/09 20:11:03 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n < 1)
		return (0);
	while (n > 0)
	{
		if (*s1 == 0 && *s2 == 0)
			return (0);
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

/* #include <stdio.h>
#include <string.h>
int	main (void)
{
	char	s1[] = "\200"; //"test\200", "test\0", 6)
	char	s2[] = "\0";

	int test = ft_strncmp(s1, s2, 6);
	int temp = strncmp(s1, s2, 6);
	printf("%d \n", test);
	printf("%d ", temp);

	return (0);
}
 */
