#include "pipex.h"

static int	ft_strlen(const char *s)
{
	if (s == NULL || *s == '\0')
		return (0);
	return (1 + ft_strlen(s + 1));
}

static int	ft_strcmp(const char *a, const char *b)
{
	if (a == NULL || b == NULL)
		return (0);
	if ((*a != *b) || !*a || !*b)
		return (*a - *b);
	return (ft_strcmp(a + 1, b + 1));
}

static char	*ft_strjoin(const char *a, const char *b)
{
	char	*n;
	int		alen;
	int		blen;
	int		i;

	if (a == NULL || b == NULL)
		return (NULL);
	alen = ft_strlen(a);
	blen = ft_strlen(b);
	n = malloc(alen + blen + 1);
	i = 0;
	while (a[i] != '\0')
	{
		n[i] = a[i];
		i++;
	}
	while (b[i - alen] != '\0')
	{
		n[i] = b[i - alen];
		i++;
	}
	n[i] = '\0';
	return (n);
}

static char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strcmp(envp[i], "PATH") == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

int			check_cmds(int cmd_count, char **args, char **envp)
{
	char	*path;

	path = get_path;
	if (path == NULL)
		return (1);
}
