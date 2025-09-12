/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:57:29 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/12 13:29:47 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_vfprintf_fd.h"

int	ft_print_log_level(t_log_level level, int fd)
{
	if (level == LOG_DEBUG)
		return (ft_printf_fd(fd, "[DEBUG] "));
	else if (level == LOG_INFO)
		return (ft_printf_fd(fd, "[INFO] "));
	else if (level == LOG_WARNING)
		return (ft_printf_fd(fd, "[WARNING] "));
	else if (level == LOG_ERROR)
		return (ft_printf_fd(fd, "[ERROR] "));
	else if (level == LOG_CRITICAL)
		return (ft_printf_fd(fd, "[CRITICAL] "));
	return (0);
}

int	ft_log_fd(t_log_level level, int fd, const char *format, ...)
{
	int		res;
	va_list	ap;

	if (fd < 0)
		return (-1);
	va_start(ap, format);
	if (level >= DEFLOG_LEVEL)
	{
		res = ft_print_log_level(level, fd);
		res += ft_vfprintf_fd(ap, format, fd);
	}
	else
		res = 0;
	va_end(ap);
	return (res);
}
