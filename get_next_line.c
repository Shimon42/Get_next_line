/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 20:22:38 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 22:15:11 by siferrar    ###    #+. /#+    ###.fr     */
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
	printf("%d\n", buff_size);
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
	while (s[i] != '\0')
		if(s[i] == '\n')
			return (i);
	return (-1);
}

int get_next_line(int fd, char **line)
{
	char	*buff;
	int		i;
	int check;

	check = 0;
	i = 1;
	if ((buff = malloc(BUFFER_SIZE * sizeof(char))) != NULL)
    {
		while (!check)
		{
			if (read(fd, buff, BUFFER_SIZE))
			{
				if ((check = has_eol) < 0)
				{
					ft_realloc(*line, BUFFER_SIZE, NULL);
					*line = ft_strjoin(*line, buff);
					printf("%s", *line);
				} else
				{
					ft_realloc(*line, NULL, ft_strlen(*line) + check);
					buff = ft_strlcpy(buff, buff, check);
					*line = ft_strjoin(*line, buff);
					printf("%s", *line);
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

	ptr = &line;
	get_next_line(fd, ptr);
}