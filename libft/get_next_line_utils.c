/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:37:43 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/22 14:11:55 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (len == 0 || start >= s_len)
	{
		substring = ft_calloc(1, 1);
		if (!substring)
			return (NULL);
		return (substring);
	}
	if (s_len - start < len)
		len = s_len - start;
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	i = 0;
	while (i < len)
		substring[i++] = s[start++];
	substring[i] = '\0';
	return (substring);
}

/* void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	total;
	size_t	i;

	total = count * size;
	ptr = (char *)malloc(total);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
} */

/* size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
} */

/* char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
} */

/* char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	total_len;
	size_t	count;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (total_len + 1));
	if (ptr == NULL)
		return (NULL);
	count = 0;
	while (*s1)
		ptr[count++] = *s1++;
	while (*s2)
		ptr[count++] = *s2++;
	ptr[count] = '\0';
	return (ptr);
} */
