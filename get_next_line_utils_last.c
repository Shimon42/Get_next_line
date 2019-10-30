/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils_last.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/24 16:01:47 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 21:56:32 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int length;

	length = 0;
	if (s != NULL)
		while (s[length])
			length++;
	return (length);
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
		*pj = '\0';
	}
	return (join);
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