/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:39:22 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/17 18:45:02 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_redirection_token(t_tokenstream *ts)
{
	if (ts_match(ts, REDIRECT_IN) || ts_match(ts, REDIRECT_OUT) || ts_match(ts,
			REDIRECT_APPEND) || ts_match(ts, HEREDOC))
		return (1);
	return (0);
}

int	set_redirection(t_command *cmd, t_tokenstream *ts)
{
	int	exit_code;

	while (is_redirection_token(ts))
	{
		exit_code = cmd_set_redirection(cmd, ts);
		if (exit_code == SYNTAX_ERROR)
			cmd->mnsh->last_exit_status = SYNTAX_ERROR;
		if (exit_code == 0)
			return (ft_log_fd(LOG_ERROR, ERROR, "Failed to set redirection\n"),
				0);
	}
	return (1);
}
