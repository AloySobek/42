/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnikia <cnikia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:14:08 by cnikia            #+#    #+#             */
/*   Updated: 2019/04/29 20:57:17 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fillit.h"

static void		remove_lst(t_lst **list)
{
	int		a;
	t_lst	*lst;
	t_lst	*wst;

	lst = *list;
	while (lst)
	{
		if (lst->loc)
		{
			a = 0;
			while (a < 4)
			{
				if (lst->loc[a])
				{
					free(lst->loc[a]);
				}
				a++;
			}
			free(lst->loc);
		}
		wst = lst->next;
		free(lst);
		lst = wst;
	}
}

void			fillit_list_exit(int a, t_lst **list)
{
	if (!(list))
	{
		ft_putstr("error\n");
		exit(a);
	}
	remove_lst(list);
	if (a == 10)
		exit(a);
	ft_putstr("error\n");
	exit(a);
}

void			fillit_exit(int a, char ***tet, t_lst **list)
{
	free_tet(tet);
	fillit_list_exit(a, list);
}
