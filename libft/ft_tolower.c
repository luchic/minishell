/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:49:46 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/04 21:50:46 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		c = c + 'a' - 'A';
	}
	return (c);
}

/* #include<stdio.h>
int	main(void)
{
	int	c;

	c = 'Z';
	printf("%c ", ft_tolower(c));
} */
