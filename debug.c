#include "get_next_line.h"

void disp_brain(t_gnl *b, char *title)
{
	if (b)
	{
printf("\033[0;36m---- BRAIN FD %d ------------------%s\033[0;36m---------------\n\
|	line:\n\033[0;35m[start]\033[0m%s\033[0;35m[end]\033[0m\n\
\033[0;36m|	buff:\n\033[0;35m[start]\033[0;33m%s\033[0;35m[end]\033[0m\n\
\033[0;36m|	asleft: \033[0;33m%d\n\
\033[0;36m|	nbr_read: \033[0;33m%d\n\
\033[0;36m|	eol: \033[0;33m%d\n\
\033[0;36m|	nextFD:\033[0;33m%d\033[0;36m\n|---------------------------------------------------\033[0m\n", b->fd, title, b->line, b->buff, b->asleft, b->nbr_read, b->eol, (b->next ? b->next->fd : 0));
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