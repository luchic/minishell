
#include "expander_internal.h"
#include "ft_printf.h"
#include "parser.h"

static char	*expand_variable_if_need(int index, char *arg, t_command *cmd)
{
	t_cmd_expander	*expander;
	char			*new_arg;

	expander = get_arg_expander(index, cmd->expander);
	if (!expander)
		return (ft_strdup(arg));
	new_arg = extract_arg(arg, expander->expand, cmd->mnsh);
	if (!new_arg)
		return (NULL);
	return (new_arg);
}

int	expand_assignments(t_list *asgmts, t_minishell *mnsh)
{
	t_list			*current;
	t_assignment	*asgmt;
	char			*new_value;

	ft_log_fd(LOG_INFO, STDOUT, "Expand assignments\n");
	if (!asgmts || !mnsh)
		return (0);
	current = asgmts;
	while (current)
	{
		asgmt = (t_assignment *)current->content;
		if (asgmt && asgmt->value && asgmt->expand)
		{
			new_value = extract_arg(asgmt->value, asgmt->expand, mnsh);
			if (!new_value)
				return (-1);
			free(asgmt->value);
			asgmt->value = new_value;
		}
		current = current->next;
	}
	return (0);
}

int	expand_redirection(t_list *redirections, t_command *cmd)
{
	t_list			*current;
	t_redirection	*redir;
	char			*new_value;

	if (!redirections || !cmd)
		return (0);
	current = redirections;
	while (current)
	{
		redir = (t_redirection *)current->content;
		if (redir && redir->value && redir->expander)
		{
			new_value = extract_arg(redir->value, redir->expander, cmd->mnsh);
			if (!new_value)
				return (-1);
			free(redir->value);
			redir->value = new_value;
		}
		current = current->next;
	}
	return (0);
}

int	run_args_expander(t_command *cmd)
{
	int		i;
	char	**args;
	char	*new_arg;

	i = -1;
	args = cmd->args;
	while (args && args[++i])
	{
		new_arg = expand_variable_if_need(i, args[i], cmd);
		if (!new_arg)
			return (-1);
		free(args[i]);
		args[i] = new_arg;
	}
	return (0);
}

int	run_variable_expander(t_command *cmd)
{
	if (!cmd)
		return (0);
	ft_log_fd(LOG_INFO, STDOUT, "Run expand_variable: cmd: %s\n", cmd->name);
	if (!cmd->mnsh)
	{
		ft_log_fd(LOG_ERROR, STDERR, "expand_variable: minishell: Internal error: mnsh is NULL\n");
		return (0);
	}
	if (cmd->args && cmd->expander && run_args_expander(cmd) == -1)
		return (-1);
	if (expand_assignments(cmd->assignments, cmd->mnsh) == -1)
		return (-1);
	if (expand_redirection(cmd->redirections, cmd) == -1)
		return (-1);
	ft_log_fd(LOG_INFO, STDOUT, "Finished redirection expansion with cmd: %s\n", cmd->name);
	return (1);
}
