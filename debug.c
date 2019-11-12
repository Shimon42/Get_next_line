#include "get_next_line.h"
#include "debug.h"

#define DEBUG  0

void disp_brain(t_gnl *b, char *title)
{
	if (b && DEBUG)
	{
printf("\033[0;36m---- BRAIN FD %d ------------------%s\033[0;36m---------------\n\
|	line:\n\033[0;35m[start]\033[0m%s\033[0;35m[end]\033[0m\n\
\033[0;36m|	lineLen:\033[0;35m%lu\033[0m\n\
\033[0;36m|	buff:\n\033[0;35m[start]\033[0;33m%s\033[0;35m[end]\033[0m\n\
\033[0;36m|	buffLen:\033[0;33m%lu\033[0m\n\
\033[0;36m|	asleft: \033[0;33m%d\n\
\033[0;36m|	nbr_read: \033[0;33m%d\n\
\033[0;36m|	eol: \033[0;33m%d\n\
\033[0;36m|	nextFD:\033[0;33m%d\033[0;36m\n|---------------------------------------------------\033[0m\n", b->fd, title, b->line, ft_strlen(b->line), b->buff, ft_strlen(b->buff), b->asleft, b->nbr_read, b->eol, (b->next ? b->next->fd : 0));
	}
}

void	disp_list(t_gnl *lst)
{
	while (lst && DEBUG)
	{
		printf("\033[1;35m--- \tFD %d is in list\033[0m\n", lst->fd);
		lst = lst->next;
	}
}
