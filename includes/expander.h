/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:52:31 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/13 14:57:13 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "ft_defines.h"

// ======================= Expander Var ========================
int	run_variable_expander(t_command *cmd);
int	run_wildcards_expander(t_command *cmd);

#endif