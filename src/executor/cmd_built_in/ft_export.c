/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:43:45 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/26 20:49:39 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

int	is_valid_identifier(char *str)
{
	if (!str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	while (*str && *str != '=')
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (0);
		str++;
	}
	return (1);
}

void	replace_env_var(char **env_var, char *new_var)
{
	char	*tmp;

	tmp = ft_strdup(new_var);
	if (!tmp)
		return ;
	free(*env_var);
	*env_var = tmp;
}

void	append_env_var(char ***envp, char *new_var)
{
	char	**tmp;
	char	*copy;

	copy = ft_strdup(new_var);
	if (!copy)
		return ;
	tmp = ft_array_append(*envp, copy);
	if (!tmp)
		return (free(copy));
	*envp = tmp;
}

void	update_env_var(char *arg, char ***envp)
{
	char	*var;
	int		i;

	if (ft_strchr(arg, '='))
		var = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	else
		var = ft_strdup(arg);
	if (!var)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], var, ft_strlen(var)) == 0
			&& (*envp)[i][ft_strlen(var)] == '=')
		{
			replace_env_var(&((*envp)[i]), arg);
			return (free(var));
		}
		i++;
	}
	append_env_var(envp, arg);
	free(var);
}

int	ft_export(t_command *cmd)
{
	char	***envp;
	int		i;
	int		status;

	if (cmd->args && !cmd->args[1])
		return (ft_export_print_env(cmd->mnsh->envp, STDOUT), 0);
	envp = &(cmd->mnsh->envp);
	status = 0;
	i = 1;
	while (cmd->args && cmd->args[i])
	{
		if (is_valid_identifier(cmd->args[i]) == 0)
		{
			ft_printf_fd(STDERR, "export: `%s': not a valid identifier\n",
				cmd->args[i]);
			status = EXIT_FAILURE;
		}
		else
		{
			update_env_var(cmd->args[i], envp);
		}
		i++;
	}
	return (status);
}
