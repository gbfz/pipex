#include "pipex.h"

static t_pid_list	**pid_singleton(void)
{
	static t_pid_list	*saved_ptr;

	return (&saved_ptr);
}

t_pid_list	*get_pid_list(void)
{
	return (*pid_singleton());
}

t_pid_list	**get_pid_list_addr(void)
{
	return (pid_singleton());
}

void	append_pid(t_pid_list **list, pid_t new_pid)
{
	if (*list == NULL)
	{
		*list = malloc(sizeof(t_pid_list));
		(*list)->pid = new_pid;
		(*list)->next = NULL;
		return ;
	}
	append_pid(&((*list)->next), new_pid);
}

void	free_pid_list(void)
{
	t_pid_list	**ptr;
	t_pid_list	*tmp;

	ptr = get_pid_list_addr();
	while (*ptr != NULL)
	{
		tmp = (*ptr)->next;
		free(*ptr);
		*ptr = tmp;
	}
}
