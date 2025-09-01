/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:10:18 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/12 20:26:25 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnstr_fd(char *s, int n, int fd)
{
	int	res;

	res = 0;
	if (!s)
		return (-1);
	while (*s && res < n)
	{
		if (ft_putchar_fd(*s++, fd) == -1)
			return (-1);
		res++;
	}
	return (res);
}
