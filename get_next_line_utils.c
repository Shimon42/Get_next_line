/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 14:44:05 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 22:49:12 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"
#include "debug.h"

char	*ft_strnjoin(char const *s1, char const *s2, int start, int size)
{
	char		*join;
	size_t		i;
	size_t		j;
	size_t		s1len;
	size_t		s2len;
	size_t		mallength;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	i = 0;
	j = 0;
	printf(UCYAN"s1 length:"YELO"%lu"RST"\n", s1len);
	printf(UCYAN"s2 length:"YELO"%lu"RST"\n", s2len);
	printf(UCYAN"start:"YELO"%d"RST"\n", start);
	printf(UCYAN"size:"YELO"%d"RST"\n", size);
	if ((size_t)start > s2len)
	start = s2len;
	if ((size_t)size > s2len)
		size = s2len;
	mallength = (s1len + size + 1);
	printf(UCYAN"Malloc length:"YELO"%lu"RST"\n", mallength);
	if ((join = malloc((mallength) * sizeof(char))) != NULL)
	{
		while (j < s1len)
			join[i++] = s1[j++];
		j = start;
		while (j < s2len && size--)
			join[i++] = s2[j++];
		join[i] = '\0';
	}
	return (join);
}

int		has_eol(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
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
