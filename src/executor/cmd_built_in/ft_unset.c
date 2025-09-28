/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:44:09 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/28 15:51:24 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

static int	is_var_in_shell_vars(char *name)
{
	t_minishell	*mnsh;
	t_list		*vars;
	t_list		*current;

	mnsh = *get_mnsh();
	vars = mnsh->variables;
	current = vars;
	while (current)
	{
		if (ft_strcmp(((t_var *)current->content)->name, name) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

static void	ft_list_remove(t_list **lst, int (*f)(char *), void (*del)(void *))
{
	t_list	*prev;
	t_list	*current;
	int		found_var;

	if (!lst || !f || !del)
		return ;
	prev = NULL;
	found_var = 0;
	current = *lst;
	while (current)
	{
		if (f(((t_var *)current->content)->name))
		{
			if (prev)
				prev->next = current->next;
			else
				*lst = current->next;
			ft_lstdelone(current, del);
			return ;
		}
		prev = current;
		current = current->next;
	}
	return ;
}

int	ft_unset(t_command *cmd)
{
	int		i;
	char	***envp;

	if (count_args(cmd->args) < 2)
		return (EXIT_SUCCESS);
	envp = &(cmd->mnsh->envp);
	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_identifier(cmd->args[i]))
		{
			ft_array_remove(envp, cmd->args[i]);
			ft_list_remove(&(cmd->mnsh->variables), is_var_in_shell_vars,
				free_variable);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
