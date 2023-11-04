/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_place.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnikia <cnikia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 18:35:17 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/30 18:42:32 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void			ft_erase_tet(char ***box, int a[2], t_lst *list, int y)
{
	int			x;

	x = 0;
	while (x < y)
	{
		(*box)[(a[0] + (*list).loc[x][0])][(a[1] + (*list).loc[x][1])] = '.';
		x++;
	}
}

static int		place_tet(char ***box, t_lst *list, int a[2], int y)
{
	int			x;

	x = 0;
	while (x < 4)
	{
		if ((a[0] + (*list).loc[x][0] < y) && (a[1] + (*list).loc[x][1] < y) &&
		(*box)[(a[0] + (*list).loc[x][0])][(a[1] + (*list).loc[x][1])] == '.')
			(*box)[(a[0] + (*list).loc[x][0])][(a[1] + (*list).loc[x][1])] =
			(char)((*list).index);
		else
			break ;
		x++;
		if (x == 4)
			return (x);
	}
	return (x);
}

static int		ft_sanya(char ***box, t_lst *tet_list, int x)
{
	int			result;
	int			inter;
	int			a[2];

	result = 0;
	a[0] = -1;
	a[1] = -1;
	if (tet_list == NULL)
		return (100);
	while (++(a[0]) < x && (a[1] = -1) == -1)
		while (++(a[1]) < x)
			if ((result = place_tet(box, tet_list, a, x)) == 4)
			{
				if ((inter = ft_sanya(box, (*tet_list).next, x)) != result)
				{
					if (inter == 100)
						return (100);
					ft_erase_tet(box, a, tet_list, result);
				}
			}
			else
				ft_erase_tet(box, a, tet_list, result);
	return (result);
}

char			**to_fill_matrix(int x)
{
	char		**matrix;
	int			i;

	if (!(matrix = (char **)malloc(sizeof(char *) * x)))
		return (NULL);
	i = 0;
	while (i < x)
	{
		if (!(matrix[i] = ft_strnew(x)))
		{
			while (--i >= 0)
				free(matrix[i]);
			free(matrix);
			return (NULL);
		}
		ft_memset(matrix[i], '.', x);
		i++;
	}
	return (matrix);
}

char			**ft_fillit(t_lst *tet_list, int x)
{
	char		**matrix;
	int			result;
	int			i;

	if (!(matrix = to_fill_matrix(x)))
		return (NULL);
	i = 0;
	while ((result = ft_sanya(&matrix, tet_list, x)) != 100)
	{
		i = x;
		while (--i >= 0)
			free(matrix[i]);
		free(matrix);
		x++;
		if (!(matrix = to_fill_matrix(x)))
			return (NULL);
	}
	i = 0;
	while (i < x)
		ft_putendl(matrix[i++]);
	i = x;
	while (--i >= 0)
		free(matrix[i]);
	free(matrix);
	return (matrix);
}
