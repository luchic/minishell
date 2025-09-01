/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_platform_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:13:28 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/29 13:39:51 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defs.h"

#if defined(__linux__)

void	ft_null_check(void *ptr, t_format *cur)
{
	if (!ptr)
	{
		if (cur->flags & FLAG_DOT)
			cur->precision = 0;
		cur->flags &= ~(FLAG_SPACE | FLAG_PLUS | FLAG_ZERO | FLAG_DOT);
	}
}
#elif defined(__APPLE__)

void	ft_null_check(void *ptr, t_format *cur)
{
	(void)ptr;
	(void)cur;
}

#endif