#include "pipex.h"

int	wordlen(const char *s, char delim)
{
	if (s == NULL || *s == '\0' || *s == delim)
		return (0);
	return (1 + wordlen(s + 1, delim));
}

int	blocklen(const char *s, char delim)
{
	int	len;

	len = wordlen(s, delim);
	while (s[len] == delim && s[len] != '\0')
		len++;
	return (len);
}

int	ft_strlen(const char *s)
{
	if (s == NULL || *s == '\0')
		return (0);
	return (1 + ft_strlen(s + 1));
}

char	*ft_strdup(const char *s)
{
	char	*n;
	int		i;

	if (s == NULL)
		return (NULL);
	n = malloc(ft_strlen(s) + 1);
	if (n == NULL)
		return (NULL);
	i = 0;
	while (*s != '\0')
		n[i++] = *s++;
	n[i] = '\0';
	return (n);
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

int	ft_strncmp(const char *a, const char *b, size_t n)
{
	if (a == NULL || b == NULL)
		return (0);
	if (*a != *b || !*a || !*b || n == 1)
		return (*a - *b);
	return (ft_strncmp(a + 1, b + 1, n - 1));
}

int	ft_strcmp(const char *a, const char *b)
{
	if (a == NULL || b == NULL)
		return (0);
	if (*a != *b || !*a || !*b)
		return (*a - *b);
	return (ft_strcmp(a + 1, b + 1));
}

char	**free_string_arr(char **arr)
{
	int	i;

	if (arr == NULL)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
	return (arr = NULL);
}

char	*ft_strappend(char *s, char c)
{
	char	*n;
	int		i;

	if (s == NULL)
		return (NULL);
	n = malloc(ft_strlen(s) + 2);
	if (n == NULL)
		return (NULL);
	i = 0;
	while (*s != '\0')
		n[i++] = *s++;
	n[i++] = c;
	n[i] = '\0';
	free(s);
	return (n);
}
