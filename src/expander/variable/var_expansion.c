#include "ft_printf.h"
#include "parser.h"

// return pointer to new string, or original one if no expansion needed
static char *handle_status_code(char *arg, char *var_position, t_minishell *mnsh)
{
	char *new_arg;
	char *status_str;

	status_str = ft_itoa(mnsh->last_exit_status);
	if (!status_str)
		return NULL;
	// TODO: check allocatied size
	new_arg = ft_calloc(ft_strlen(arg) + ft_strlen(status_str) - 1, sizeof(char));
	if (!new_arg)
	{
		free(status_str);
		return NULL;
	}
	int i = 0;
	while (&arg[i] != var_position) // -1 to include the $ sign
	{
		new_arg[i] = arg[i];
		i++;
	}

	ft_strlcat(new_arg, status_str, ft_strlen(arg) + ft_strlen(status_str) + 1);
	while (arg[i + 2]) // +2 to skip $? 
	{
		new_arg[i + ft_strlen(status_str)] = arg[i + 2];
		i++;
	}
	free(status_str);
	new_arg[i + ft_strlen(status_str)] = '\0';
	return new_arg;
}

static char *handle_path_var(char *arg, char *var_position, char *env)
{
	char *new_arg;
	char *var_value;

	var_value = env + ft_strlen(var_position + 1) + 1;
	new_arg = ft_calloc(ft_strlen(arg) + ft_strlen(var_value) + 1, sizeof(char));
	if (!new_arg)
		return NULL;
	int i = 0;
	while (&arg[i] != var_position)
	{
		new_arg[i] = arg[i];
		i++;
	}
	ft_strlcat(new_arg, var_value, ft_strlen(arg) + ft_strlen(var_value) + 1);
	return new_arg;
}

static char	*var_expansion(char *arg, char *var_position,
		t_minishell *mnsh)
{
	int	i;
	char **envp;

	if (!arg || !mnsh || !mnsh->envp)
		return (NULL);
	// Handle special case for $?
	if (var_position[0] == '$' && var_position[1] == '?')
	{
		return handle_status_code(arg, var_position, mnsh);
	}
	envp = mnsh->envp;
	for (i = 0; envp[i]; i++)
	{
		if (ft_strncmp(envp[i], var_position + 1, ft_strlen(var_position + 1)) == 0
			&& envp[i][ft_strlen(var_position + 1)] == '=')
			return (handle_path_var(arg, var_position, envp[i]));
	}
	return (ft_strdup("")); // Variable not found, return empty string
}

static char	*expand_variable_if_need(char *arg, t_minishell *mnsh)
{
	int		i;
	char	*new_arg;

	i = 0;
	while (arg && arg[i])
	{
		if (arg[i] == '$')
		{
			new_arg = var_expansion(arg, arg + i, mnsh);
			free(arg);
			return (new_arg);
		}
		i++;
	}
	return (arg);
}

void	expand_variable(t_command *cmd)
{
	int		i;
	char	**args;

	if (!cmd || !cmd->args)
		return ;
	ft_log_fd(LOG_INFO, STDOUT, "Run expand_variable: cmd: %s\n", cmd->name);
	if (!cmd->mnsh)
	{
		ft_log_fd(LOG_DEBUG, STDOUT,
			"expand_variable: minishell: Internal error: mnsh is NULL\n");
		return ;
	}
	args = (cmd->args + 1);
	for (i = 0; args && args[i]; i++)
	{
		args[i] = expand_variable_if_need(args[i], cmd->mnsh);
	}
}

