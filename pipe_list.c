#include "pipex.h"

static t_pipe	*new_pipe_node(int fd)
{
	t_pipe	*node;

	node = malloc(sizeof(t_pipe));
	node->fd = fd;
	node->next = NULL;
	return (node);
}

void	append_pipe(t_pipe **head, int new_fd[2])
{
	if (*head == NULL)
	{
		*head = new_pipe_node(new_fd[1]);
		(*head)->next = new_pipe_node(new_fd[0]);
		return ;
	}
	append_pipe(&((*head)->next), new_fd);
}

static void	del_pipe_node(t_pipe **node)
{
	t_pipe	*tmp;

	tmp = (*node)->next;
	free(*node);
	*node = tmp;
}

int	get_fd_from_pipe_list(void)
{
	t_pipe	**head;
	int		fd;

	head = get_pipe_list_addr();
	if (*head == NULL)
		return (-1);
	fd = (*head)->fd;
	del_pipe_node(head);
	return (fd);
}
