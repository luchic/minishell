/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:04:48 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/29 14:04:25 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defs.h"
#include "libft.h"
#include "ft_utils.h"

int	ft_puthex_fd(unsigned long num, int fd)
{
	return (ft_putulnbr_base_fd(num, "0123456789abcdef", fd));
}
#if defined(__linux__)

int	ft_size_ptr(void *ptr, t_format *cur)
{
	int	size;
	int	nsize;
	int	fl;

	size = 0;
	if (!ptr)
		return (NPTRSIZE);
	fl = cur->flags;
	if (!(fl & FLAG_MINUS) && (fl & (FLAG_PLUS | FLAG_SPACE)))
		size++;
	nsize = ft_getsize_unsigned((unsigned long)ptr, 16);
	size += ft_max(nsize, cur->precision) + 2;
	return (size);
}

int	ft_print_nullptr(void *ptr, int fd)
{
	if (!ptr)
		return (ft_putstr_fd(PTRNULL, fd));
	return (0);
}
#elif defined(__APPLE__)

int	ft_size_ptr(void *ptr, t_format *cur)
{
	int	size;
	int	nsize;

	size = 0;
	nsize = ft_getsize_unsigned((unsigned long)ptr, 16);
	size += (ft_max(nsize, cur->precision) + 2);
	return (size);
}

int	ft_print_nullptr(void *ptr, int fd)
{
	(void)ptr;
	(void)fd;
	return (0);
}

#endif