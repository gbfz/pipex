#include "pipex.h"

static void	execute_heredoc(int fd[2], char *delim)
{
	char	*string;

	pipe(fd);
	close(fd[0]);
	string = calloc(sizeof(char), 1); // TODO: replace with ft_
	while (ft_strcmp(string, delim) != 0)
	{
	}
}

void	heredoc_exec(int file_fd[2], char **av, char **envp)
{
	int	heredoc_fd[2];
	int	cmd1_fd[2];
	int	cmd2_fd[2];

	execute_heredoc(heredoc_fd, av[2]);
}
