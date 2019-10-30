/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 14:44:05 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 23:17:17 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strnjoin(char const *s1, char const *s2, int start, int size)
{
	char		*join;
	const char	*ps1;
	const char	*ps2;
	char		*pj;

	ps1 = s1;
	ps2 = s2;
	if(size == -1)
		size = ft_strlen(s2);
	ps2 += start;
	if ((join = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char)))
		!= NULL)
	{
		pj = join;
		while (*ps1 != '\0')
			*pj++ = *ps1++;
		while (*ps2 != '\0' && size--)
			*pj++ = *ps2++;
		*pj = '\0';
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

void	*ft_calloc(size_t count, size_t size)
{
	void			*obj;
	unsigned char	*pobj;

	if ((obj = malloc(count * size)) != NULL)
	{
		pobj = obj;
		while (count--)
			*pobj++ = '\0';
	}
	return (obj);
}

size_t	ft_strlen(const char *s)
{
	size_t length;

	length = 0;
	if (s != NULL)
		while (s[length])
			length++;
	return (length);
}