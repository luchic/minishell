#include "parser.h"

void	restore_str(char *str)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
	{
		if (str[i] == SENTINEL)
			str[i] = '*';
	}
}

void	restore_str_array(char **args)
{
	int	i;

	if (!args)
		return ;
	i = -1;
	while (args[++i])
		restore_str(args[i]);
}

void	restore_values(t_command *cmd)
{
	t_list			*cur;
	t_redirection	*redir;
	t_assignment	*asgmt;

	restore_str_array(cmd->args);
	cur = cmd->redirections;
	while (cur)
	{
		redir = (t_redirection *)cur->content;
		if (redir)
			restore_str(redir->value);
		cur = cur->next;
	}
	cur = cmd->assignments;
	while (cur)
	{
		asgmt = (t_assignment *)cur->content;
		if (asgmt)
			restore_str(asgmt->value);
		cur = cur->next;
	}
}

void	set_status(int *status, int new_status)
{
	if (status)
		*status = new_status;
}
