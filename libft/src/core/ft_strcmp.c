/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:27:19 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/10 18:55:14 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	ch1;
	unsigned char	ch2;

	while (*s1 && *s2)
	{
		ch1 = (unsigned char) *s1;
		ch2 = (unsigned char) *s2;
		if (ch1 - ch2 != 0 || ch1 == '\0' || ch2 == '\0')
		{
			return (ch1 - ch2);
		}
		s1++;
		s2++;
	}
	return ((unsigned char) *s1 - (unsigned char) *s2);
}
