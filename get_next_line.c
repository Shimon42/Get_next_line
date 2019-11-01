/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 14:39:54 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/01 21:45:10 by siferrar    ###    #+. /#+    ###.fr     */
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
	printf("\033[0;33m\tInit brain fd %d\n", fd);
	if ((brain = malloc(sizeof(t_gnl))) != NULL)
	{
		brain->fd = fd;
		brain->asleft = 0;
		brain->next = NULL;
		brain->line = *line;
		brain->line = ft_calloc(1,1);
		brain->buff = ft_calloc(BUFFER_SIZE, sizeof(char));
		brain->eol = -1;
		//disp_brain(*brain);
		printf("\tNEW FD OK %d\033[0m\n", fd);
	}
	return (brain);
}

t_gnl	*get_brain(t_gnl **b, int fd, char **line)
{
	t_gnl *tmp;
	t_gnl **ptr;

	ptr = b;
	printf("-> Searching for FD %d\n", fd);
	if (*ptr != NULL)
	{
		while ((*ptr) != NULL)
		{
			if ((*ptr)->fd == fd)
				return (*ptr);
			ptr = &((*ptr)->next);
		}
		printf("\t-> NOT FOUND\n");
		tmp = init_brain(fd, line);
		tmp->next = *b;
		*b = tmp;
		printf("\t-> Alloc ok\n");
		return (tmp);
	}
	printf("-> First in list\n");
	*b = init_brain(fd, line);
	printf("\tAlloc ok\n");
	return (*b);
}


void	meditate(t_gnl **blist, t_gnl *b)
{
	t_gnl **ptr;
	
	printf("-> Meditate on FD %d\n", b->fd);
	ptr = blist;
	if ((*ptr)->fd != b->fd)
	{
		if ((*ptr)->next != NULL)
		{
			while (((*ptr)->next->fd) != b->fd && ((*ptr)->next->next) != NULL)
				ptr = &((*ptr)->next);
			if ((*ptr)->next->fd == b->fd)
				(*ptr)->next = b->next;
		}
	}
	else
		*blist = b->next;
	free(b->buff);
	b->next = NULL;
	free(b);
}

int		treat_left(t_gnl *b, char **line)
{
	printf("-> Has left\n");
	if((b->eol = has_eol(b->buff)) >= 0)
	{
		printf("-> HAS EOL in left - %d\n", b->eol);
		if (b->eol == 0)
		{
			printf("->LINE JUMP\n");
			*line = ft_strnjoin("\n", "", 0, -1);
			b->buff = ft_strnjoin("", b->buff, b->eol + 1, -1);
			disp_brain(b);
			return (1);
		}
		b->line = ft_strnjoin(b->line, b->buff, 0, b->eol);	
		*line = b->line;
		b->buff = ft_strnjoin("", b->buff, b->eol + 1, ft_strlen(b->buff) - b->eol);
		printf("-> HAS BUFF - \033[0;35m[start]\033[0m%s\033[0;35m[end]\033[0m\n", b->buff);
		b->asleft = 1;
		disp_brain(b);
		return (1);
	}
	disp_brain(b);
	if (b->eol == -2)
		return (0);
	b->line = ft_strnjoin(b->line, b->buff, 0, -1);	
	return (0);
}


int		get_next_line(int fd, char **line)
{
	static	t_gnl *blist;
	t_gnl *b;

	if (BUFFER_SIZE > 0 && fd >= 0)
		if ((b = get_brain(&blist, fd, line)))
		{
			b->nbr_read = 0;
			b->line = ft_calloc(1, 1);
			disp_brain(b);
			if(b->asleft)
				if (treat_left(b, line))
					return (1);
			b->buff = ft_calloc(BUFFER_SIZE, sizeof(char));
			while((b->nbr_read = read(b->fd, b->buff, BUFFER_SIZE)))
			{
				if (b->nbr_read < BUFFER_SIZE)
					b->buff[b->nbr_read] = '\0';
				printf("-> READED:\n\033[0;35m[start]\033[0m%s\033[0;35m[end]\033[0m\n", b->buff);
				if (treat_left(b, line))
						return (1);
			}
			if (b->nbr_read == 0)
			{
				*line = b->line;
				meditate(&blist, b);
				return (0);
			}
		}
	return (-1);
}

int main(void)
{
	int fd = open("tests/test", O_RDONLY);
	char *line ;
	line = NULL;
	int i = 0;
	int res = 1;

	int fd2 = open("tests/test2", O_RDONLY);
	char *line2;
	line2 = NULL;
	int res2 = 1;

	int fd3 = open("tests/test3", O_RDONLY);
	char *line3;
	line3 = NULL;
	int res3 = 1;

	int fd4 = open("tests/test4", O_RDONLY);
	char *line4;
	line4 = NULL;
	int res4 = 1;
	printf("\n\033[1;33m--------------- GNL START ------------------\033[0m\n");
	while (i < 5)
	{
		if (res > 0)
		{
			printf("\n\033[1;34m--------------- GNL - %d - FD %d ---------------\033[0m\n", i, fd);
			res = get_next_line(fd, &line);
			printf("\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd, i, line, res);
		}
		
		if (res2 > 0)
		{
			printf("\n\033[1;34m--------------- GNL - %d - FD %d ---------------\033[0m\n\n", i, fd2);
			res2 = get_next_line(fd2, &line2);
			printf("\n\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd2, i, line2, res2);
		}

		if(res3 > 0)
		{
			printf("\n\033[1;34m--------------- GNL - %d - FD %d ---------------\033[0m\n\n", i, fd3);
			//res3 = get_next_line(fd3, &line3);
			printf("\n\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd3, i, line3, res3);
		}
		
		if(res4 > 0)
		{
			printf("\n\033[1;34m--------------- GNL - %d - FD %d ---------------\033[0m\n\n", i, fd4);
			//res4 = get_next_line(fd4, &line4);
			printf("\n\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd4, i, line4, res4);
		}
		i++;
	}
	printf("\n\033[1;32m--------------- GNL   END ------------------\033[0m\n");
}
