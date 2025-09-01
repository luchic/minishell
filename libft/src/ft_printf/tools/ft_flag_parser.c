/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:45:40 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/29 14:03:07 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defs.h"
#include "libft.h"

int	ft_get_datatype(char c)
{
	if (c == 'c')
		return (CHAR);
	else if (c == '%')
		return (NONE);
	else if (c == 's')
		return (STR);
	else if (c == 'p')
		return (PTR);
	else if (c == 'd' || c == 'i')
		return (INT);
	else if (c == 'u')
		return (UINT);
	else if (c == 'x' || c == 'X')
		return (UINT);
	return (NONE);
}

int	ft_get_flag(const char *format)
{
	char	c;

	c = *format;
	if (c == '-')
		return (FLAG_MINUS);
	else if (*(format - 1) != '.' && c == '0')
		return (FLAG_ZERO);
	else if (c == '.')
		return (FLAG_DOT);
	else if (c == '#')
		return (FLAG_HASH);
	else if (c == '+')
		return (FLAG_PLUS);
	else if (c == ' ')
		return (FLAG_SPACE);
	return (NO_FLAG);
}

int	ft_isflag(char c)
{
	return (c == '-' || c == '0' || c == '.' || c == '#' || c == '+'
		|| c == ' ');
}

int	ft_istype(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%');
}

int	ft_is_valid_char(char c)
{
	if (ft_isflag(c))
		return (1);
	else if (c == '*')
		return (1);
	else if (ft_istype(c))
		return (1);
	else if (ft_isdigit(c))
		return (1);
	return (0);
}
