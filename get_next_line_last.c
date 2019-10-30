/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 20:22:38 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/29 17:51:40 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void disp_brain(t_gnl *b)
{
	printf("--- BRAIN FD %d ---\n\
	line: %s\n\
	buff: %s\n\
	left: %s\n\
	asleft: %d\n\
	line_len: %d\n\
	nbr_read: %d\n\
	init: %d\n\
	check: %d\n", (*b).fd, (*b).line, (*b).buff, (*b).left, (*b).asleft, (*b).line_len, (*b).nbr_read, (*b).init, (*b).check);
}

void	disp_list(t_gnl *lst)
{
	while (lst)
	{
		printf("\033[1;35m--- \tFD %d is in list\033[0m\n", lst->fd);
		lst = lst->next;
	}
}

t_gnl	*init_brain(int fd, char **line)
{
	t_gnl *brain;
	printf("-- Init brain fd %d\n", fd);
	if ((brain = malloc(sizeof(t_gnl))) != NULL)
	{
		if (brain->init == 1)
			printf("ALREADY INIT\n");
		brain->asleft = 0;
		brain->left = NULL;
		brain->init = 1;
		brain->fd = fd;
		brain->next = NULL;
		brain->line = *line;
		if ((brain->buff = malloc(BUFFER_SIZE * sizeof(char))) == NULL)
			return (NULL);
		brain->nbr_read = 0;
		brain->line_len = 0;
		brain->check = -1;
		//disp_brain(*brain);
		printf("-- NEW FD OK %d\n", fd);
	}
	return (brain);
}

int	treat_left(t_gnl *b)
{
	if (b->asleft)
	{
		if ((b->check = has_eol(b->left)) >= 0)
		{
			ft_realloc(b->line, 0, ft_strlen(b->left) - b->check);
			ft_strlcpy(b->line, b->left, b->check);
			b->left += b->check;
			ft_realloc(b->left, 0, ft_strlen(b->left));
			b->left[ft_strlen(b->left)] = '\0';
		} else {
			ft_strlcpy(b->line, b->left, ft_strlen(b->left) + 1);
			b->left = "";
			b->asleft = 0;
		}
	} else
		printf("NO LEFT\n");
	return (1);
}

int	treat_read(t_gnl *b)
{
	printf("START TREAT READ\n");
	ft_strlen((*b).line);
	ft_strlen((*b).buff);
	if ((*b).line != NULL)
		ft_realloc((*b).line,
					0,
					ft_strlen((*b).line) + ft_strlen((*b).buff) - (*b).check);
	else
	{
		ft_realloc((*b).line,
					0,
					ft_strlen((*b).buff) - (*b).check);
	}
	
	printf("REALLOC READ OK\n");
	(*b).line += ft_strlen((*b).line);
	ft_strlcpy((*b).line, (*b).buff, (*b).check);
	*((*b).line + (*b).check - 1) = '\0';
	(*b).left = (*b).buff + (*b).check;
	ft_realloc((*b).left, 0, ft_strlen((*b).buff) - (*b).check);
	(*b).left[BUFFER_SIZE - (*b).check] = '\0';
	(*b).asleft = 1;
	return (1);
}

t_gnl	*get_brain(t_gnl *b, int fd, char **line)
{
	printf("-- Searching for Fd %d\n", fd);
	t_gnl **ptr;

	ptr = &b;

	if((*ptr) != NULL)
	{
		while ((*ptr))
		{
			printf("-- \033[1;33mtmpid %d\033[0m\n", b->fd);
			if((*ptr)->fd == fd)
			{
				printf("\033[1;33m-- Found !\033[0m\n");
				return ((*ptr));
			}
			if ((*ptr)->next == NULL)
				break;
			*ptr = (*ptr)->next;
		}
		printf("-- Not Found but list...\n");
		(*ptr)->next = init_brain(fd, line);
		*ptr = (*ptr)->next;
		return ((*ptr));
	}
	printf("-- Not Found ...\n");
	printf("-- FIRST IN LIST\n");
	b = init_brain(fd, line);
	printf("Malloc ok\n");
	printf("-- Returning new fd %d\n", fd);
	return ((*ptr));
}

/*
int get_next_lineGG(int fd, char **line)
{
	static	t_gnl b;

	if (BUFFER_SIZE > 0)
		if (init_brain(&b, line))
		while (treat_left(&b) && b.check < 0)
			{
				if ((b.nbr_read = read(fd, b.buff, BUFFER_SIZE))
					&& (b.check = has_eol(b.buff)) >= 0)
					return (treat_read(&b));
				if (b.nbr_read == 0)
					return (ft_realloc(b.line, 0, ft_strlen(b.line)));
				ft_realloc(b.line, 0, ft_strlen(b.line) + BUFFER_SIZE);
				b.line = ft_strjoin(b.line, b.buff);
				*line = b.line;
			}
	return (0);
}*/

int treat_all(t_gnl *b)
{
	if ((*b).left)
		if (((*b).check = has_eol((*b).left)))
		{
			ft_strlcpy((*b).line, (*b).left + (*b).check, ft_strlen((*b).left) - (*b).check);
			return (1);
		}
	return (1);
}

int get_next_line(int fd, char **line)
{
	static	t_gnl *b;
	t_gnl **curb;

	curb = &b;
	disp_list(b);
	if (BUFFER_SIZE > 0)
		if ((*curb = get_brain(b, fd, line)))
			{
				printf("\033[1;36m-- BRAIN %d WELL RETRIEVED\033[0m\n", (*curb)->fd);
				disp_brain(*curb);
				(*curb)->line  = *line;
				while (treat_left(*curb) && (*curb)->check < 0)
				{
					printf("-- TREAT LEFT OK\n");
					if (((*curb)->nbr_read = read(fd, (*curb)->buff, BUFFER_SIZE))
						&& ((*curb)->check = has_eol((*curb)->buff)) >= 0)
					{
						printf("-- RETURN IN LEFT\n");
						*line = (*curb)->line;
						return (treat_read(*curb));
					}
					printf("-- NO RETURN IN BUFF\n");
					if ((*curb)->nbr_read == 0)
						return (ft_realloc((*curb)->line, 0, ft_strlen((*curb)->line)));
					printf("-- NO END OF FILE\n");
					ft_realloc((*curb)->line, 0, ft_strlen((*curb)->line) + BUFFER_SIZE);
					printf("-- REALLOC OK\n");
					(*curb)->line = ft_strjoin((*curb)->line, (*curb)->buff);
					*line = (*curb)->line;
				}
				return (1);
			}
	return (0);
}



int main(void)
{
	int fd = open("test.txt", O_CREAT | O_RDWR);
	char *line;
	int i = 0;
	int res = 1;
	//fd = 0;
	int fd2 = open("test2.txt", O_CREAT | O_RDWR);
	char *line2;
	int res2 = 1;
	//res2 = 1;
	//fd2 = 1;
	printf("\n\033[1;33m--------------- GNL START ------------------\033[0m\n");
	while (res == 1)
	{
		printf("\n\033[1;34m--------------- GNL - %d - FD %d ---------------\033[0m\n\n", i, fd);
		res = get_next_line(fd, &line);
		printf("\n\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd, i, line, res);
		
		printf("\n\033[1;34m--------------- GNL - %d - FD %d ---------------\033[0m\n\n", i, fd2);
		res2 = get_next_line(fd2, &line2);
		printf("\n\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd2, i, line2, res2);
		i++;
	}
	printf("\n\033[1;32m--------------- GNL   END ------------------\033[0m\n");
}