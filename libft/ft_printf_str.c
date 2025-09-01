/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:24:16 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/13 10:32:23 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_str(char *s)
{
	int	i;

	if (!s)
		return (write(1, "(null)", 6));
	i = 0;
	while (s[i] != '\0')
	{
		if (write(1, &s[i], 1) < 0)
			return (-1);
		else
			i++;
	}
	return (i);
}

/* int	main(void)
{
	char	*z = "some string with %s hehe";
	int	b = ft_printf_str(z);

	printf("\n%d", b);
	printf("%s", "some string with %s hehe");
	return (0);
} */
