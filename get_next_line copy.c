/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 20:22:38 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/22 17:05:41 by siferrar    ###    #+. /#+    ###.fr     */
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

	if (overright)
		buff_size = overright;
	else
		buff_size += buff_length;
	tmp = malloc(buff_size * sizeof(char));
	ft_strlcpy(tmp, buff, buff_size);
	buff[buff_size] = *tmp;
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
	int i;

	i = 0;
	while (s[i])
		if(s[i++] == '\n')
			return (i);
	return (-1);
}

int get_next_line(int fd, char **line)
{
	char		*buff;
	int			check;
	static char *left;
	static int	asleft;
    char    *ptr;

	if (!asleft)
		left = NULL;
	check = -1;
	printf("LEFT BEGIN: \033[0;33m%s\033[0m\n", left);
	if ((buff = malloc(BUFFER_SIZE * sizeof(char))) != NULL)
    {
		while (check < 0)
		{
			if (asleft)
			{
				printf("\nAS LEFT ");
				if ((check = has_eol(left)) > 0)
				{
					*line =  ft_strdup(&left[check]);
					printf("----- LINE FROM LEFT: %s\n", *line);
					asleft = 0;
					left = "";
				} else if (read(fd, buff, BUFFER_SIZE))
				{
					printf("------- Line left not ended\n");
					if ((check = has_eol(buff)) < 0) // NOT END - OK
					{
						ft_realloc(*line, BUFFER_SIZE, 0); // REALLOC + buff size
						*line = ft_strjoin(*line, buff); // line = line + curbuff
						printf("line not end: %s\n", *line);
					}
					else // END FROM LEFT
					{
                        printf("END FROM LEFT --\n");
                        ft_realloc(*line, 0, ft_strlen(*left) + check);
                        ptr = *line + (ft_strlen(*line));
                        printf("PTR: %s\n", ptr);
                        ft_strlcpy(ptr, buff, check); // line = line + curbuff
						printf("\n--\033[1;31mLineBUFF: %s\n\n", buff);
						printf("--LineFL: %s\n\n", *line);
						printf("--LeftFL: %s\n\n\033[0m", left);
                        *line = ft_strjoin(left, buff);
                        if (check >= 0 && check <= BUFFER_SIZE)
						    asleft = 1;
                        else
                        {
                            asleft = 0;
                            left = "";
                        }
                        return (1);
					}
				}
			}
			else if (read(fd, buff, BUFFER_SIZE))
			{
				if ((check = has_eol(buff)) < 0)
				{
					ft_realloc(*line, BUFFER_SIZE, 0);
					*line = ft_strjoin(*line, buff);
					//printf("line not end: %s\n", *line);
				} else
				{
					ft_realloc(*line, 0, ft_strlen(*line) + check);
					ft_strlcpy(buff, buff, check);
					left = ft_strdup(&buff[check]);
					*line = ft_strjoin(*line, buff);
					printf("line:%s\n", *line);
					printf("left:%s\n", left);
					asleft = 1;
					return (1);
				}
			}
		}
    }
	return (1);
}


int main(void)
{
	int fd = open("test.txt", O_CREAT | O_RDWR);
	char *line;
	char **ptr;
	int i = 0;

	ptr = &line;
	while (i < 3)
	{
		printf("\n\033[1;34m--------------- GNL - %d ------------------\033[0m\n\n", i);
		get_next_line(fd, ptr);
		printf("\n\033[0;32mRES %d -> %s\033[0m\n", i++, line);
	}
}