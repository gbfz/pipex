#include "pipex.h"

static int	ft_strcmp(const char *a, const char *b)
{
	if (a == NULL || b == NULL)
		return (0);
	if ((*a != *b) || !*a || !*b)
		return (*a - *b);
	return (ft_strcmp(a + 1, b + 1));
}

static char	**get_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strcmp(envp[i], "PATH") == 0)
			return (ft_split(envp[i], ':'));
		i++;
	}
	return (NULL);
}

static int	append_path(char **arg, char **paths)
{
	char	*arg_with_path;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		arg_with_path = ft_strjoin(*arg, paths[i]);
		if (access(arg_with_path, X_OK) == 0)
		{
			free(*arg);
			*arg = arg_with_path;
			return (0);;
		}
		free(arg_with_path);
		i++;
	}
	printf("%s: command not found\n", *arg);
	return (1);
}

int	check_cmds(char **args, char **paths)
{
	if (*args == NULL)
		return (0);
	if (access(*args, X_OK) != 0)
		if (append_path(args, paths) == 1)
			return (1);
	return (check_cmds(args + 1, paths));
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
	return (NULL);
}

char	**get_cmd_args(const char *cmd, char **envp)
{
	static char	**paths;
	char		**args;

	if (paths == NULL)
		paths = get_paths(envp);
	args = ft_split(cmd, ' ');
	if (paths == NULL || args == NULL || check_cmds(args, paths) != 0)
	{
		free_string_arr(paths);
		free_string_arr(args);
		return (NULL);
	}
	return (args);
}
