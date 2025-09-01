/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlnbr_base_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:23:53 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/14 13:27:07 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putlnbr_base_fd(long nbr, char *base, int fd)
{
	unsigned long	ln;

	ln = nbr;
	return (ft_putulnbr_base_fd(ln, base, fd));
}
