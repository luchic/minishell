/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wld_utlis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:03:02 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/24 15:03:03 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	parse_wildcards(t_exp_info *info, t_token *token,
		int (*is_qted)(t_quote_status))
{
	char	*pos;

	pos = ft_strchr_escaped(info->res + info->size, '*');
	while (pos)
	{
		info->res[pos - info->res - 1] = SENTINEL;
		ft_memmove(pos, pos + 1, ft_strlen(pos + 1) + 1);
		pos = ft_strchr_escaped(pos, '*');
	}
	if (is_qted(token->quote_status))
	{
		pos = ft_strchr(info->res + info->size, '*');
		while (pos)
		{
			info->res[pos - info->res] = SENTINEL;
			pos = ft_strchr(pos + 1, '*');
		}
	}
}

static int	is_last_token(t_tokenstream *ts)
{
	t_tokenstream	*copy;
	int				res;

	copy = ts_clone(ts);
	if (!copy)
		return (0);
	ts_advance(copy);
	res = 0;
	if (ts_peek(copy) == NULL)
		res = 1;
	ts_free(copy);
	return (res);
}

static int	update_value(t_exp_info *info, t_token *token, int is_last)
{
	char	*pos;
	int		exit_status;

	if (ft_append_str(&info->res, token->value) == -1)
		return (-1);
	pos = ft_strchr_not_escaped(token->value, '$');
	while (pos)
	{
		if (*(pos + 1) == '\0' && !token->is_space_after && !is_last)
		{
			info->res[ft_strlen(info->res) - 1] = '\0';
			break ;
		}
		exit_status = handle_var(info->size, pos, token, info->expand);
		if (exit_status == -1)
			return (-1);
		pos = ft_strchr_not_escaped(pos + 1, '$');
	}
	parse_wildcards(info, token, is_single_or_double);
	return (1);
}

void	release_escaped_char(char *str, char c)
{
	char	*pos;

	pos = ft_strchr_escaped(str, c);
	while (pos)
	{
		ft_memmove(pos - 1, pos, ft_strlen(pos) + 1);
		pos = ft_strchr_escaped(pos, c);
	}
}

int	set_merged_value(char **value, t_list **expander, t_tokenstream *ts)
{
	t_token		*token;
	t_exp_info	info;

	token = ts_peek(ts);
	if (!token)
		return (0);
	ft_bzero(&info, sizeof(t_exp_info));
	info.expand = expander;
	if (update_value(&info, token, is_last_token(ts)) == -1)
		return (free(info.res), -1);
	while (ts_match(ts, WORD))
	{
		token = ts_peek(ts);
		ts_advance(ts);
		if (!token || token->is_space_after)
			return (*value = info.res, 1);
		token = ts_peek(ts);
		if (!token || !ts_match(ts, WORD))
			break ;
		info.size = ft_strlen(info.res);
		if (update_value(&info, token, is_last_token(ts)) == -1)
			return (free(info.res), -1);
	}
	return (*value = info.res, 1);
}
