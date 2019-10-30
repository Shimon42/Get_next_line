#include "get_next_line.h"

void disp_brain(t_gnl *b)
{
	if (b)
	{
		printf("--- BRAIN FD %d ---\n\
		line: %s\n\
		buff: %s\n\
		left: %s\n\
		asleft: %d\n\
		line_len: %d\n\
		nbr_read: %d\n\
		init: %d\n\
		check: %d\n\
		nextFD:%d\n", b->fd, b->line, b->buff, b->left, b->asleft, b->line_len, b->nbr_read, b->init, b->check, (b->next ? b->next->fd : 0));
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