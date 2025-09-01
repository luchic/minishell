/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:52:34 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/09 20:00:11 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	first;
	size_t	last;

	if (!s1 || !set)
		return (NULL);
	first = 0;
	last = ft_strlen(s1);
	while (s1[first] && in_set(s1[first], set))
		first++;
	while (last > first && in_set(s1[last - 1], set))
		last--;
	new = (char *)malloc(sizeof(char) * (last - first + 1));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, s1 + first, last - first + 1);
	return (new);
}

/* int	main(void)
{
	char const	*s1 =  "...../,./.de123d,.//ede4de  ./,sdf"; //"deabc";
	char const	*set = ",./";

	printf("%s", ft_strtrim(s1, set));
}
 */
/* 如果 s1 是 abcdabcd，set 是 ab，那么 strtrim 应该返回 cdabcd。因为 strtrim
 只会去掉 s1 开头和结尾的 set 中的字符，而不会去掉中间的字符。 */
