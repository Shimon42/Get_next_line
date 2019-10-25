/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_brained.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 20:22:38 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 21:47:16 by siferrar    ###    #+. /#+    ###.fr     */
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
		printf(" - ok\n");
		(*brain).asleft = 0;
		(*brain).init = 1;
	}
	(*brain).line = *line;
	(*brain).buff = NULL;
	(*brain).nbr_read = 0;
	(*brain).line_len = 0;
	return (1);
}

void	treat_left(t_gnl *b, int *check)
{
	if ((*check = has_eol((*b).left)) >= 0) // if line has \n 
	{
		printf("-- AS RETURN IN LEFT\n");
		ft_realloc((*b).line, 0, ft_strlen((*b).left) - *check);
		ft_strlcpy((*b).line, (*b).left, *check); //line = left - check
		(*b).left += *check; // get start of next left
		printf ("\033[0;36m-- CUR LINE: %s\033[0;35m[end]\033[0m\n", (*b).line);
		printf("-- LEFT OK - %s\n", (*b).left);
		printf("-- ALLOC LEFT - %d\n", BUFFER_SIZE - *check);
		
		ft_realloc((*b).left, 0, ft_strlen((*b).left));
		(*b).left[ft_strlen((*b).left)] = '\0';
		printf("\033[0;31mLEFT END: \033[0;33m%s\033[0;35m[end]\033[0m\n", (*b).left);
	} else {
		printf("-- NO RETURN IN LEFT\n");
		ft_strlcpy((*b).line, (*b).left, ft_strlen((*b).left) + 1); // store left
		(*b).left = "";
		(*b).asleft = 0;
	}
}

void	treat_read(t_gnl *b, int *check)
{
	printf("-- READ OK -> BUFF:%s\033[0;35m[end]\033[0m\n", (*b).buff);
	printf("-- FOUND EOL -- %d\n", *check);
	ft_realloc((*b).line, 0, ft_strlen((*b).line) + ft_strlen((*b).buff) - *check); // alloc size of left + buff length - *check 
	printf("-- REALLOC OK\n");
	//*line = (*b).line;
	(*b).line += ft_strlen((*b).line); //get start
	printf("-- PTR OK - %s\n", (*b).line);
	ft_strlcpy((*b).line, (*b).buff, *check); //line = left - *check
		printf("-- LINE ASSIGN OK\n");
	*((*b).line + *check - 1) = '\0';
		printf ("\033[0;36m--READ CUR LINE: %s\033[0;35m[end]\033[0m\n", (*b).line);
	(*b).left = (*b).buff + *check;
	printf("-- PTR OK 2\n");
	ft_realloc((*b).left, 0, ft_strlen((*b).buff) - *check);
	printf("-- REALLOC LEFT OK - %s\n", (*b).left);
	(*b).left[BUFFER_SIZE - *check] = '\0';
	printf("-- STORE LEFT OK -\n");
	(*b).asleft = 1;
}
int get_next_line(int fd, char **line)
{
	static t_gnl b;
	int			check;
	
	if (!b.init)
		init_brain(&b, line);
	check = -1;
	printf("\033[0;31mLEFT BEGIN: \033[0;33m%s\033[0;35m[end]\033[0m\n", b.left);
	if (BUFFER_SIZE > 0 && (b.buff = malloc(BUFFER_SIZE * sizeof(char))) != NULL)
    {
		printf("-- FIRST TEST OK\n");
		if (b.asleft) // if left
			treat_left(&b, &check);
        while (check < 0) // Read file
        {
            printf("--READLOOP\n");
            if ((b.nbr_read = read(fd, b.buff, BUFFER_SIZE)) && (check = has_eol(b.buff)) >= 0) // if \n
            {
				treat_read(&b, &check);	
                return (1);
            } else {
				printf("CHECK NO EOF - %d\n", check);
				printf("READCHECK NO EOF - %d\n", b.nbr_read);
				  printf("-- READ END OF FILE -> BUFF:%s\033[0;35m[end]\033[0m\n", b.buff);
				
				if (b.nbr_read == 0)
				{
					printf("FINAL RETURN\n");
					ft_realloc(b.line, 0, ft_strlen(b.line) + ft_strlen(b.buff));
					printf ("\033[0;36m-- CUR LINEEND: %s\033[0;35m[end]\033[0m\n", b.line);
					*line = b.line;
					return (1);
				}
                ft_realloc(b.line, 0, ft_strlen(b.line) + BUFFER_SIZE);
                b.line = ft_strjoin(b.line, b.buff);
				printf ("\033[0;36m-- CUR LINE: %s\033[0;35m[end]\033[0m\n", b.line);
				*line = b.line;
            }
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