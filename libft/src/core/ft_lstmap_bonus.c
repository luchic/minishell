/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:01:12 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/14 09:28:57 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	*ft_free(t_list **list, void *content, void (*del)(void *))
{
	if (content)
		del(content);
	ft_lstclear(list, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*mapped;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		mapped = f(lst->content);
		new_node = ft_lstnew(mapped);
		if (!new_node)
			return (ft_free(&new_list, mapped, del));
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

/* 
#include <stdio.h>
#include <stdlib.h>

void leaks(void)
{
	system("leaks a.out");
}

void	ft_print_result(t_list *elem)
{
	while (elem)
	{
		printf("%s\n", (char *)(elem->content));
		elem = elem->next;
	}
}

void *ft_map(void *content)
{
	char *value = (char *)content;
	char *new = (char *)malloc(30);
	
	sprintf(new, "__%s", value);
	return (new);
}


int main()
{	
	// to moc malloc i use global variable
	t_list **array;
	array = (t_list **)malloc(sizeof(t_list *));
	*array = NULL;

	ft_lstadd_back(array, ft_lstnew("Hello"));
	ft_lstadd_back(array, ft_lstnew("World"));
	ft_lstadd_back(array, ft_lstnew("42"));

	ft_print_result(*array);
	printf("\n");
	ft_lstclear(array, free);
	atexit(leaks);
	t_list *new_list = ft_lstmap(*array, ft_map, free);
	ft_print_result(new_list);
} */