/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 20:22:38 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 23:29:46 by siferrar    ###    #+. /#+    ###.fr     */
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

int	init_brain(t_gnl *brain, char **line)
{
	if (!(*brain).init)
	{
		(*brain).asleft = 0;
		(*brain).init = 1;
	}
	(*brain).line = *line;
	if (((*brain).buff = malloc(BUFFER_SIZE * sizeof(char))) == NULL)
		return (-1);
	(*brain).nbr_read = 0;
	(*brain).line_len = 0;
	(*brain).check = -1;
	return (1);
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

int get_next_line(int fd, char **line)
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
						return (ft_realloc(b.line, 0, ft_strlen(b.line)) * 0);
					ft_realloc(b.line, 0, ft_strlen(b.line) + BUFFER_SIZE);
					b.line = ft_strjoin(b.line, b.buff);
					*line = b.line;
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
	printf("\n\033[1;31m--------------- GNL START ------------------\033[0m\n");
	while (res)
	{
		printf("\n\033[1;34m--------------- GNL - %d ------------------\033[0m\n\n", i);
		res = get_next_line(fd, ptr);
		printf("\n\033[0;32mRES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", i++, line, res);
	}
	printf("\n\033[1;32m--------------- GNL   END ------------------\033[0m\n");
}