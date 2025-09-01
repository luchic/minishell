/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 22:59:47 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/20 16:25:16 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (len == 0 || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

// int	main(void)
// {
// 	// char const	s[] = "lorem ipsum dolor sit amet";
// 	// unsigned int	start = 400;
// 	// size_t	len = 20;

// 	printf("%s\n", ft_substr("abc\\d", 0, 4));
// }
