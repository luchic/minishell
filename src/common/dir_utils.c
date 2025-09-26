/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:55:41 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/26 18:55:45 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}
