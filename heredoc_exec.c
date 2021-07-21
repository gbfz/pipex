#include "pipex.h"

static void	write_to_pipe(int fd, char **string)
{
	write(fd, *string, ft_strlen(*string));
	write(fd, "\n", 1);
	free(*string);
	*string = ft_calloc(sizeof(char), 1);
	write(1, "heredoc> ", 9);
}

static void	execute_heredoc(int cmd1_in, char *delim)
{
	char	*string;
	char	c;

	string = ft_calloc(sizeof(char), 1);
	write(1, "heredoc> ", 9);
	while (ft_strcmp(string, delim) != 0)
	{
		read(0, &c, 1);
		if (c != '\n')
			string = ft_strappend(string, c);
		else
			write_to_pipe(cmd1_in, &string);
	}
}

static void	execute_cmd(int in_fd, int out_fd, char *cmd, char **envp)
{
	char	**args;
	pid_t	pid;

	args = ft_split(cmd, ' ');
	pid = fork();
	if (pid == 0)
	{
		dup2(in_fd, 0);
		dup2(out_fd, 1);
		close(in_fd);
		close(out_fd);
		execve(args[0], args, envp);
		exit(127);
	}
	free_string_arr(args);
	append_pid(get_pid_list(), pid);
}

static void	close_all_fds(int cmd1_fd[2], int cmd2_fd[2], int file_fd)
{
	close(cmd1_fd[0]);
	close(cmd1_fd[1]);
	close(cmd2_fd[0]);
	close(cmd2_fd[1]);
	close(file_fd);
}

int	heredoc_exec(char **av, char **envp)
{
	int		file_fd;
	int		cmd1_fd[2];
	int		cmd2_fd[2];
	pid_t	pid;

	file_fd = open(av[5], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (file_fd == -1)
		return (set_exit_code(ENOENT));
	pipe(cmd1_fd);
	pipe(cmd2_fd);
	execute_heredoc(cmd1_fd[1], av[2]);
	if (handle_cmds(av + 3, 2, envp) != 0)
		return (set_exit_code(ENOENT));
	pid = fork();
	if (pid == 0)
	{
		execute_cmd(cmd1_fd[0], cmd2_fd[1], av[3], envp);
		execute_cmd(cmd2_fd[0], file_fd, av[4], envp);
		exit(0);
	}
	close_all_fds(cmd1_fd, cmd2_fd, file_fd);
	wait_for_all_procs();
	free_pid_list();
	return (get_exit_code());
}
