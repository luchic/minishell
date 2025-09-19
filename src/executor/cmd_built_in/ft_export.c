
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

//first letter must be alpha or _
int	is_valid_identifier(char *str)
{
	if (!str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	// ft_printf_fd(STDOUT, "Validating identifier: %s\n", str); ///to delete --- IGNORE ---
	while (*str && *str != '=')
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (0);
		str++;
	}
	// ft_printf_fd(STDOUT, "Identifier valid: %s\n", str); ///to delete --- IGNORE ---
	return (1);
}

// export h, h=5
// export var=value
// export var=#$^@#$

//h, new_var = "h=5"

void	replace_env_var(char **env_var, char *new_var)
{
	// char	*new;
	char	*tmp;

    tmp = ft_strdup(new_var);
    if (!tmp)
        return ;
    free(*env_var);
    *env_var = tmp;

	// new = ft_substr(new_var, 0, ft_strchr(new_var, '=') - new_var + 1);
	// if (!new)
	// 	return ;
	// tmp = ft_strjoin(new, "\"");
	// if (!tmp)
	// 	return (free(new));
	// free(new);
	// new = ft_strjoin(tmp, ft_strchr(new_var, '=') + 1);
	// if (!new)
	// 	return (free(tmp));
	// free(tmp);
	// tmp = ft_strjoin(new, "\"");
	// if (!tmp)
	// 	return (free(new));
	// free(new);
	// tmp[ft_strlen(tmp)] = '\0';
	// new = *env_var;
	// free(new);
	// *env_var = tmp;
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
	// ft_printf_fd(STDOUT, "Appending new env var: %s\n", copy); ///to delete --- IGNORE ---
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
	// ft_printf_fd(STDOUT, "\n\nUpdating env var: %s\n", var); ///to delete --- IGNORE ---
	i = 0;
	while((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], var, ft_strlen(var)) == 0 && (*envp)[i][ft_strlen(var)] == '=')
		{
			// ft_printf_fd(STDOUT, "  Found match, replacing env[%d]: %s with %s\n", i, (*envp)[i], arg); ///to delete --- IGNORE ---
			replace_env_var(&((*envp)[i]), arg);
			return (free(var));
		}
		i++;
	}
	// ft_printf_fd(STDOUT, "  No match found, appending new var: %s\n", arg); ///to delete --- IGNORE ---
	append_env_var(envp, arg);
	free(var);
}


// if no args, print env sorted by name
// if args, for each one: validate identifier:
// - if not valid, print error and continue
// - if validate, update or add to env

int	ft_export(t_command *cmd)
{
	char	***envp;
	int		i;
	int		status;

	if (cmd->args && !cmd->args[1])
		return (ft_export_print_env(cmd->mnsh->envp, STDOUT), 0);
	
	envp = &(cmd->mnsh->envp);
	// ft_printf_fd(STDOUT, "Running export with args:\n"); ///to delete --- IGNORE ---
	// ft_printf_fd(STDOUT, "  Arg[0]: %s\n", cmd->args[0]); ///to delete --- IGNORE ---
	// ft_printf_fd(STDOUT, "  Arg[1]: %s\n", cmd->args[1]); ///to delete --- IGNORE ---
	// ft_printf_fd(STDOUT, "  Arg[2]: %s\n", cmd->args[2]); ///to delete --- IGNORE ---
	status = 0;
	i = EXIT_SUCCESS;
	while (cmd->args && cmd->args[i])
	{
		// ft_printf_fd(STDOUT, "  Arg[%d]: %s\n", i, cmd->args[i]); ///to delete --- IGNORE ---
		if (is_valid_identifier(cmd->args[i]) == 0)
		{
			ft_printf_fd(STDERR, "export: `%s': not a valid identifier\n", cmd->args[i]);
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
