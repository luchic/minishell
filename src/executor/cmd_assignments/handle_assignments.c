/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_assignments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:43:00 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/29 13:51:08 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "ft_defines.h"
#include "ft_executor.h"
#include "libft.h"
#include "minishell.h"

static void	check(char *name, char *arg)
{
	char	*value;
	char	***envp;

	value = get_env(name);
	if (!value)
		return ;
	envp = &((*get_mnsh())->envp);
	update_env_var(arg, envp);
	free(value);
}

static t_list	*get_env_local_node(char *name)
{
	t_list		*node;
	t_minishell	*mnsh;

	mnsh = *get_mnsh();
	if (!mnsh || !name || !mnsh->variables)
		return (NULL);
	node = mnsh->variables;
	while (node)
	{
		if (node && ft_strcmp(((t_var *)node->content)->name, name) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

static int	create_new_node(char *name, char *value)
{
	t_minishell	*mnsh;
	t_list		*node;
	t_var		*var;

	mnsh = *get_mnsh();
	var = ft_calloc(1, sizeof(t_var));
	if (!mnsh || !var)
		return (free(var), -1);
	node = ft_lstnew(var);
	if (!node)
		return (free(var), -1);
	var->name = name;
	var->value = value;
	ft_lstadd_back(&mnsh->variables, node);
	return (0);
}

static void	update_mnsh_vars(t_assignment *asgmt)
{
	t_minishell	*mnsh;
	t_list		*node;
	char		*name;
	char		*value;

	mnsh = *get_mnsh();
	name = ft_substr(asgmt->value, 0, ft_strchr(asgmt->value, '=')
			- asgmt->value);
	if (!name)
		return ;
	value = ft_strdup(ft_strchr(asgmt->value, '=') + 1);
	if (!value)
		return (free(name));
	node = get_env_local_node(name);
	check(name, asgmt->value);
	if (node)
	{
		free(name);
		free(((t_var *)(node->content))->value);
		((t_var *)(node->content))->value = value;
		return ;
	}
	if (create_new_node(name, value) == -1)
		return (free(name), free(value));
}

char	**handle_assignments(t_minishell *mnsh, t_list *assignments)
{
	t_list			*current;
	t_assignment	*asgmt;
	char			**original_env;

	current = assignments;
	original_env = ft_strdup_array(mnsh->envp);
	if (!original_env)
		return (NULL);
	while (current)
	{
		asgmt = (t_assignment *)current->content;
		if (!is_valid_identifier(asgmt->value) || !ft_strchr(asgmt->value, '='))
		{
			ft_printf_fd(STDERR,
				"minishell: assignment: `%s': not a valid identifier\n",
				asgmt->value);
			current = current->next;
			continue ;
		}
		if (ft_strchr(asgmt->value, '='))
			update_mnsh_vars(asgmt);
		current = current->next;
	}
	return (original_env);
}
