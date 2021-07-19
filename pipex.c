#include "pipex.h"

static int	handle_files(int file_fd[2], int ac, char **av)
{
	file_fd[0] = open(av[1], O_RDONLY);
	if (file_fd[0] == -1)
		return (printf("Couldn't open outfile\n"));
	file_fd[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (file_fd[1] == -1)
		return (printf("Couldn't open infile\n"));
	return (0);
}

static void	wait_for_all_procs(void)
{
	t_pid_list	*list;
	int			stat_loc;

	list = get_pid_list();
	while (list != NULL)
	{
		waitpid(list->pid, &stat_loc, 0);
		if (WIFEXITED(stat_loc))
			set_exit_code(WEXITSTATUS(stat_loc));
		if (WIFSIGNALED(stat_loc))
			set_exit_code(WTERMSIG(stat_loc));
		list = list->next;
	}
}

void	create_pipes(int cmd_count)
{
	int	fd[2];

	if (cmd_count == 0)
		return ;
	pipe(fd);
	append_pipe(get_pipe_list_addr(), fd);
	create_pipes(cmd_count - 1);
}

static void	execute_readfile_cmd(int readfile_fd, char *cmd, char **envp)
{
	int		out_fd;
	char	**args;
	pid_t	pid;

	args = get_cmd_args(cmd);
	out_fd = get_fd_from_pipe_list();
	pid = fork();
	if (pid == 0)
	{
		dup2(readfile_fd, 0);
		dup2(out_fd, 1);
		close(out_fd);
		close(readfile_fd);
		execve(args[0], args, envp);
		exit(127);
	}
	close(out_fd);
	free_cmd_args(args);
	append_pid(get_pid_list_addr(), pid);
}

static void	execute_inner_cmds(int cmd_count, char **cmd, char **envp)
{
	int		in_fd;
	int		out_fd;
	char	**args;
	pid_t	pid;

	if (cmd_count == 0)
		return ;
	args = get_cmd_args(*cmd);
	in_fd = get_fd_from_pipe_list();
	out_fd = get_fd_from_pipe_list();
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
	close(in_fd);
	close(out_fd);
	free_cmd_args(args);
	append_pid(get_pid_list_addr(), pid);
	execute_inner_cmds(cmd_count - 1, cmd + 1, envp);
}

static void	execute_writefile_cmd(int writefile_fd, char *cmd, char **envp)
{
	int		in_fd;
	char	**args;
	pid_t	pid;

	args = get_cmd_args(cmd);
	in_fd = get_fd_from_pipe_list();
	pid = fork();
	if (pid == 0)
	{
		dup2(in_fd, 0);
		dup2(writefile_fd, 1);
		close(in_fd);
		close(writefile_fd);
		execve(args[0], args, envp);
		exit(127);
	}
	close(in_fd);
	free_cmd_args(args);
	append_pid(get_pid_list_addr(), pid);
}

static int	ft_strcmp(const char *a, const char *b)
{
	if (a == NULL || b == NULL)
		return (0);
	if ((*a != *b) || !*a || !*b)
		return (*a - *b);
	return (ft_strcmp(a + 1, b + 1));
}

static int	main_exec(int ac, char **av, char **envp)
{
	int	file_fd[2];

	if (handle_files(file_fd, ac, av) != 0)
		return (1);
	check_cmds(ac - 3, av, envp);
	create_pipes(ac - 4);
	execute_readfile_cmd(file_fd[0], av[2], envp);
	execute_inner_cmds(ac - 5, av + 3, envp);
	execute_writefile_cmd(file_fd[1], av[ac - 2], envp);
	wait_for_all_procs();
	close(file_fd[0]);
	close(file_fd[1]);
	return (get_exit_code());
}

static int	heredoc_exec(int ac, char **av, char **envp)
{
	/*
	int		heredoc_fd[2];
	int		leftcmd_fd[2];
	int		rightcmd_fd[2];
	int		file_fd;
	pid_t	heredoc_pid;
	pid_t	leftcmd_pid;
	pid_t	rightcmd_pid;

	if (ac != 6)
	{
		printf("5 args needed in heredoc\n");
		return (1);
	}
	file_fd = open(av[ac - 1], O_RDONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (file_fd == -1)
	{
		printf("Couldn't open write file in heredoc\n");
		return (1);
	}
	pipe(heredoc_fd);
	pipe(leftcmd_fd);
	pipe(rightcmd_fd);
	dup2(heredoc_fd[1], leftcmd_fd[0]);
	dup2(leftcmd_fd[1], rightcmd_fd[0]);
	dup2(rightcmd_fd[1], file_fd);
	close(heredoc_fd[0]);
	*/
	return (0);
}

int		main(int ac, char **av, char **envp)
{
	if (ac < 5)
		return (printf("At least 4 args!\n"));
	if (ft_strcmp(av[1], "here_doc") == 0)
		return (heredoc_exec(ac, av, envp));
	return (main_exec(ac, av, envp));
}
