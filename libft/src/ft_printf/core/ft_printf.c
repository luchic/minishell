/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:26:50 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/29 13:33:33 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vfprintf_fd.h"
#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		res;
	va_list	ap;

	va_start(ap, format);
	res = ft_vfprintf_fd(ap, format, 1);
	va_end(ap);
	return (res);
}
