#include "pipex.h"

int		main(int ac, char **av, char **envp)
{
	if (ac < 5)
		return (write(1, "At least 4 args!\n", 17)); // TODO: bonus.....
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		return (heredoc_exec(av, envp));
	return (main_exec(ac, av, envp));
}
