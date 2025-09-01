/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:03:05 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/13 18:28:54 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = (char *)ft_calloc((len_s1 + len_s2 + 1), sizeof(char));
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, len_s1 + len_s2 + 1);
	ft_strlcat(join, s2, len_s1 + len_s2 + 1);
	return (join);
}
