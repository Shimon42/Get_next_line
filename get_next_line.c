/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 14:39:54 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/31 17:09:14 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

void disp_brain(t_gnl *b);
void	disp_list(t_gnl *lst);

t_gnl	*init_brain(int fd, char **line)
{
	t_gnl *brain;
	printf("\tInit brain fd %d\n", fd);
	if ((brain = malloc(sizeof(t_gnl))) != NULL)
	{
		if (brain->init == 1)
			printf("\tALREADY INIT\n");
		brain->asleft = 0;
		brain->left = NULL;
		brain->init = 1;
		brain->fd = fd;
		brain->next = NULL;
		brain->left = ft_calloc(1,1);
		brain->line = *line;
		brain->line = ft_calloc(1,1);
		brain->buff = ft_calloc(BUFFER_SIZE, sizeof(char));
		brain->nbr_read = 0;
		brain->line_len = 0;
		brain->eol = -1;
		//disp_brain(*brain);
		printf("\tNEW FD OK %d\n", fd);
	}
	return (brain);
}

t_gnl	*get_brain(t_gnl **b, int fd, char **line)
{
	t_gnl *tmp;
	t_gnl **ptr;

	ptr = b;
	printf("Searching for FD %d\n", fd);
	if (*ptr != NULL)
	{
		while ((*ptr) != NULL)
		{
			printf("- FD %d in list\n", (*ptr)->fd);
			if ((*ptr)->fd == fd)
				return (*ptr);
			ptr = &((*ptr)->next);
		}
		printf("\tNOT FOUND\n");
		//*ptr = (*ptr)->next;
		tmp = init_brain(fd, line);
		tmp->next = *b;
		*b = tmp;
		printf("\tAlloc ok\n");
		return (tmp);
	}
	printf("First in list\n");
	*b = init_brain(fd, line);
	return (*b);
}

int get_next_line(int fd, char **line)
{
	static	t_gnl *blist;
	t_gnl *b;

	disp_list(blist);
	if (BUFFER_SIZE > 0)
		if ((b = get_brain(&blist, fd, line)))
			{
				b->line = ft_calloc(1,1);
				printf("\033[1;36m--- BRAIN %d WELL RETRIEVED\033[0m\n", b->fd);
				disp_brain(b);
				if(b->asleft)
				{
					printf("- Has left\n");
					if((b->eol = has_eol(b->buff)) >= 0)
					{
						printf("- HAS EOL in left - %d\n", b->eol);
						*line = ft_strnjoin(b->line, b->buff, 0, b->eol - 1);	
						b->buff = ft_strnjoin("", b->buff, b->eol + 1, -1);
						b->asleft = 1;
						disp_brain(b);
						return (1);
					}
					b->line = ft_strnjoin(b->line, b->buff, 0, -1);			
					b->asleft = 1;
				}
				while((b->nbr_read = read(b->fd, b->buff, BUFFER_SIZE)))
				{
					b->buff[b->nbr_read] = '\0';
					printf("- READED: %s[END]\n", b->buff);
					if ((b->eol = has_eol(b->buff)) >= 0)
					{
						*line = ft_strnjoin(b->line, b->buff, 0, b->eol - 1);
						b->buff = ft_strnjoin("", b->buff, b->eol, -1);
						b->asleft = 1;
						disp_brain(b);
						return (1);
					}
					b->line = ft_strnjoin(b->line, b->buff,0 , -1);
					b->asleft = 0;
				}
				if (b->nbr_read == 0)
				{
					*line = b->line;
					return (0);
				}
				b->asleft = 1;
				printf("Check: %d\n", b->eol);
				disp_brain(b);
				return (0);
			}
	return (0);
}



int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;
	int i = 0;
	int res = 1;

	int fd2 = open("test2.txt", O_RDONLY);
	char *line2;
	int res2 = 1;
/*
	int fd3 = open("test2.txt", O_RDONLY);
	char *line3;
	int res3 = 1;
	
	int fd4 = open("test2.txt", O_RDONLY);
	char *line4;
	int res4 = 1;
	*/
	printf("\n\033[1;33m--------------- GNL START ------------------\033[0m\n");
	while (res || res2)
	{
		printf("\n\033[1;34m--------------- GNL - %d - FD %d ---------------\033[0m\n\n", i, fd);
		res = get_next_line(fd, &line);
		printf("\n\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd, i, line, res);
		
		printf("\n\033[1;34m--------------- GNL - %d - FD %d ---------------\033[0m\n\n", i, fd2);
		res2 = get_next_line(fd2, &line2);
		printf("\n\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd2, i, line2, res2);
		
	/*	printf("\n\033[1;34m--------------- GNL - %d - FD %d ---------------\033[0m\n\n", i, fd3);
		res3 = get_next_line(fd3, &line3);
		printf("\n\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd3, i, line3, res3);
		
		printf("\n\033[1;34m--------------- GNL - %d - FD %d ---------------\033[0m\n\n", i, fd4);
		res4 = get_next_line(fd4, &line4);
		printf("\n\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd4, i, line4, res4);
		*/
		i++;
	}
	printf("\n\033[1;32m--------------- GNL   END ------------------\033[0m\n");
}