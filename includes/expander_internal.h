/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:13:28 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/24 15:16:40 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_INTERNAL_H
# define EXPANDER_INTERNAL_H

# include "parser.h"

// ======================== Wildcard utils ========================
char			*get_last_slash(const char *pattern);
char			*extract_pattern(char *pattern);
char			*get_prefix(char *pattern);
char			*get_current_path(char *format);
char			*get_slash_after(const char *pattern);
int				ft_fnmatch(char *pattern, const char *filename);
int				is_wildcard(t_command *cmd);
void			restore_str(char *str);
void			restore_str_array(char **args);
void			restore_values(t_command *cmd);
void			set_status(int *status, int new_status);

// ======================== File utils ========================
char			**get_matching_files(char *path, char *pattern, int *status);
char			*get_file_prefix(char *path, char *pattern);
int				is_arg_wildcard(char *arg);

// ======================== Wildcard Expansion ========================
char			**expand_wildcard_recursive(char *path, char *pattern,
					int *status);
t_cmd_expander	*get_arg_expander(int index, t_list *exp);
char			*extract_arg(char *arg, t_list *exp, t_minishell *mnsh);
int				expand_wildcard_redirection(t_list *redir, t_command *cmd);
char			**expand_wildcard_internal(char *pattern, int *status);
char			**expand_wildcard_internal(char *pattern, int *status);

#endif