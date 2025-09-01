/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:41:45 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/22 16:54:49 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*temp;

	if (!lst || !del)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		temp = ptr;
		if (del)
			del(ptr->content);
		ptr = ptr->next;
		free(temp);
	}
	*lst = NULL;
}

/* void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*temp;
	int		i;

	i = ft_lstsize(*lst);
	ptr = *lst;
	while (i - 1 > 0)
	{
		del(ptr->content);
		temp = ptr->next;
		free(ptr);
		ptr = temp;
		i--;
	}
	*lst = NULL;
} */
