#include "get_next_line.h"

void disp_brain(t_gnl *b)
{
	if (b)
	{
		printf("--- BRAIN FD %d ---\n\
		line: %s\n\
		buff: %s\n\
		asleft: %d\n\
		nbr_read: %d\n\
		eol: %d\n\
		nextFD:\033[0;33m%d\033[0m\n", b->fd, b->line, b->buff, b->asleft, b->nbr_read, b->eol, (b->next ? b->next->fd : 0));
	}
}

void	disp_list(t_gnl *lst)
{
	while (lst)
	{
		printf("\033[1;35m--- \tFD %d is in list\033[0m\n", lst->fd);
		lst = lst->next;
	}
}