/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_assignment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:59:08 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/15 21:04:22 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "lexer.h"
#include <stdlib.h>

int	token_assignment(t_list **token, const char *input)
{
	t_list	*head;
	int		exit_code;

	head = NULL;
	exit_code = ft_split_tokens(&head, input);
	if (exit_code == FAIL)
		return (FAIL);
	else if (exit_code == SYNTAX_ERROR)
	{
		ft_lstclear(&head, free_tokens);
		return (SYNTAX_ERROR);
	}
	*token = head;
	return (0);
}
