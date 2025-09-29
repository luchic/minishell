/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:44:09 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/29 13:50:27 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

static void	ft_list_remove(t_list **lst, char *name, void (*del)(void *))
{
	t_list	*prev;
	t_list	*current;
	int		found_var;

	if (!lst || !name || !del)
		return ;
	prev = NULL;
	found_var = 0;
	current = *lst;
	while (current)
	{
		if (ft_strcmp(((t_var *)current->content)->name, name) == 0)
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
			ft_list_remove(&(cmd->mnsh->variables), cmd->args[i],
				free_variable);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
