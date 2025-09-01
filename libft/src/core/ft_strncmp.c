/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:27:19 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/04 16:19:51 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	ch1;
	unsigned char	ch2;
	size_t			counter;

	counter = 0;
	while (counter < n)
	{
		ch1 = (unsigned char) *s1;
		ch2 = (unsigned char) *s2;
		if (ch1 - ch2 != 0 || ch1 == '\0' || ch2 == '\0')
		{
			return (ch1 - ch2);
		}
		s1++;
		s2++;
		counter++;
	}
	return (0);
}
