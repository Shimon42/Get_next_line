/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 14:44:05 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 15:00:38 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl		*ft_lstlast(t_gnl *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_gnl **alst, t_gnl *newlst)
{
	t_gnl *tmp;

	if (*alst)
	{
		tmp = ft_lstlast(*alst);
		tmp->next = newlst;
	}
	else
		*alst = newlst;
}