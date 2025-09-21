

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

static int	handle_special_var(char **new_arg, int *st, t_expander *exp,
		t_minishell *mnsh)
{
	char	*tmp;
	char	*env;

	env = NULL;
	if (ft_strcmp(exp->var_name, "?") == 0)
	{
		env = ft_itoa(mnsh->last_exit_status);
		if (!env)
			return (-1);
		tmp = ft_replace(*new_arg, env, *st + exp->var_start, *st
				+ exp->var_end);
		ft_memmove(*new_arg + *st + exp->var_end, *new_arg + *st + exp->var_end
			+ 1, ft_strlen(*new_arg + *st + exp->var_end + 1) + 1);
		*st += ft_strlen(env) - 2;
		if (!tmp)
			return (free(env), -1);
		return (*new_arg = tmp, free(env), 0);
	}
	return (1);
}

static int	append_new_var(int *st, char **new_arg, t_expander *exp,
		t_minishell *mnsh)
{
	char	*tmp;
	char	*env;

	env = NULL;
	ft_log_fd(LOG_INFO, STDOUT, "Expanding variable at pos %d to %d\n",
		exp->var_start, exp->var_end);
	if (ft_strcmp(exp->var_name, "?") == 0)
	{
		if (handle_special_var(new_arg, st, exp, mnsh) == -1)
			return (-1);
		return (0);
	}
	env = get_env(mnsh, exp->var_name);
	if (!env)
		env = ft_strdup("");
	tmp = ft_replace(*new_arg, env, *st + exp->var_start, *st + exp->var_end);
	if (env && *env == '\0')
		ft_memmove(*new_arg + *st + exp->var_start, *new_arg + *st
			+ exp->var_end + 1, ft_strlen(*new_arg + *st + exp->var_end + 1)
			+ 1);
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
