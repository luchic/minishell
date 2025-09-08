/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:41:08 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/08 13:29:49 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

t_list	*create_assignments_node(t_tokenstream *ts)
{
	t_list	*head;
	t_list	*node;
	char	*assignment;

	head = NULL;
	while (ts_match(ts, VARIABLE))
	{
		assignment = ft_strdup(ts_advance(ts)->value);
		if (!assignment)
			return (ft_lstclear(&head, free), NULL);
		node = ft_lstnew(assignment);
		if (!node)
			return (free(assignment), ft_lstclear(&head, free), NULL);
		ft_lstadd_back(&head, node);
	}

	return (head);
}
