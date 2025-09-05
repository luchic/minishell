
# include "minishell.h"

int count_args(char **args)
{
	int count = 0;
	while (args && args[count])
		count++;
	return count;
}
