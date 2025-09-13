#include "ft_printf.h"
#include "ft_defines.h"
#include "libft.h"
#include <dirent.h>
#include <sys/stat.h>

char	*get_slash_after(const char *pattern)
{
	char	*slash;
	char	*star;

	star = ft_strchr(pattern, '*');
	if (!star)
		return (NULL);
	slash = ft_strrchr(star, '/');
	if (!slash)
		return ((char *)pattern);
	return (slash + 1);
}

int	ft_fnmatch(char *pattern, const char *filename)
{
	if (*pattern == '\0')
		return (*filename == '\0');
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (*pattern == '\0')
			return (1);
		while (*filename)
		{
			if (ft_fnmatch(pattern, filename))
				return (1);
			filename++;
		}
	}
	if (*pattern == *filename)
		return (ft_fnmatch(pattern + 1, filename + 1));
	return (0);
}

int	is_wildcard(char **arg)
{
	if (!arg)
	{
		return (-1);
	}
	while (**arg)
	{
		if (ft_strchr(*arg, '*'))
			return (1);
		arg++;
	}
	return (0);
}
