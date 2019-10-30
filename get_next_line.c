/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 14:39:54 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 18:07:05 by siferrar    ###    #+. /#+    ###.fr     */
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
		brain->line = *line;
		if ((brain->buff = malloc(BUFFER_SIZE * sizeof(char))) == NULL)
			return (NULL);
		brain->nbr_read = 0;
		brain->line_len = 0;
		brain->check = -1;
		//disp_brain(*brain);
		printf("\tNEW FD OK %d\n", fd);
	}
	return (brain);
}

t_gnl	*get_brain(t_gnl **ptr, int fd, char **line)
{
	printf("Searching for FD %d\n", fd);
	disp_brain(*ptr);
	if (*ptr != NULL)
	{
		while ((*ptr)->next != NULL)
		{
			if ((*ptr)->fd == fd)
				return (*ptr);
			(*ptr) = (*ptr)->next;
		}
		printf("\tNOT FOUND\n");
		(*ptr)->next = init_brain(fd, line);
		printf("\tAlloc ok\n");
		//*ptr = (*ptr)->next;
		return ((*ptr)->next->next);
	}
	printf("First in list\n");
	*ptr = init_brain(fd, line);
	return (*ptr);
}

int get_next_line(int fd, char **line)
{
	static	t_gnl *b;
	t_gnl **curb;

	curb = &b;
	disp_list(b);
	if (BUFFER_SIZE > 0)
		if ((get_brain(&b, fd, line)))
			{
				printf("\033[1;36m-- BRAIN %d WELL RETRIEVED\033[0m\n", (*curb)->fd);
				disp_brain(*curb);
				(*curb)->line  = *line;
			}
	return (0);
}



int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;
	int i = 0;
	int res = 1;
	line = malloc(30 * sizeof(char));
	line = "Bonjour comment ca va";

	int fd2 = open("test2.txt", O_RDONLY);
	char *line2;
	int res2 = 1;
	line2 = malloc(30 * sizeof(char));
	line2 = "Bien et toi ?";

	int fd3 = open("test2.txt", O_RDONLY);
	char *line3;
	int res3 = 1;
	line3 = malloc(30 * sizeof(char));
	line3 = "CA VA CA VA";
	
	printf("\n\033[1;33m--------------- GNL START ------------------\033[0m\n");
	while (i < 2)
	{
		printf("\n\033[1;34m--------------- GNL - %d - FD %d ---------------\033[0m\n\n", i, fd);
		res = get_next_line(fd, &line);
		printf("\n\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd, i, line, res);
		
		printf("\n\033[1;34m--------------- GNL - %d - FD %d ---------------\033[0m\n\n", i, fd2);
		res2 = get_next_line(fd2, &line2);
		printf("\n\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd2, i, line2, res2);
		
		printf("\n\033[1;34m--------------- GNL - %d - FD %d ---------------\033[0m\n\n", i, fd3);
		res3 = get_next_line(fd3, &line3);
		printf("\n\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd3, i, line3, res3);
		i++;
	}
	printf("\n\033[1;32m--------------- GNL   END ------------------\033[0m\n");
}