/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:56:53 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/26 18:56:55 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "libft.h"

int	append_char(char **dst, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	return (ft_append_str(dst, buf));
}

int	is_name_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
