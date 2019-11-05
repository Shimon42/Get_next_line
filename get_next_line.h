/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 20:52:46 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/05 22:23:10 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct		s_gnl
{
	struct s_gnl	*next;
	int				fd;
	int				asleft;
	int				nbr_read;
	int				eol;
	char			*buff;
}					t_gnl;

int					get_next_line(int fd, char **line);
int					ft_realloc(char *buff, int buff_length, int overright);
int					has_eol(char *s);
char				*ft_strdup(const char *s1);
char				*ft_strnjoin(char const *s1,
					char const *s2,
					int start,
					int size);
size_t				ft_strlen(const char *s);
void				*ft_calloc(size_t count, size_t size);
#endif
