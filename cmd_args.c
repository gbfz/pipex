#include "pipex.h"

static int	ft_strlen(const char *s)
{
	if (s == NULL || *s == '\0')
		return (0);
	return (1 + ft_strlen(s + 1));
}

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

static int	wordlen(const char *cmd)
{
	if (cmd == NULL || *cmd == '\0' || ft_isspace(*cmd))
		return (0);
	return (1 + wordlen(cmd + 1));
}

static int	blocklen(const char *cmd)
{
	int	i;

	i = wordlen(cmd);
	while (ft_isspace(cmd[i]))
		i++;
	return (i);
}

static int	count_words(const char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i] != '\0')
	{
		i += blocklen(cmd + i);
		count++;
	}
	return (count);
}

static char	*ft_strndup(const char *s, int len)
{
	char	*n;
	int		i;
	int		slen;

	slen = ft_strlen(s);
	if (len > slen)
		len = slen;
	n = malloc(len + 1);
	i = 0;
	while (s[i] && i < len)
	{
		n[i] = s[i];
		i++;
	}
	n[i] = '\0';
	return (n);
}

char	**get_cmd_args(const char *cmd)
{
	char	**args;
	int		words_count;
	int		i;

	words_count = count_words(cmd);
	args = malloc(sizeof(char *) * (words_count + 1));
	i = 0;
	while (i < words_count)
	{
		args[i++] = ft_strndup(cmd, wordlen(cmd));
		cmd += blocklen(cmd);
	}
	args[i] = NULL;
	return (args);
}

void	free_cmd_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		free(args[i++]);
	free(args);
}
