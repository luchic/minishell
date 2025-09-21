
#include "libft.h"

static int	is_escaped_at(const char *start, const char *pos)
{
	int			back_slashes;
	const char	*p = pos;

	back_slashes = 0;
	while (p > start && *(p - 1) == '\\')
	{
		back_slashes++;
		p--;
	}
	return (back_slashes & 1);
}

char	*ft_strchr_escaped(const char *s, int c)
{
	const char	*p;

	if (!s)
		return (NULL);
	p = s;
	while (*p)
	{
		if (*p == (char)c && is_escaped_at(s, p))
			return ((char *)p);
		p++;
	}
	return (NULL);
}

char	*ft_strchr_not_escaped(const char *s, int c)
{
	const char	*p;

	if (!s)
		return (NULL);
	p = s;
	while (*p)
	{
		if (*p == (char)c && !is_escaped_at(s, p))
			return ((char *)p);
		p++;
	}
	if ((char)c == '\0')
		return ((char *)p);
	return (NULL);
}
