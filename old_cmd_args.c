#include "pipex.h"

/*
static int	append_path(char **arg, char **paths)
{
	char	*arg_with_path;
	char	*cmd;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		cmd = ft_strndup(*arg, wordlen(*arg, ' '));
		arg_with_path = ft_strjoin(paths[i], *arg);
		if (access(arg_with_path, X_OK) == 0)
		{
			*arg = arg_with_path;
			return (0);
		}
		free(arg_with_path);
		i++;
	}
	printf("%s: command not found\n", *arg);
	return (1);
}

int	check_cmds(char **args, char **envp)
{
	char	**paths;
	int		i;
	int		ret;

	paths = get_paths(envp);
	if (paths == NULL)
		return (1);
	i = 0;
	ret = 0;
	while (args[i + 1] != NULL)
	{
		if (access(args[i], X_OK) != 0)
			if (append_path(args + i, paths) != 0)
				ret = 1;
		i++;
	}
	free_string_arr(paths);
	return (ret);
}
*/
