/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expo_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 16:53:07 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/21 17:25:04 by vrichese         ###   ########.fr       */
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
	char		tra[256];
	int			expo;
	int			j;
	int			i;

	j = 0;
	i = 0;
	(nbr < 0) ? (nbr *= -1) && (*flags |= NEG) : 0;
	nbr != nbr ? (*flags |= NAN) && (*pre = 0) : 0;
	nbr && nbr == nbr * 10 ? (*flags |= INF) && (*pre = 0) : 0;
	!(*flags & (INF | NAN)) ? calculation_expo(&nbr, &expo) : 0;
	!(*flags & (INF | NAN)) ? (j = putfloat(&tra[0], &nbr, flags, pre)) :
	inf_handler(&nbr, flags, wid, pre);
	adjustment_wid_pre(flags, wid, pre, j);
	*wid -= 4;
	fill_width(flags, wid, pre);
	while (i < j && EJECT(1))
		g_buff[g_count++] = tra[i++];
	!(*flags & (INF | NAN)) ? add_expo(flags, &expo) : 0;
	while ((*wid)-- > 0 && EJECT(1))
		g_buff[g_count++] = (*flags << 56) >> 56;
}
