/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:54:36 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/12 15:58:06 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	res;

	res = 0;
	if (!s)
		return (-1);
	while (*s)
	{
		if (ft_putchar_fd(*s++, fd) == -1)
			return (-1);
		res++;
	}
	return (res);
}
