/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:13:28 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/18 19:38:35 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_INTERNAL_H
# define EXPANDER_INTERNAL_H

# include "parser.h"

// ======================== Wildcard utils ========================
char			*get_last_slash(const char *pattern);
char			*extract_pattern(char *pattern);
char			*get_prefix(char *pattern);
int				is_directory(const char *path);
char			*get_current_path(char *format);
char			*get_slash_after(const char *pattern);
int				ft_fnmatch(char *pattern, const char *filename,
					const char *next_not_escaped);
int				is_wildcard(char **arg);

// ======================== File utils ========================
char			**get_matching_files(char *path, char *pattern);
char			*get_file_prefix(char *path, char *pattern);

// ======================== Wildcard Expansion ========================
char			**expand_wildcard_recursive(char *path, char *pattern,
					int *status);
t_cmd_expander	*get_arg_expander(int index, t_list *exp);
char			*extract_arg(char *arg, t_list *exp, t_minishell *mnsh);

#endif