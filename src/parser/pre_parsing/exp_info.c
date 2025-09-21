/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:25:18 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/21 14:49:44 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "libft.h"
#include "parser.h"
#include <stdlib.h>

int	is_single_quoted(t_quote_status status)
{
	if (status == SINGLE_QUOTED)
		return (1);
	return (0);
}

// int	handle_wildcard(int count, t_token *token, t_list **expand,
// 		int (*is_quoted)(t_quote_status))
// {
// 	t_list	*new_node;

// 	if (is_quoted(token->quote_status))
// 		return (0);
// 	new_node = add_wld_expander(count);
// 	if (!new_node)
// 		return (-1);
// 	ft_lstadd_back(expand, new_node);
// 	return (1);
// }

static t_list	*add_var_expander(t_var_handle info, t_token *token)
{
	t_list		*new_node;
	t_expander	*var_exp;

	var_exp = ft_calloc(1, sizeof(t_expander));
	if (!var_exp)
		return (NULL);
	new_node = ft_lstnew(var_exp);
	if (!new_node)
		return (free_expander(var_exp), NULL);
	var_exp->var_name = ft_substr(info.begin, 1, info.var_end - info.begin - 1);
	if (!var_exp->var_name)
		return (free_expander(var_exp), free(new_node), NULL);
	var_exp->var_start = info.size + (info.begin - token->value);
	var_exp->var_end = info.size + (info.var_end - token->value) - 1;
	return (new_node);
}

int	handle_var(int size, char *var_pos, t_token *token, t_list **expand)
{
	char			*var_end;
	t_var_handle	info;
	t_list			*new_node;

	var_end = var_pos + 1;
	if (!var_end || *var_end == '\0' || token->quote_status == SINGLE_QUOTED)
		return (0);
	if (*var_end == '?')
	{
		info = (t_var_handle){size, var_pos, var_end + 1};
		new_node = add_var_expander(info, token);
		if (!new_node)
			return (-1);
		ft_lstadd_back(expand, new_node);
		return (1);
	}
	if ((!ft_isalpha(*var_end) && *var_end != '_'))
		return (0);
	while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
		var_end++;
	info = (t_var_handle){size, var_pos, var_end};
	new_node = add_var_expander(info, token);
	if (!new_node)
		return (-1);
	return (ft_lstadd_back(expand, new_node), 1);
}
