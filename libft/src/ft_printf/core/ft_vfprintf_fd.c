/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:13:37 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/19 16:51:00 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defs.h"
#include "ft_parser.h"
#include "ft_printer.h"
#include "ft_vfprintf_fd.h"
#include "libft.h"

int	ft_vfprintf_fd(va_list ap, const char *format, int fd)
{
	t_format	cur;
	int			res;
	int			tmp;

	res = 0;
	while (*format)
	{
		if (*format != '%')
		{
			if (ft_putchar_fd(*format, fd) == -1)
				return (-1);
			res++;
			format++;
			continue ;
		}
		format += ft_parse(format, &cur);
		tmp = ft_print_format(&cur, ap, fd);
		if (tmp == -1)
			return (-1);
		res += tmp;
	}
	return (res);
}
