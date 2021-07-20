#include "pipex.h"

static int	wordlen(const char *s, char delim)
{
	if (s == NULL || *s == '\0' || *s == delim)
		return (0);
	return (1 + wordlen(s + 1, delim));
}

static int	blocklen(const char *s, char delim)
{
	int	len;

	len = wordlen(s, delim);
	while (s[len] == delim && s[len] != '\0')
		len++;
	return (len);
}

static int	count_words(const char *s, char delim)
{
	int	count;

	count = 0;
	while (*s != '\0')
	{
		s += blocklen(s, delim);
		count++;
	}
	return (count);
}

int	ft_strlen(const char *s)
{
	if (s == NULL || *s == '\0')
		return (0);
	return (1 + ft_strlen(s + 1));
}

char	*ft_strndup(const char *s, int len)
{
	char	*n;
	int		slen;
	int		i;

	if (s == NULL || len <= 0)
		return (NULL);
	slen = ft_strlen(s);
	if (len > slen)
		len = slen;
	n = malloc(len + 1);
	if (n == NULL)
		return (NULL);
	i = 0;
	while (i < len)
		n[i++] = *s++;
	n[i] = '\0';
	return (n);
}

static char	**free_on_error(char **split, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(split[i++]);
	free(split);
	return (NULL);
}

char	**ft_split(const char *s, char delim)
{
	char	**split;
	int		words_count;
	int		i;

	words_count = count_words(s, delim);
	split = malloc(sizeof(char *) * (words_count + 1));
	if (split == NULL)
		return (NULL);
	i = 0;
	while (i < words_count)
	{
		split[i] = ft_strndup(s, wordlen(s, delim));
		if (split[i] == NULL)
			return (free_on_error(split, i));
		s += blocklen(s, delim);
		i++;
	}
	split[i] = NULL;
	return (split);
}
