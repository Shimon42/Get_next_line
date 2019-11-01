/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 14:44:05 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/01 21:48:53 by siferrar    ###    #+. /#+    ###.fr     */
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
	ps2 += start;
	printf("- Malloc join:\n\
	s1:\033[0;31m%s\033[0m\n\
	Size s1:\033[0;31m%lu\033[0m\n\
	s2:\033[0;33m%s\033[0m\n\
	Size s2:\033[0;33m%lu\033[0m\n\
	Start:%d\n\
	Size:%d\n\
	mallocSize:%lu\n\
	\033[0m", s1, ft_strlen(s1), ps2, ft_strlen(s2), start, size, ft_strlen(s1) + size + 1);
	if(size == -1)
		size = ft_strlen(ps2) - start;
	if ((join = ft_calloc((ft_strlen(s1) + size + 1), sizeof(char)))
		!= NULL)
	{
		pj = join;
		while (*ps1 != '\0')
			*pj++ = *ps1++;
		while (*ps2 != '\0' && size--)
			*pj++ = *ps2++;
		*pj = '\0';
	}
	printf("-Malloc endS1->\033[0;34m%s\033[0;35m[end]\033[0m\n", s1);
	printf("-Malloc endS2->\033[0;34m%s\033[0;35m[end]\033[0m\n", s2);
	printf("-Malloc end->\033[0;34m%s\033[0;35m[end]\033[0m\n", join);
	return (join);
}

int has_eol(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if(s[i] == '\n')
			return (i);
		i++;
	}
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