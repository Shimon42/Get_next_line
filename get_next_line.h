/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 20:52:46 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 22:13:51 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>

typedef struct	s_gnl
{
	char	*line_buff;
	int		line_len;
	int		nbr_read;
}				t_gnl;

int				get_next_line(int fd, char **line);
char			*ft_strdup(const char *s1);
int				ft_realloc(char *buff, int buff_length, int overright);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
int				has_eol(char *s);