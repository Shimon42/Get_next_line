/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 14:44:05 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 22:33:14 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strnjoin(char const *s1, char const *s2, int start, int size)
{
	char		*join;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (size < 0)
		size = ft_strlen(s2) - start;
	if ((join = ft_calloc((ft_strlen(s1) + size + 1), sizeof(char)))
		!= NULL)
	{
		while (s1[j] != '\0')
			join[i++] = s1[j++];
		j = start;
		while (s2[j] != '\0' && size--)
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
