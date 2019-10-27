/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 20:22:38 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/27 20:11:49 by siferrar    ###    #+. /#+    ###.fr     */
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

void disp_brain(t_gnl b)
{
	printf("--- BRAIN FD %d ---\n\
	line: %s\n\
	buff: %s\n\
	left: %s\n\
	asleft: %d\n\
	line_len: %d\n\
	nbr_read: %d\n\
	init: %d\n\
	check: %d\n", b.fd, b.line, b.buff, b.left, b.asleft, b.line_len, b.nbr_read, b.init, b.check);
}

int	treat_left(t_gnl *b)
{
	if ((*b).asleft)
	{
		if (((*b).check = has_eol((*b).left)) >= 0)
		{
			ft_realloc((*b).line, 0, ft_strlen((*b).left) - (*b).check);
			ft_strlcpy((*b).line, (*b).left, (*b).check);
			(*b).left += (*b).check;
			ft_realloc((*b).left, 0, ft_strlen((*b).left));
			(*b).left[ft_strlen((*b).left)] = '\0';
		} else {
			ft_strlcpy((*b).line, (*b).left, ft_strlen((*b).left) + 1);
			(*b).left = "";
			(*b).asleft = 0;
		}
	}
	return (1);
}

int	treat_read(t_gnl *b)
{
	ft_realloc((*b).line,
				0,
				ft_strlen((*b).line) + ft_strlen((*b).buff) - (*b).check);
	(*b).line += ft_strlen((*b).line);
	ft_strlcpy((*b).line, (*b).buff, (*b).check);
	*((*b).line + (*b).check - 1) = '\0';
	(*b).left = (*b).buff + (*b).check;
	ft_realloc((*b).left, 0, ft_strlen((*b).buff) - (*b).check);
	(*b).left[BUFFER_SIZE - (*b).check] = '\0';
	(*b).asleft = 1;
	return (1);
}

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

t_gnl	*init_brain(t_gnl *brain, int fd, char **line)
{
	if (!(*brain).init)
	{
		(*brain).asleft = 0;
		(*brain).init = 1;
		(*brain).fd = fd;
		(*brain).next = NULL;
	}
	(*brain).line = *line;
	if (((*brain).buff = malloc(BUFFER_SIZE * sizeof(char))) == NULL)
		return (NULL);
	(*brain).nbr_read = 0;
	(*brain).line_len = 0;
	(*brain).check = -1;
	printf("-- NEW FD OK %d\n", fd);
	return (brain);
}

t_gnl *get_brain(t_gnl *b, int fd, char **line)
{
	t_gnl *newfd;

	newfd = b;
	printf("-- SEARCH FD %d\n", fd);
	if (newfd)
	{
		while (newfd->next)
		{
			disp_brain(*newfd);
			if (newfd->fd == fd)
			{
				printf("-- FOUND FD %d\n", fd);
				newfd = init_brain(newfd, fd, line);
				return (newfd);
			}
			newfd = newfd->next;
		}
	}
	printf("-- NEW FD %d\n", fd);
	newfd = init_brain(newfd, fd, line);
	(*newfd).next = b;
	return (b);
		
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

int get_next_line(int fd, char **line)
{
	static	t_gnl b;
	t_gnl *curb;

	if (BUFFER_SIZE > 0)
		if ((curb = get_brain(&b, fd, line)))
			{
				while (treat_left(curb) && (*curb).check < 0)
				{
					if (((*curb).nbr_read = read(fd, (*curb).buff, BUFFER_SIZE))
						&& ((*curb).check = has_eol((*curb).buff)) >= 0)
						return (treat_read(&b));
					if ((*curb).nbr_read == 0)
						return (ft_realloc((*curb).line, 0, ft_strlen((*curb).line)));
					ft_realloc((*curb).line, 0, ft_strlen((*curb).line) + BUFFER_SIZE);
					(*curb).line = ft_strjoin((*curb).line, (*curb).buff);
					*line = (*curb).line;
				}
			}
	return (0);
}



int main(void)
{
	int fd = open("test.txt", O_CREAT | O_RDWR);
	char *line;
	char **ptr;
	int i = 0;
	int res = 1;
	ptr = &line;
	//fd = 0;
	int fd2 = open("test2.txt", O_CREAT | O_RDWR);
	char *line2;
	char **ptr2;
	int res2 = 1;
	ptr2 = &line2;
	//res2 = 1;
	fd2 = 1;
	printf("\n\033[1;33m--------------- GNL START ------------------\033[0m\n");
	while (i < 6)
	{
		printf("\n\033[1;34m--------------- GNL - %d ------------------\033[0m\n\n", i);
		res = get_next_line(fd, ptr);
		res2 = get_next_line(fd2, ptr2);
		printf("\n\033[0;32mfd: %d - RES  %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd, i, line, res);
		//printf("\n\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd2, i, line2, res2);
			i++;
	}
	printf("\n\033[1;32m--------------- GNL   END ------------------\033[0m\n");
}