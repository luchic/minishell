/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 22:56:55 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/09 20:10:36 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len_s;
	char	*ptr;

	len_s = ft_strlen(s);
	if ((unsigned char) c == '\0')
		return ((char *)s + len_s);
	ptr = NULL;
	while (len_s > 0)
	{
		if (s[len_s - 1] == (unsigned char)c)
		{
			ptr = (char *)&s[len_s - 1];
			return (ptr);
		}
		len_s--;
	}
	return (NULL);
}

/* #include <stdio.h>
#include <string.h>

int main(void)
{
	const char	s[] = "adcdddddd";
	int			c = 'c';

	printf("%s \n",ft_strrchr(s, c));
	printf("%s \n",strrchr(s, c));

	return 0;
} */
