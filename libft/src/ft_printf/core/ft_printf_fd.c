/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:19:21 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/19 16:51:16 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_vfprintf_fd.h"

int	ft_printf_fd(int fd, const char *format, ...)
{
	int		res;
	va_list	ap;

	if (fd < 0)
		return (-1);
	va_start(ap, format);
	res = ft_vfprintf_fd(ap, format, fd);
	va_end(ap);
	return (res);
}
