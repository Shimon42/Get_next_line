/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 14:39:54 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 21:41:14 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"
#include "debug.h"

t_gnl	*init_brain(int fd)
{
	t_gnl *brain;

	if ((brain = malloc(sizeof(t_gnl))) != NULL)
	{
		brain->fd = fd;
		brain->asleft = 0;
		brain->next = NULL;
		brain->eol = -1;
		brain->nbr_read = 0;
	}
	return (brain);
}

t_gnl	*get_brain(t_gnl **b, int fd, char **line)
{
	t_gnl *tmp;
	t_gnl **ptr;

	if (read(fd, NULL, 0) == -1)
		return (NULL);
	ptr = b;
	if (*ptr != NULL)
	{
		while ((*ptr) != NULL)
		{
			if ((*ptr)->fd == fd)
			{
				*line = ft_calloc(1, sizeof(char));
				return (*ptr);
			}
			ptr = &((*ptr)->next);
		}
		tmp = init_brain(fd);
		tmp->next = *b;
		*b = tmp;
		return (tmp);
	}
	*b = init_brain(fd);
	return (*b);
}

void	meditate(t_gnl **blist, t_gnl *b)
{
	t_gnl **ptr;

	printf(UYELO"------- Meditate -------"RST"\n");
	ptr = blist;
	if (*ptr && (*ptr)->fd != b->fd)
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
	char *temp;
	char *btemp;

	printf(UYELO"------- Treat Left -------"RST"\n");
	if ((b->eol = has_eol(b->buff)) >= 0)
	{
		printf(GRN"Has EOL "RST"\n");
		printf("Join to line temp\n");
		temp = ft_strnjoin(*line, b->buff, 0, b->eol);
		free(*line);
		*line = temp;
		printf("*line length:%lu (+ 1 for '\\0')\n", ft_strlen(*line));
		printf("Join to buff temp\n");
		btemp = ft_strnjoin("",
							b->buff,
							b->eol + 1,
							ft_strlen(b->buff) - b->eol);
		free(b->buff);
		b->buff = btemp;
		printf("b->buff length:%lu (+ 1 for '\\0')\n", ft_strlen(b->buff));
		b->asleft = 1;
		printf(URED"------- ENDTreat Left -------"RST"\n");
		return (1);
	}
	printf(RED"NO EOL"RST"\n");
	printf("Join to line temp\n");
	temp = ft_strnjoin(*line, b->buff, 0, BUFFER_SIZE);
	free(*line);
	*line = temp;
	printf("*line length:%lu (+ 1 for '\\0')\n", ft_strlen(*line));
	b->asleft = 1;
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static	t_gnl	*blist;
	t_gnl			*b;
	printf("\n");
	if (BUFFER_SIZE > 0 && fd >= 0)
		if ((b = get_brain(&blist, fd, line)))
		{
			if (b->asleft && treat_left(b, line))
				return (1);
			if ((b->buff = malloc((BUFFER_SIZE + 1) * sizeof(char))) != NULL)
			{
				while ((b->nbr_read = read(b->fd, b->buff, BUFFER_SIZE)))
				{
					b->buff[b->nbr_read] = 0;
					if (treat_left(b, line))
						return (1);
				}
				if (!b->nbr_read)
				{
					meditate(&blist, b);
					return (0);
				}
			}
		}
	return (-1);
}
