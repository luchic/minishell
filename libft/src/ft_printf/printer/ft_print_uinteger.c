/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uinteger.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:27:36 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/29 14:02:26 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defs.h"
#include "ft_printer.h"
#include "ft_utils.h"
#include "libft.h"

static int	ft_putunsigned(unsigned int unum, t_format *cur, int fd)
{
	if (cur->format == 'x')
		return (ft_putulnbr_base_fd(unum, "0123456789abcdef", fd));
	else if (cur->format == 'X')
		return (ft_putulnbr_base_fd(unum, "0123456789ABCDEF", fd));
	else
		return (ft_putulnbr_base_fd(unum, "0123456789", fd));
}

static int	ft_print_uzero(unsigned int unum, t_format *cur, int fd)
{
	int	nsize;
	int	res;

	nsize = ft_getsize_numformat(unum, cur);
	if (cur->flags & (FLAG_DOT))
	{
		if (ft_fillspace(cur->precision - nsize, '0', fd) == -1)
			return (-1);
		if (cur->precision == 0 && unum == 0)
			return (0);
	}
	else if (cur->flags & FLAG_ZERO && !(cur->flags & FLAG_DOT))
	{
		if (cur->flags & FLAG_HASH && (cur->format == 'x' || cur->format == 'X')
			&& unum != 0)
			nsize += 2;
		if (ft_fillspace(cur->width - nsize, '0', fd) == -1)
			return (-1);
	}
	res = ft_putunsigned(unum, cur, fd);
	if (res == -1)
		return (-1);
	return (ft_max(res, cur->precision));
}

static int	ft_print_usign(unsigned int unum, t_format *cur, int fd)
{
	int		res;
	char	*sign;

	if (cur->format == 'x')
		sign = "0x";
	else
		sign = "0X";
	if (cur->flags & (FLAG_HASH) && (cur->format == 'x' || cur->format == 'X')
		&& unum != 0)
	{
		if (ft_putstr_fd(sign, fd) == -1)
			return (-1);
		res = ft_print_uzero(unum, cur, fd);
		if (res == -1)
			return (-1);
		return (res + 2);
	}
	return (ft_print_uzero(unum, cur, fd));
}

static int	ft_uszie_output(unsigned int unum, t_format *cur)
{
	int	size;
	int	nsize;

	size = 0;
	nsize = ft_getsize_numformat(unum, cur);
	if ((cur->format == 'x' || cur->format == 'X') && cur->flags & FLAG_HASH
		&& unum != 0)
		size += 2;
	size += ft_max(nsize, cur->precision);
	return (size);
}

int	ft_print_unit(va_list ap, t_format *cur, int fd)
{
	unsigned int	unum;
	int				res;
	int				is_error;
	int				fl;

	unum = va_arg(ap, unsigned int);
	is_error = 0;
	fl = cur->flags;
	res = ft_uszie_output(unum, cur);
	if (!(fl & FLAG_MINUS) && (!(fl & FLAG_ZERO) || (fl & FLAG_DOT)))
	{
		if ((fl & FLAG_DOT) && cur->precision == 0 && unum == 0)
			res--;
		is_error = ft_fillspace(cur->width - res, ' ', fd);
	}
	if (is_error == -1)
		return (-1);
	res = ft_print_usign(unum, cur, fd);
	if (res == -1)
		return (-1);
	if ((fl & FLAG_MINUS))
		is_error = ft_fillspace(cur->width - res, ' ', fd);
	if (is_error == -1)
		return (-1);
	return (ft_max(cur->width, res));
}
