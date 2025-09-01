/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:32:28 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/29 14:01:40 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defs.h"
#include "ft_printer.h"
#include "ft_utils.h"
#include "libft.h"

static int	print_ptr_zero_flags(void *ptr, int len_p, t_format *cur, int fd)
{
	if (ft_putstr_fd("0x", fd) == -1)
		return (-1);
	if (cur->flags & FLAG_DOT)
	{
		if (ptr == 0 && cur->precision == 0)
			return (2);
		if (ft_fillspace(cur->precision - len_p, '0', fd) == -1)
			return (-1);
		if (ft_puthex_fd((unsigned long)ptr, fd) == -1)
			return (-1);
	}
	else if ((cur->flags & FLAG_ZERO) && !(cur->flags & FLAG_MINUS))
	{
		if (ft_fillspace(cur->width - len_p, '0', fd) == -1)
			return (-1);
		if (ft_puthex_fd((unsigned long)ptr, fd) == -1)
			return (-1);
	}
	else if (ft_puthex_fd((unsigned long)ptr, fd) == -1)
		return (-1);
	return (ft_max(len_p, cur->precision) + 2);
}

static int	print_ptr_zero(void *ptr, t_format *cur, int fd)
{
	int	len_p;
	int	add;

	len_p = ft_getsize_unsigned((unsigned long)ptr, 16);
	add = 0;
	if (cur->flags & (FLAG_PLUS | FLAG_SPACE))
		add = 1;
	if ((cur->flags & FLAG_ZERO) && !(cur->flags & FLAG_MINUS))
	{
		len_p += add + 2;
	}
	return (print_ptr_zero_flags(ptr, len_p, cur, fd));
}

int	ft_print_ptr_sign(void *ptr, t_format *cur, int fd)
{
	int	sign_add;
	int	res;

	sign_add = 0;
	if (cur->flags & FLAG_PLUS)
	{
		if (ft_putchar_fd('+', fd) == -1)
			return (-1);
		sign_add++;
	}
	else if (cur->flags & FLAG_SPACE)
	{
		if (ft_putchar_fd(' ', fd) == -1)
			return (-1);
		sign_add++;
	}
	res = print_ptr_zero(ptr, cur, fd);
	if (res == -1)
		return (-1);
	return (res + sign_add);
}

int	ft_print_ptr(va_list ap, t_format *cur, int fd)
{
	void	*ptr;
	int		fl;
	int		res;

	ptr = va_arg(ap, void *);
	ft_null_check(ptr, cur);
	fl = cur->flags;
	res = ft_size_ptr(ptr, cur);
	if (!(fl & FLAG_MINUS) && (!(fl & FLAG_ZERO) || (fl & FLAG_DOT)))
	{
		if (ft_fillspace(cur->width - res, ' ', fd) == -1)
			return (-1);
	}
	res = ft_print_nullptr(ptr, fd);
	if (!res)
		res = ft_print_ptr_sign(ptr, cur, fd);
	if (res == -1)
		return (-1);
	if ((fl & FLAG_MINUS) && (ft_fillspace(cur->width - res, ' ', fd) == -1))
		return (-1);
	return (ft_max(cur->width, res));
}
