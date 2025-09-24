/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extracter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:08:39 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/24 15:08:42 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "ft_defines.h"
#include "libft.h"

t_cmd_expander	*get_arg_expander(int index, t_list *exp)
{
	t_cmd_expander	*cmd_exp;

	if (!exp)
		return (NULL);
	while (exp)
	{
		cmd_exp = (t_cmd_expander *)exp->content;
		if (cmd_exp->index == index)
			return (cmd_exp);
		exp = exp->next;
	}
	return (NULL);
}

static char	*get_var_value(t_minishell *mnsh, const char *name)
{
	char	*env;

	if (ft_strcmp(name, "0") == 0)
		return (ft_strdup(PREFIX));
	if (ft_strcmp(name, "?") == 0)
		return (ft_itoa(mnsh->last_exit_status));
	env = get_env(mnsh, name);
	if (!env)
		return (ft_strdup(""));
	return (env);
}

static int	append_new_var(int *st, char **new_arg, t_expander *exp,
		t_minishell *mnsh)
{
	char	*tmp;
	char	*env;

	env = NULL;
	ft_log_fd(LOG_INFO, STDERR, "Expanding variable at pos %d to %d\n",
		exp->var_start, exp->var_end);
	env = get_var_value(mnsh, exp->var_name);
	if (!env)
		return (-1);
	tmp = ft_replace(*new_arg, env, *st + exp->var_start, *st + exp->var_end);
	if (!tmp)
		return (free(env), -1);
	*st += ft_strlen(env) - (exp->var_end - exp->var_start + 1);
	return (free(*new_arg), *new_arg = tmp, free(env), 0);
}

char	*extract_arg(char *arg, t_list *exp, t_minishell *mnsh)
{
	t_expander	*expander;
	char		*new_arg;
	int			shift;

	if (!exp)
		return (NULL);
	new_arg = ft_strdup(arg);
	if (!new_arg)
		return (NULL);
	shift = 0;
	while (exp)
	{
		expander = (t_expander *)exp->content;
		if (!expander)
		{
			exp = exp->next;
			continue ;
		}
		if (!expander || !expander->var_name)
			return (free(new_arg), NULL);
		if (append_new_var(&shift, &new_arg, expander, mnsh) == -1)
			return (free(new_arg), NULL);
		exp = exp->next;
	}
	return (new_arg);
}
