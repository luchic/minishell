/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:58:09 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/14 13:59:12 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*node;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (!content)
			return (ft_lstclear(&new_lst, del), NULL);
		node = ft_lstnew(content);
		if (!node)
		{
			del(content);
			return (ft_lstclear(&new_lst, del), NULL);
		}
		ft_lstadd_back(&new_lst, node);
		lst = lst->next;
	}
	return (new_lst);
}

/*
t_list	*ft_lstmap(t_list *lst, void *(f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*prev_node;
	t_list	*nxt_node;
	void	*content;

	if (!lst || !f)
		return (NULL);
	new_lst = ft_lstnew(f(lst->content));
	if (!new_lst)
		return (NULL);
	prev_node = new_lst;
	lst = lst->next;
	while (lst != NULL)
	{
		content = f(lst->content);
		nxt_node = ft_lstnew(content);
		if (!nxt_node)
		{
			del(content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		prev_node->next = nxt_node;
		prev_node = nxt_node;
		lst = lst->next;
	}
	return (new_lst);
}
 */
