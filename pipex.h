#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>

# include <string.h>	// TODO:
# include <stdio.h>		// TODO:

//			Main exec
int			main_exec(int ac, char **av, char **evnp);

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

t_pid_list	**get_pid_list(void);
void		append_pid(t_pid_list **list, pid_t new_pid);
void		free_pid_list(void);
void		wait_for_all_procs(void);

//			CMD args
int			handle_cmds(char **cmds, int cmd_count, char **envp);
char		**get_cmd_args(const char *cmd);

//			Heredoc
int			heredoc_exec(char **av, char **envp);

//			Exit code
int			get_exit_code(void);
int			set_exit_code(int new_code);

//			String shit
int			ft_strlen(const char *s);
char		*ft_strdup(const char *s);
char		*ft_strndup(const char *s, int len);
char		**ft_split(const char *s, char delim);
char		*ft_strjoin(const char *a, const char *b);
int			ft_strncmp(const char *a, const char *b, size_t n);
int			ft_strcmp(const char *a, const char *b);
char		**free_string_arr(char **arr);
int			wordlen(const char *s, char delim);
int			blocklen(const char *s, char delim);
int			ft_strlen(const char *s);
char		*ft_strappend(char *s, char c);

#endif
