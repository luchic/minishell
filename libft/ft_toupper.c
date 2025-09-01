/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:31:24 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/04 21:49:30 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		c = c + 'A' - 'a';
	}
	return (c);
}

/* #include<stdio.h>
int	main(void)
{
	int	c;

	c = 'z';
	printf("%c ", ft_toupper(c));
} */
