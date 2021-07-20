#include "pipex.h"

static size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	if (dst == NULL || src == NULL)
		return (0);
	if (*src == '\0' || len == 0)
		return (0);
	*dst = *src;
	return (1 + ft_strlcpy(dst + 1, src + 1, len - 1));
}

char	*ft_strjoin(const char *a, const char *b)
{
	char	*n;
	int		alen;
	int		blen;

	if (a == NULL || b == NULL)
		return (NULL);
	alen = ft_strlen(a);
	blen = ft_strlen(b);
	n = malloc(alen + blen + 1);
	if (n == NULL)
		return (NULL);
	ft_strlcpy(n, a, alen);
	ft_strlcpy(n + alen, b, blen + 1);
	return (n);
}
