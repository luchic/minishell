
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

//first letter must be alpha or _
int	is_valid_identifier(char *str)
{
	if (!str[0] || !(ft_isalpha(str[0]) || (str[0] == '_')))
		return (0);
	while (*str && *str != '=')
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (0);
		str++;
	}
	// if (*str == '=')
	// {
	// 	if (*(str + 1) == '\0')
	// 		return (0);
	// }
	return (1);
}

// export h, h=5
// export var=value
// export var=#$^@#$

//h, new_var = "h=5"

void	replace_env_var(char **env_var, char *new_var)
{
	char	*new;
	char	*tmp;

	new = ft_substr(new_var, 0, ft_strchr(new_var, '=') - new_var + 1);
	if (!new)
		return ;
	tmp = ft_strjoin(new, "\"");
	if (!tmp)
		return (free(new));
	free(new);
	new = ft_strjoin(tmp, ft_strchr(new_var, '=') + 1);
	if (!new)
		return (free(new));
	free(tmp);
	tmp = ft_strjoin(new, "\"");
	if (!tmp)
		return (free(new));
	free(new);
	tmp[ft_strlen(tmp)] = '\0';
	new = *env_var;
	free(new);
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
	while((*envp)[i])
	{
		// find var exists in envp and has values
		if (ft_strncmp((*envp)[i], var, ft_strlen(var)) == 0 && (*envp)[i][ft_strlen(var)] == '=')
		{
			replace_env_var(&((*envp)[i]), arg);
			return (free(var));
		}
		i++;
	}
	append_env_var(envp, arg);
	free(var);
}


// if no args, print env sorted by name
// if args, for each one: validate identifier:
// - if not valid, print error and continue
// - if validate, update or add to env

int	ft_export(t_command *cmd)
{
	char	**envp;
	int		i;

	if (!cmd->args[1])
		return (ft_export_print_env(cmd->mnsh->envp, STDOUT), 0); // could be replaced by cmd->fd_out
	envp = cmd->mnsh->envp;
	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_identifier(cmd->args[i]))
		{
			ft_printf_fd(STDERR, "export: `%s': not a valid identifier\n", cmd->args[i]);
		}
		else
		{
			update_env_var(cmd->args[i], &envp);
		}
		i++;
	}
	return (0);
}
