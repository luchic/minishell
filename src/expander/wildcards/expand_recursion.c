/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_recursion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:06:49 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/16 11:33:46 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_internal.h"
#include "ft_common.h"
#include <stdlib.h>

int	ft_append_matched(char *prefix, char **matched, char ***expanded)
{
	int		i;
	char	**tmp;
	char	*value;

	i = 0;
	while (matched && matched[i])
	{
		if (prefix)
			value = ft_strjoin(prefix, matched[i]);
		else
			value = ft_strdup(matched[i]);
		if (!value)
			return (-1);
		tmp = ft_array_append(*expanded, value);
		if (!tmp)
			return (free(value), -1);
		*expanded = tmp;
		i++;
	}
	return (0);
}

static char	**get_expanded_files(char *path, char *pattern)
{
	char	**expanded;
	char	**matched;
	char	*prefix;
	char	*extracted_pattern;

	expanded = NULL;
	matched = NULL;
	extracted_pattern = extract_pattern(pattern);
	if (!extracted_pattern)
		return (NULL);
	matched = get_matching_files(path, extracted_pattern);
	free(extracted_pattern);
	if (!matched)
		return (NULL);
	prefix = get_file_prefix(path, pattern);
	if (!prefix)
	{
		free_str_array(matched);
		return (NULL);
	}
	if (ft_append_matched(prefix, matched, &expanded) == -1)
		return (free(prefix), free_str_array(matched), NULL);
	free(prefix);
	free_str_array(matched);
	return (expanded);
}

static int	expand_wildcard_recursive_core(char *npattern, char **expanded,
		char ***new, int *status)
{
	char	**sub_matched;
	int		i;

	i = 0;
	while (expanded && expanded[i])
	{
		sub_matched = expand_wildcard_recursive(expanded[i], npattern, status);
		if (sub_matched)
		{
			if (ft_append_matched(NULL, sub_matched, new) == -1)
				return (free_str_array(sub_matched), -1);
			free_str_array(sub_matched);
		}
		i++;
	}
	return (0);
}

static int	expander(char *pattern, char **expanded, char ***new, int *status)
{
	char	*last_slash;
	char	*npat;

	last_slash = get_slash_after(pattern);
	if (!last_slash || last_slash == pattern)
		return (ft_append_matched(NULL, expanded, new));
	npat = ft_strdup(last_slash);
	if (!npat)
		return (-1);
	if (expand_wildcard_recursive_core(npat, expanded, new,
			status) == -1)
	{
		return (free(npat), -1);
	}
	free(npat);
	return (0);
}

char	**expand_wildcard_recursive(char *path, char *pattern, int *status)
{
	char	**expanded;
	char	**new_expanded;

	expanded = NULL;
	new_expanded = NULL;
	if (status)
		*status = 0;
	expanded = get_expanded_files(path, pattern);
	if (!expanded)
	{
		if (status)
			*status = -1;
		return (NULL);
	}
	if (expander(pattern, expanded, &new_expanded, status) == -1)
	{
		if (status)
			*status = -1;
		free_str_array(expanded);
		return (NULL);
	}
	free_str_array(expanded);
	return (new_expanded);
}
