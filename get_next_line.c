/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 20:22:38 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 16:06:57 by siferrar    ###    #+. /#+    ###.fr     */
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

int	ft_realloc(char *buff, int buff_length, int overright)
{
	static int	buff_size;
	char *tmp;
	int i;

	i = 0;
	if (overright)
		buff_size = overright;
	else
		buff_size += buff_length;
	tmp = malloc((buff_size + 1) * sizeof(char));
	while (i <= buff_size)
		tmp[i++] = '\0';
	ft_strlcpy(tmp, buff, buff_size);
	buff = tmp;
	return (buff_size);
}

int has_eol(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		if(s[i++] == '\n')
			return (i);
	if (i < BUFFER_SIZE)
		return (-2);
	return (-1);
}

void	treat_left(char *left, char *line, int *check, int *asleft)
{
	char    *ptr;

	if ((*check = has_eol(left)) >= 0) // if line has \n 
	{
		ft_realloc(*line, 0, ft_strlen(left) - *check);
		ft_strlcpy(*line, left, check); //line = left - check
		ptr = left + *check; // get start of next left
		left = ptr;
		ft_realloc(left, 0, ft_strlen(left));
		left[ft_strlen(left)] = '\0';
		return (1);
	} else {
		ft_strlcpy(*line, left, ft_strlen(left) + 1); // store left
		left = "";
		asleft = 0;
	}
}

int get_next_line(int fd, char **line)
{
	char		*buff;
	int			check;
	static char *left;
	static int	asleft;
    char    *ptr;
	int		readcheck;

	readcheck = 0;
	if (!asleft)
		left = NULL;
	check = -1;
	if (BUFFER_SIZE > 0 && (buff = malloc(BUFFER_SIZE * sizeof(char))) != NULL)
    {
		if (asleft) // if left
		treat_left(left, line, &check, &asleft);
        while (check < 0) // Read file
        {
            if ((readcheck = read(fd, buff, BUFFER_SIZE)) && (check = has_eol(buff)) >= 0) // if \n
            {
                ft_realloc(*line, 0, ft_strlen(*line) + ft_strlen(buff) - check); // alloc size of left + buff length - check 
                ptr = *line + ft_strlen(*line); //get start
                ft_strlcpy(ptr, buff, check); //line = left - check
				*(ptr + check - 1) = '\0';
                ptr = buff + check; //get start, pas de + 1 car le "plus 1" est le \n 
				left = ptr;
				ft_realloc(left, 0, ft_strlen(buff) - check);
				left[BUFFER_SIZE - check] = '\0';
                asleft = 1;
                return (1);
            } else {
				if (readcheck == 0)
				{
					ft_realloc(*line, 0, ft_strlen(*line) + ft_strlen(buff));
					return (1);
				}
                ft_realloc(*line, 0, ft_strlen(*line) + BUFFER_SIZE);
                *line = ft_strjoin(*line, buff);
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