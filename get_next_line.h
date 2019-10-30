/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 20:52:46 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 15:01:08 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct	s_gnl
{
	struct s_gnl	*next;
	int			fd;
	char		*line;
	char		*buff;
	char		*left;
	int			asleft;
	int			line_len;
	int			nbr_read;
	int			init;
	int			check;
}				t_gnl;

int				get_next_line(int fd, char **line);
int				ft_realloc(char *buff, int buff_length, int overright);
int				has_eol(char *s);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
void			ft_lstadd_front(t_gnl **alst, t_gnl *newlst);
void	ft_lstadd_back(t_gnl **alst, t_gnl *newlst);