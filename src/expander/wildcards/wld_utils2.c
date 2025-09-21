#include "parser.h"

void restore_str(char *str)
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
	int	j;

	if (!args)
		return ;
	i = -1;
	while (args[++i])
		restore_str(args[i]);
}