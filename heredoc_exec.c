#include "pipex.h"

static void	write_to_pipe(int fd, char **string)
{
	write(fd, *string, ft_strlen(*string));
	free(*string);
	*string = calloc(sizeof(char), 1); // TODO: replace with ft_
	write(1, "heredoc> ", 9);
}

static void	create_pipes(int cmd1_fd[2], int cmd2_fd[2],
				int file_fd)
{
	pipe(cmd1_fd);
	pipe(cmd2_fd);
	dup2(cmd1_fd[1], cmd2_fd[0]);
	dup2(cmd2_fd[1], file_fd);
}

static void	execute_heredoc(int heredoc_out, char *delim)
{
	char	*string;
	char	c;

	string = calloc(sizeof(char), 1); // TODO: replace with ft_
	write(1, "heredoc> ", 9);
	while (ft_strcmp(string, delim) != 0)
	{
		read(0, &c, 1);
		if (c != '\n')
			string = ft_strappend(string, c);
		else
			write_to_pipe(heredoc_out, &string);
	}
	close(heredoc_out);
	printf("out of cycle\n");
}

static void	execute_first_cmd(int cmd1_out, int cmd2_in, char *cmd, char **envp)
{
	char	**args;
	pid_t	pid;

	printf(" 1 >> |%s|\n", cmd);
	args = get_cmd_args(cmd);
	for (int i = 0; args[i] != NULL; i++)
		printf(" !! %s\n", args[i]);
	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, envp);
		exit(127);
	}
	close(cmd1_out);
	close(cmd2_in);
	free_string_arr(args);
	append_pid(get_pid_list_addr(), pid);
}

static void	execute_second_cmd(int cmd2_out, int file_fd, char *cmd, char **envp)
{
	char	**args;
	pid_t	pid;

	printf(" 2 >> |%s|\n", cmd);
	args = get_cmd_args(cmd);
	for (int i = 0; args[i] != NULL; i++)
		printf(" !! %s\n", args[i]);
	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, envp);
		exit(127);
	}
	close(cmd2_out);
	close(file_fd);
	free_string_arr(args);
	append_pid(get_pid_list_addr(), pid);
}

int	heredoc_exec(char **av, char **envp)
{
	int	file_fd;
	int	cmd1_fd[2];
	int	cmd2_fd[2];

	file_fd = open(av[5], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (file_fd == -1)
		return (printf("Couldn't open infile\n"));
	if (handle_cmds(av + 3, 2, envp) != 0)
		return (1);
	create_pipes(cmd1_fd, cmd2_fd, file_fd);
	execute_heredoc(cmd1_fd[0], av[2]);
	execute_first_cmd(cmd1_fd[1], cmd2_fd[0], av[3], envp);
	execute_second_cmd(cmd2_fd[1], file_fd, av[4], envp);
	wait_for_all_procs();
	return (get_exit_code());
}
