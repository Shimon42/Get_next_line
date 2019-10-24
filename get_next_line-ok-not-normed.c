/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 20:22:38 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 15:57:16 by siferrar    ###    #+. /#+    ###.fr     */
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

char	*ft_strdup(const char *s1)
{
	int		length;
	char	*dup;
	int		i;

	i = -1;
	length = 0;
	while (s1[length] != '\0')
		length++;
	if ((dup = malloc((length + 1) * sizeof(char))) != NULL)
		while (i++ < length)
			dup[i] = s1[i];
	return (dup);
}


size_t	ft_strlen(const char *s)
{
	int length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}

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

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;

	i = 0;
	if (size != 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
		while (src[i] != '\0')
			i++;
	}
	else
		return (ft_strlen(src));
	return (i);
}


char		*ft_strjoin(char const *s1, char const *s2)
{
	char		*join;
	const char	*ps1;
	const char	*ps2;
	char		*pj;

	ps1 = s1;
	ps2 = s2;
	if ((join = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char)))
		!= NULL)
	{
		pj = join;
		while (*ps1 != '\0')
			*pj++ = *ps1++;
		while (*ps2 != '\0')
			*pj++ = *ps2++;
		*pj++ = '\0';
	}
	return (join);
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
	printf("\033[0;31mLEFT BEGIN: \033[0;33m%s\033[0;35m[end]\033[0m\n", left);
	if (BUFFER_SIZE > 0 && (buff = malloc(BUFFER_SIZE * sizeof(char))) != NULL)
    {
        printf("-- Malloc OK\n");
		if (asleft) // if left
        {
            printf("-- AS LEFT\n");
            if ((check = has_eol(left)) >= 0) // if line has \n 
            {
				printf("-- AS RETURN IN LEFT\n");
                ft_realloc(*line, 0, ft_strlen(left) - check);
                ft_strlcpy(*line, left, check); //line = left - check
                ptr = left + check; // get start of next left
                printf ("\033[0;36m-- CUR LINE: %s\033[0;35m[end]\033[0m\n", *line);
                printf("-- PTR LEFT OK - %s\n", ptr);
				printf("-- ALLOC LEFT - %d\n", BUFFER_SIZE - check);
				//ft_realloc(left, 0, ft_strlen(buff) - check + 1);
				left = ptr;
				ft_realloc(left, 0, ft_strlen(left));
				left[ft_strlen(left)] = '\0';
				printf("\033[0;31mLEFT END: \033[0;33m%s\033[0;35m[end]\033[0m\n", left);
                return (1);
            } else {
				printf("-- NO RETURN IN LEFT\n");
                ft_strlcpy(*line, left, ft_strlen(left) + 1); // store left
                left = "";
                asleft = 0;
            }
        }
        while (check < 0) // Read file
        {
            
            if ((readcheck = read(fd, buff, BUFFER_SIZE)) && (check = has_eol(buff)) >= 0) // if \n
            {
          	  printf("-- READ OK -> BUFF:%s\033[0;35m[end]\033[0m\n", buff);
                printf("-- FOUND EOL -- %d\n", check);
                ft_realloc(*line, 0, ft_strlen(*line) + ft_strlen(buff) - check); // alloc size of left + buff length - check 
                printf("-- REALLOC OK\n");
                ptr = *line + ft_strlen(*line); //get start
                printf("-- PTR OK - %s\n", ptr);
                printf("-- PTR AT - %lu\n", ft_strlen(buff) - check);
                ft_strlcpy(ptr, buff, check); //line = left - check
                printf("-- LINE ASSIGN OK\n");
				*(ptr + check - 1) = '\0';
                printf ("\033[0;36m-- CUR LINE: %s\033[0;35m[end]\033[0m\n", *line);
                ptr = buff + check; //get start, pas de + 1 car le "plus 1" est le \n 
                printf("-- PTR LEFT OK - %s\n", ptr);
				printf("-- ALLOC LEFT - %d\n", BUFFER_SIZE - check);
				//ft_realloc(left, 0, ft_strlen(buff) - check + 1);
				left = ptr;
				ft_realloc(left, 0, ft_strlen(buff) - check);
				left[BUFFER_SIZE - check] = '\0';

				printf("-- REALLOC LEFT OK - %s\n", left);
                printf("-- STORE LEFT OK -\n");
                asleft = 1;
				printf("\033[0;31mLEFT END: \033[0;33m%s\033[0;35m[end]\033[0m\n", left);

                return (1);
            } else {
				printf("CHECK NO EOF - %d\n", check);
				printf("READCHECK NO EOF - %d\n", readcheck);
				  printf("-- READ END OF FILE -> BUFF:%s\033[0;35m[end]\033[0m\n", buff);
				if (readcheck == 0)
				{
					printf("FINAL RETURN\n");
					ft_realloc(*line, 0, ft_strlen(*line) + ft_strlen(buff));
                	//*line = ft_strjoin(*line, left);
					//*line = ft_strjoin(*line, buff);
					 printf ("\033[0;36m-- CUR LINEEND: %s\033[0;35m[end]\033[0m\n", *line);
					return (1);
				}
                ft_realloc(*line, 0, ft_strlen(*line) + BUFFER_SIZE);
                *line = ft_strjoin(*line, buff);
                printf ("\033[0;36m-- CUR LINE: %s\033[0;35m[end]\033[0m\n", *line);
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