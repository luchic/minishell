/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:56:24 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/16 19:29:39 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "parser.h"

static int	add_var_expander(t_var_handle info, t_token *token,
		t_assignment *assignment)
{
	t_list		*new_node;
	t_expander	*var_exp;

	var_exp = ft_calloc(1, sizeof(t_expander));
	if (!var_exp)
		return (-1);
	new_node = ft_lstnew(var_exp);
	if (!new_node)
		return (free(var_exp), -1);
	var_exp->type = VAR;
	var_exp->var = ft_calloc(1, sizeof(t_var_expand));
	if (!var_exp->var)
		return (free(var_exp), free(new_node), -1);
	var_exp->var->var_name = ft_substr(info.begin, 1, info.var_end - info.begin
			- 1);
	if (!var_exp->var->var_name)
		return (free(var_exp->var), free(var_exp), free(new_node), -1);
	var_exp->var->var_start = info.size + (info.begin - token->value);
	var_exp->var->var_end = info.size + (info.var_end - token->value) - 1;
	ft_lstadd_back(&assignment->expand, new_node);
	return (1);
}

static int	handle_var(int size, char *var_pos, t_token *token,
		t_assignment *assignment)
{
	char			*var_end;
	t_var_handle	info;

	var_end = var_pos + 1;
	if (!var_end || *var_end == '\0')
		return (0);
	if (*var_end == '?')
	{
		info = (t_var_handle){size, var_pos, var_end};
		if (add_var_expander(info, token, assignment) == -1)
			return (-1);
		return (1);
	}
	if ((!ft_isalpha(*var_end) && *var_end != '_'))
		return (0);
	while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
		var_end++;
	info = (t_var_handle){size, var_pos, var_end};
	if (add_var_expander(info, token, assignment) == -1)
		return (-1);
	return (1);
}

int	handle_expander_if_need(int size, t_token *token, t_assignment *assignment)
{
	char	*value;
	char	*var_pos;

	if (token->quote_status == SINGLE_QUOTED)
		return (0);
	value = token->value;
	if (!value)
		return (0);
	var_pos = ft_strchr_not_escaped(value, '$');
	while (var_pos)
	{
		if (handle_var(size, var_pos, token, assignment) == -1)
			return (-1);
		var_pos = ft_strchr_not_escaped(var_pos + 1, '$');
	}
	return (1);
}
