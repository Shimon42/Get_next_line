/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 20:22:38 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 23:13:59 by siferrar    ###    #+. /#+    ###.fr     */
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

void	init_brain(t_gnl *brain, char **line, int *check)
{
	if (!(*brain).init)
	{
		printf(" - ok\n");
		(*brain).asleft = 0;
		(*brain).init = 1;
	}
	(*brain).line = *line;
	(*brain).buff = NULL;
	(*brain).nbr_read = 0;
	(*brain).line_len = 0;
	*check = -1;
}

int	treat_left(t_gnl *b, int *check)
{
	if ((*b).asleft)
	{
		if ((*check = has_eol((*b).left)) >= 0)
		{
			ft_realloc((*b).line, 0, ft_strlen((*b).left) - *check);
			ft_strlcpy((*b).line, (*b).left, *check);
			(*b).left += *check;
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

int	treat_read(t_gnl *b, int *check)
{
	ft_realloc((*b).line,
				0,
				ft_strlen((*b).line) + ft_strlen((*b).buff) - *check);
	(*b).line += ft_strlen((*b).line);
	ft_strlcpy((*b).line, (*b).buff, *check);
	*((*b).line + *check - 1) = '\0';
	(*b).left = (*b).buff + *check;
	ft_realloc((*b).left, 0, ft_strlen((*b).buff) - *check);
	(*b).left[BUFFER_SIZE - *check] = '\0';
	(*b).asleft = 1;
	return (1);
}

int get_next_line(int fd, char **line)
{
	static	t_gnl b;
	int		check;

	init_brain(&b, line, &check);
	if ((b.buff = malloc(BUFFER_SIZE * sizeof(char))) == NULL)
		return (-1);
	if (BUFFER_SIZE > 0)
	{
		while (treat_left(&b, &check) && check < 0)
			if ((b.nbr_read = read(fd, b.buff, BUFFER_SIZE)) && (check = has_eol(b.buff)) >= 0)
				return (treat_read(&b, &check));
			else {
				if (b.nbr_read == 0)
					return (ft_realloc(b.line, 0, ft_strlen(b.line)));
				ft_realloc(b.line, 0, ft_strlen(b.line) + BUFFER_SIZE);
				b.line = ft_strjoin(b.line, b.buff);
				*line = b.line;
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
	int res = 0;
	ptr = &line;
	printf("\n\033[1;31m--------------- GNL START ------------------\033[0m\n");
	while (i < 7)
	{
		printf("\n\033[1;34m--------------- GNL - %d ------------------\033[0m\n\n", i);
		res = get_next_line(fd, ptr);
		printf("\n\033[0;32mRES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", i++, line, res);
	}
	printf("\n\033[1;32m--------------- GNL   END ------------------\033[0m\n");
}