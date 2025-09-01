/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:00:32 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/26 17:54:46 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
}

/* int	main(void)
{
	char const	*s1 = "ab";
	char const	*s2 = " cde";

	printf("%s ", ft_strjoin(s1, s2));
} */
