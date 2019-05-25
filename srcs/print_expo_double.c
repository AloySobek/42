/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expo_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 16:53:07 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/25 20:05:39 by vrichese         ###   ########.fr       */
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
	if (*expo >= 0)
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
	t_bits		tally;
	char		*med;
	int			expo;
	int			j;
	int			i;

	!(*flags & (INF | NAN)) ? calculation_expo(&nbr, &expo) : 0;
	get_bits(&tally, &nbr, flags, pre);
	!(*flags & (INF | NAN)) ? med = (char *)malloc(tally.size) : 0;
	!(*flags & (INF | NAN)) ? ft_bzero(med, tally.size) : 0;
	j = 0;
	i = 1;
	!(*flags & (INF | NAN)) ? j = putfloat(&med, &tally, flags, pre) : 0;
	adjustment_wid_pre(flags, wid, pre, j);
	*wid -= 4;
	fill_width(flags, wid, pre);
	(*flags & (INF | NAN)) ? inf_handler(flags, wid, pre) : 0;
	!(*flags & (INF | NAN)) && med[0] != 0 ? i = 0 : 0;
	while (i <= j && EJECT(1) && !(*flags & (INF | NAN)))
		g_buff[g_count++] = med[i++];
	!(*flags & (INF | NAN)) ? add_expo(flags, &expo) : 0;
	while ((*wid)-- > 0 && EJECT(1))
		g_buff[g_count++] = (*flags << 56) >> 56;
}
