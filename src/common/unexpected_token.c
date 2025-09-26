/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:51:09 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/26 18:56:39 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"

static void	unexpected_token(t_token_type type)
{
	if (type == PIPE)
		ft_printf_fd(STDERR, "`|'\n");
	else if (type == AND)
		ft_printf_fd(STDERR, "`&&'\n");
	else if (type == OR)
		ft_printf_fd(STDERR, "`||'\n");
	else if (type == AMPERSAND)
		ft_printf_fd(STDERR, "`&'\n");
	else if (type == SEMICOLON)
		ft_printf_fd(STDERR, "`;'\n");
	else if (type == REDIRECT_IN)
		ft_printf_fd(STDERR, "`<'\n");
	else if (type == REDIRECT_OUT)
		ft_printf_fd(STDERR, "`>'\n");
	else if (type == REDIRECT_APPEND)
		ft_printf_fd(STDERR, "`>>'\n");
	else if (type == HEREDOC)
		ft_printf_fd(STDERR, "`<<'\n");
	else if (type == PAREN_OPEN)
		ft_printf_fd(STDERR, "`('\n");
	else if (type == PAREN_CLOSE)
		ft_printf_fd(STDERR, "`)'\n");
	else
		ft_printf_fd(STDERR, "\n");
}

void	msg_unexpected_token(t_token *token)
{
	ft_printf_fd(STDERR, "%s: %s ", PREFIX, UNEXPECTED_TOKEN);
	if (token)
		unexpected_token(token->type);
	else
		ft_printf_fd(STDERR, "`EOF'\n");
}

void	msg_unexpected_token_type(t_token_type type)
{
	ft_printf_fd(STDERR, "%s: %s ", PREFIX, UNEXPECTED_TOKEN);
	unexpected_token(type);
}
