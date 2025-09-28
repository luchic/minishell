/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_assignments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:43:00 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/28 11:08:13 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "ft_defines.h"
#include "ft_executor.h"
#include "libft.h"
#include "minishell.h"

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

static void	create_new_node(t_list **node, t_var **var, char *name)
{
	t_minishell	*mnsh;
	
	mnsh = *get_mnsh();
	*var = ft_calloc(1, sizeof(t_var));
	if (!mnsh || !var)
		return (free(*var));
	*node = ft_lstnew(*var);
	if (!*node)
		return (free(*var));
	(*var)->name = name;
	if (!(*var)->name)
		return (free(*var), free(*node));
	(*var)->value = ft_strdup(ft_strchr(name, '=') + 1);
	if (!(*var)->value)
		return (free((*var)->name), free(*var), free(*node));
	ft_lstadd_back(&mnsh->variables, *node);
	if (!*node)
		return ;
}

static void	update_mnsh_vars(t_assignment *asgmt)
{
	t_minishell	*mnsh;
	t_list		*node;
	t_var		*var;
	char		*name;

	mnsh = *get_mnsh();
	name = ft_substr(asgmt->value, 0, ft_strchr(asgmt->value, '=')
			- asgmt->value);
	if (!name)
		return ;
	node = get_env_local_node(name);
	if (node)
	{
		free(name);
		free(((t_var *)(node->content))->value);
		((t_var *)(node->content))->value = ft_strdup(ft_strchr(asgmt->value,
					'=') + 1);
		return ;
	}
	// var = ft_calloc(1, sizeof(t_var));
	// if (!mnsh || !var)
	// 	return (free(var));
	// node = ft_lstnew(var);
	// if (!node)
	// 	return (free(var));
	// var->name = name;
	// if (!var->name)
	// 	return (free(var), free(node));
	// var->value = ft_strdup(ft_strchr(asgmt->value, '=') + 1);
	// if (!var->value)
	// 	return (free(var->name), free(var), free(node));
	// ft_lstadd_back(&mnsh->variables, node);
	// if (!node)
	// 	return ;

	create_new_node(&node, &var, name);
	if (!node)
		return ;
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
