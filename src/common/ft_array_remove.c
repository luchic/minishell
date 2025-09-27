/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 09:16:24 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/27 17:17:04 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "libft.h"

static void	ft_create_new_array(char ***array, char *value)
{
	char	**envp;
	char	**new_array;
	int		i;
	int		j;

	envp = *array;
	new_array = malloc(sizeof(char *) * (count_args(envp) + 1));
	if (!new_array)
		return ;
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], value, ft_strlen(value)) != 0)
		{
			new_array[j] = envp[i];
			j++;
		}
		else
			free(envp[i]);
		i++;
	}
	new_array[j] = NULL;
	free(envp);
	*array = new_array;
}

void	ft_array_remove(char ***array, char *value)
{
	char	**envp;
	int		i;

	if (!array || !*array || !value)
		return ;
	envp = *array;
	i = 0;
	while (envp[i] && is_var_in_envp(envp[i], value) == 0)
		i++;
	if (!envp[i])
		return ;
	ft_create_new_array(array, value);
}

// void	ft_array_remove(char ***array, char *value)
// {
// 	int		i;
// 	int		j;
// 	char	**envp;
// 	char	**new_array;

// 	if (!array || !*array || !value)
// 		return ;
// 	i = 0;
// 	envp = *array;
// 	while (envp[i] && is_valid_name(envp[i], value) == 0)
// 		i++;
// 	if (!envp[i])
// 		return ;
// 	new_array = malloc(sizeof(char *) * (count_args(envp) + 1));
// 	if (!new_array)
// 		return ;
// 	j = 0;
// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], value, ft_strlen(value)) != 0)
// 		{
// 			new_array[j] = envp[i];
// 			j++;
// 		}
// 		else
// 			free(envp[i]);
// 		i++;
// 	}
// 	new_array[j] = NULL;
// 	free(envp);
// 	*array = new_array;
// }
