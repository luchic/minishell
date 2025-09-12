
#include "expander.h"
#include "parser.h"

char **get_current_files_in_dir(char *dir_path)
{
	// Placeholder for directory reading logic
	// This function should return a NULL-terminated array of strings
	// representing the files in the specified directory.
	return NULL;
}

char *get_full_path(char *format)
{
	// Placeholder for path joining logic
	// This function should return a new string that is the concatenation
	// of dir and file with a '/' in between.
	return NULL;
}

void run_expander(t_command *cmd)
{
	char **args;
	int i;

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