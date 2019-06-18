/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern_funct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnikia <cnikia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 19:58:30 by cnikia            #+#    #+#             */
/*   Updated: 2019/04/29 18:36:27 by cnikia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fillit.h"

void	free_tet(char ***tet)
{
	int	b;

	b = 0;
	if ((*tet))
	{
		while (b < 4)
		{
			if ((*tet)[b])
				free((*tet)[b]);
			b++;
		}
		free((*tet));
	}
}

void	new_cords_dlc(char ***str, int ***tet)
{
	int		a;
	int		b;
	int		c;

	a = 0;
	c = 0;
	while (a < 4)
	{
		b = 0;
		while (b < 4)
		{
			if ((*str)[a][b] == '*')
			{
				(*tet)[c][0] = a;
				(*tet)[c][1] = b;
				c++;
			}
			b++;
		}
		a++;
	}
}
