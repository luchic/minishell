/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:51:14 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/22 14:06:42 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char) c == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}

/* int main(void)
{
	const char	s[] = "abcdefghijklmnopqrstuvwxzy";
	int			c = -100;

	printf("%s \n",ft_strchr(s, c));
	printf("%s \n",strchr(s, c));

	return 0;
} */
