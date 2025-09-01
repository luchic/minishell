/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:32:10 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/11 13:44:09 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ptr;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/* char	f(unsigned int i, char c)
{
	char	z;
	char	*str = "0123456789";

	z = str[i % ft_strlen(str)];
	return (0);
}

int	main(void)
{
	char const *s="abcdefghijklmnopqrstuvwxyz";

	printf("%s ", ft_strmapi(s, f));
} */
