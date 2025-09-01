/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putulnbr_base_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:21:50 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/18 14:41:25 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static int	ft_isgood_base(char *s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '-' || s[i] == '+')
			return (1);
		j = i + 1;
		while (s[j] != '\0')
		{
			if (s[i] == s[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	print_base_fd(unsigned long nbr, int base, char *base_tabel, int fd)
{
	char	out;
	int		res;

	if (nbr / base == 0)
		return (write(fd, &base_tabel[nbr], 1));
	out = base_tabel[nbr % base];
	nbr = nbr / base;
	res = print_base_fd(nbr, base, base_tabel, fd);
	if (res == -1)
		return (-1);
	if (write(fd, &out, 1) == -1)
		return (-1);
	return (res + 1);
}

int	ft_putulnbr_base_fd(unsigned long nbr, char *base, int fd)
{
	int		len_base;

	len_base = ft_strlen(base);
	if (ft_isgood_base(base) || len_base <= 1)
		return (-1);
	if (nbr == 0)
		return (write(fd, "0", 1));
	return (print_base_fd(nbr, len_base, base, fd));
}
