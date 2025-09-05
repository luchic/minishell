/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:44:17 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/05 13:13:40 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_substrin(const char *str, const char *substr, size_t reminder)
{
	size_t	len_needle;

	len_needle = ft_strlen(substr);
	if (len_needle > reminder)
		return (0);
	while (*substr != '\0')
	{
		if (*str != *substr)
			return (0);
		str++;
		substr++;
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (haystack == NULL && needle != NULL && len == 0)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0' && i < len)
	{
		if (is_substrin(haystack, needle, len - i))
			return ((char *)haystack);
		haystack++;
		i++;
	}
	return (NULL);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (haystack == NULL && needle != NULL)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	len = ft_strlen(haystack);
	while (*haystack != '\0')
	{
		if (is_substrin(haystack, needle, len - i))
			return ((char *)haystack);
		haystack++;
		i++;
	}
	return (NULL);
}
