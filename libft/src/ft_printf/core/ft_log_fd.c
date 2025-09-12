/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:57:29 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/12 11:19:23 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_vfprintf_fd.h"

int	ft_log_fd(t_log_level level, int fd, const char *format, ...)
{
	int		res;
	va_list	ap;

	if (fd < 0)
		return (-1);
	ft_printf("Log [%d]: Current DEBUG LEVEL: %d\n", level, DEFLOG_LEVEL);
	va_start(ap, format);
	if (level >= DEFLOG_LEVEL)
		res = ft_vfprintf_fd(ap, format, fd);
	else
		res = 0;
	va_end(ap);
	return (res);
}