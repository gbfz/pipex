#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include <string.h>	// TODO:
# include <stdio.h>		// TODO:

//			PIPE
typedef struct s_pipe
{
	int				fd;
	struct s_pipe	*next;
}				t_pipe;

void		append_pipe(t_pipe **head, int new_fd[2]);
t_pipe		*get_pipe_list(void);
t_pipe		**get_pipe_list_addr(void);
int			get_fd_from_pipe_list(void);
void		free_pipe_list(void);

//			PID list
typedef struct s_pid_list
{
	pid_t				pid;
	struct s_pid_list	*next;
}				t_pid_list;

t_pid_list	*get_pid_list(void);
t_pid_list	**get_pid_list_addr(void);
void		append_pid(t_pid_list **list, pid_t new_pid);
void		free_pid_list(void);

//			CMD check
int			check_cmds(int cmd_count, char **args, char **envp);

//			CMD args
char		**get_cmd_args(const char *cmd);
void		free_cmd_args(char **args);

//			Heredoc

//			Exit code
int			get_exit_code(void);
int			set_exit_code(int new_code);

#endif
