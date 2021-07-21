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

void	wait_for_all_procs(void)
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

	printf(" 1 >> |%s|\n", cmd);
	args = get_cmd_args(cmd);
	for (int i = 0; args[i] != NULL; i++)
		printf(" !! %s\n", args[i]);
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
	free_string_arr(args);
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
	printf(" 2 >> |%s|\n", *cmd);
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
	free_string_arr(args);
	append_pid(get_pid_list_addr(), pid);
	execute_inner_cmds(cmd_count - 1, cmd + 1, envp);
}

static void	execute_writefile_cmd(int writefile_fd, char *cmd, char **envp)
{
	int		in_fd;
	char	**args;
	pid_t	pid;

	printf(" 3 >> |%s|\n", cmd);
	args = get_cmd_args(cmd);
	for (int i = 0; args[i] != NULL; i++)
		printf(" !! %s\n", args[i]);
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
	free_string_arr(args);
	append_pid(get_pid_list_addr(), pid);
}

int	main_exec(int ac, char **av, char **envp)
{
	int	file_fd[2];

	if (handle_files(file_fd, ac, av) != 0)
		return (1);
	if (handle_cmds(av + 2, ac - 3, envp) != 0)
		return (2);
	create_pipes(ac - 4);
	execute_readfile_cmd(file_fd[0], av[2], envp);
	execute_inner_cmds(ac - 5, av + 2, envp);
	execute_writefile_cmd(file_fd[1], av[ac - 2], envp);
	wait_for_all_procs();
	close(file_fd[0]);
	close(file_fd[1]);
	return (get_exit_code());
}

int		main(int ac, char **av, char **envp)
{
	if (ac < 5)
		return (printf("At least 4 args!\n"));
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		return (heredoc_exec(av, envp));
	return (main_exec(ac, av, envp));
}
