/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:59:17 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/15 20:59:28 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_printf.h"

static int	count_unmatched_close(const char *str)
{
	int	i;
	int	valid;
	int	unmatched;

	valid = 0;
	unmatched = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '(')
			valid++;
		else if (str[i] == ')')
		{
			if (valid > 0)
				valid--;
			else
				unmatched++;
		}
	}
	return (unmatched);
}

static int	count_unmatched_open(const char *str)
{
	int	unmatched;
	int	i;

	unmatched = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '(')
			unmatched++;
		else if (str[i] == ')')
		{
			if (unmatched > 0)
				unmatched--;
		}
	}
	return (unmatched);
}

static int	is_valid(const char *str)
{
	int	unmatched_close;
	int	unmatched_open;

	unmatched_close = count_unmatched_close(str);
	if (unmatched_close > 0)
	{
		ft_printf_fd(STDERR, "%s: %s `)'\n", PREFIX, UNEXPECTED_TOKEN);
		return (SYNTAX_ERROR);
	}
	unmatched_open = count_unmatched_open(str);
	if (unmatched_open > 0)
	{
		ft_printf_fd(STDERR, "%s: %s `('\n", PREFIX, UNEXPECTED_TOKEN);
		return (SYNTAX_ERROR);
	}
	return (0);
}

int	validate_parantheses(const char *input)
{
	return (is_valid(input));
}
