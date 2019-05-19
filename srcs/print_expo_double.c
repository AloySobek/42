/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expo_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 16:53:07 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/19 20:31:44 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			calculation_expo(long double *nbr, int *expo)
{
	if (*nbr >= 10)
	{
		while (*nbr >= 10)
		{
			*nbr /= 10;
			(*expo)++;
		}
	}
	else if (*nbr < 1)
	{
		while (*nbr < 1)
		{
			*nbr *= 10;
			(*expo)--;
		}
	}
}

void			add_expo(size_t *flags, int *expo)
{
	if (*flags & BIG)
		g_buff[g_count++] = 'E';
	else
		g_buff[g_count++] = 'e';
	if (expo >= 0)
		g_buff[g_count++] = '+';
	else
		(g_buff[g_count++] = '-') && (*expo *= -1);
	if (*expo >= 10)
	{
		g_buff[g_count++] = *expo / 10 + '0';
		g_buff[g_count++] = *expo % 10 + '0';
	}
	else
	{
		g_buff[g_count++] = '0';
		g_buff[g_count++] = *expo + '0';
	}
}

void			print_expo_double(long double nbr, size_t *flags, int *wid,
				int *pre)
{
	long double	rou;
	long double	dis;
	size_t		cou;
	int			expo;

	(nbr < 0) ? (nbr *= -1) && (*flags |= NEG) : 0;
	cou = 0;
	dis = 1.0;
	calculation_expo(&nbr, &expo);
	rou = nbr;
	while ((rou /= 10) >= 1 && ++cou > 0)
		dis *= 10;
	*wid -= *pre > 0 ? *pre + 1 : 0;
	*wid -= 4;
	fill_width(flags, wid, pre);
	putfloat(&nbr, &dis, pre);
	while ((*pre)-- > 0 && EJECT(1))
		g_buff[g_count++] = '0';
	add_expo(flags, &expo);
	while ((*wid)-- > 0 && EJECT(1))
		g_buff[g_count++] = (*flags << 56) >> 56;
}
