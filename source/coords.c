/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnikia <cnikia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 19:20:20 by cnikia            #+#    #+#             */
/*   Updated: 2019/04/30 15:13:25 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fillit.h"

static void			cords_move(int ***tet)
{
	int		a;
	int		x;
	int		y;

	a = 0;
	y = 3;
	x = 3;
	while (a < 4)
	{
		if ((*tet)[a][0] < y)
			y = (*tet)[a][0];
		if ((*tet)[a][1] < x)
			x = (*tet)[a][1];
		a++;
	}
	a = 0;
	while (a < 4)
	{
		(*tet)[a][0] -= y;
		(*tet)[a][1] -= x;
		a++;
	}
}

static int			**new_cords(char ***str)
{
	int		**tet;
	int		a;

	a = 0;
	if (!(tet = (int **)malloc(sizeof(int **) * 4)))
		return (NULL);
	while (a < 4)
	{
		if (!(tet[a] = (int *)malloc(sizeof(int) * 2)))
		{
			while (a-- >= 0)
				free(tet[a]);
			free(tet);
			return (NULL);
		}
		a++;
	}
	new_cords_dlc(str, &tet);
	cords_move(&tet);
	free_tet(str);
	return (tet);
}

static t_lst		*ft_create_elem(int **loc)
{
	t_lst		*new_lst;

	if (!(new_lst = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	(*new_lst).loc = loc;
	(*new_lst).next = NULL;
	return (new_lst);
}

static void			ft_create_or_add_list(t_lst **list, char ***str)
{
	t_lst	*iter;
	int		**loc;

	if (!(loc = new_cords(str)))
		fillit_list_exit(5, list);
	iter = *list;
	if (!iter)
	{
		*list = ft_create_elem(loc);
		(**list).index = 65;
		return ;
	}
	while ((*iter).next)
		iter = (*iter).next;
	(*iter).next = ft_create_elem(loc);
	(*((*iter).next)).index = (*iter).index + 1;
}

t_lst				*coords(int fd)
{
	t_lst	*tet;
	char	**str;

	tet = NULL;
	if (!(str = tetrimino_read(fd, NULL)))
		fillit_list_exit(5, NULL);
	ft_create_or_add_list(&tet, &str);
	while ((str = tetrimino_read(fd, &tet)))
	{
		ft_create_or_add_list(&tet, &str);
	}
	return (tet);
}
