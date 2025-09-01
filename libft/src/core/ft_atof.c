/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:35:59 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/30 16:40:09 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static double	ft_integer(const char **str)
{
	double	result;

	result = 0.0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	return (result);
}

static double	ft_frac(const char **str)
{
	double	frac;
	double	div;

	frac = 0.0;
	div = 10.0;
	while (**str >= '0' && **str <= '9')
	{
		frac += (**str - '0') / div;
		div *= 10.0;
		(*str)++;
	}
	return (frac);
}

double	ft_atof(const char *str)
{
	double	result;
	double	sign;
	double	frac;

	result = 0.0;
	sign = 1.0;
	frac = 0.0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1.0;
		str++;
	}
	result = ft_integer(&str);
	if (*str == '.')
		str++;
	frac = ft_frac(&str);
	return (sign * (result + frac));
}
