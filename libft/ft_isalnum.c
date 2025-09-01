/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:41:31 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/09 16:12:58 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= 48 && c <= 57))
		return (1);
	return (0);
}

/* #include<stdio.h>

int	main(void)
{
	unsigned char	c;

	c = 9;
	printf("%d", ft_isalnum(c));
} */
