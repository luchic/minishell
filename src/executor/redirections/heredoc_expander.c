/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:10:33 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/26 17:14:00 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "ft_defines.h"
#include "libft.h"
#include <stdlib.h>

static int	handle_special_char(char **out, char c)
{
	char		*st;
	t_minishell	*mnsh;

	mnsh = *get_mnsh();
	if (!mnsh)
		return (-1);
	if (c == '$')
		st = ft_itoa(mnsh->last_exit_status);
	else if (c == '0')
		st = ft_strdup(PREFIX);
	else
		st = ft_strdup("");
	if (!st || ft_append_str(out, st) == -1)
		return (free(st), -1);
	free(st);
	return (0);
}

static int	handle_variable(int *i, char **out, const char *line)
{
	int			j;
	char		*name;
	char		*val;
	t_minishell	*mnsh;

	j = *i + 1;
	mnsh = *get_mnsh();
	if (!mnsh)
		return (-1);
	while (line[j] && is_name_char(line[j]))
		j++;
	name = ft_substr(line, *i + 1, j - (*i + 1));
	val = get_env(mnsh, name);
	if (!val)
		val = ft_strdup("");
	if (!name || !val || ft_append_str(out, val) == -1)
		return (free(name), free(val), -1);
	free(name);
	free(val);
	*i = j;
	return (0);
}

static int	handle_dolor_sign(int *i, char **out, const char *line, char **pos)
{
	if (line[*i] == '$' && *pos == &line[*i])
	{
		if (line[*i + 1] == '?' || line[*i + 1] == '0')
		{
			if (handle_special_char(out, line[*i + 1]) == -1)
				return (-1);
			*i += 2;
		}
		else if (is_name_start(line[*i + 1]))
		{
			if (handle_variable(i, out, line) == -1)
				return (-1);
		}
		else if (append_char(out, '$') == -1)
			return (-1);
		(*i)++;
		*pos = ft_strchr_not_escaped(line + *i, '$');
	}
	if (append_char(out, line[*i]) == -1)
		return (-1);
	(*i)++;
	return (0);
}

char	*expand_heredoc_line(const char *line)
{
	int		i;
	char	*out;
	char	*pos;

	if (!line)
		return (NULL);
	out = ft_strdup("");
	if (!out)
		return (NULL);
	i = 0;
	pos = ft_strchr_not_escaped(line, '$');
	while (line[i])
	{
		if (line[i] == '$' && pos == &line[i])
		{
			if (handle_dolor_sign(&i, &out, line, &pos) == -1)
				return (free(out), NULL);
			continue ;
		}
		if (append_char(&out, line[i]) == -1)
			return (free(out), NULL);
		i++;
	}
	return (out);
}
