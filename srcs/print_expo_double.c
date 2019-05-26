/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expo_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 16:53:07 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/27 02:02:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			add_expo(char **str, int cou, size_t *flags, int *expo)
{
	if (*flags & BIG)
		(*str)[cou++] = 'E';
	else
		(*str)[cou++] = 'e';
	if (*expo >= 0)
		(*str)[cou++] = '+';
	else
		((*str)[cou++] = '-') && (*expo *= -1);
	if (*expo >= 10)
	{
		(*str)[cou++] = *expo / 10 + '0';
		(*str)[cou++] = *expo % 10 + '0';
	}
	else
	{
		(*str)[cou++] = '0';
		(*str)[cou++] = *expo + '0';
	}
	return (1);
}

void		calc_expo(char **med, int *pre, int end)
{
	int swim;
	int expo;
	int real;
	int i;

	expo = 0;
	(*med)[0] > '0' ? i = 0 : (i = 1);
	if ((*med)[i] != '0')
	{
		real = end;
		while ((*med)[expo] != '.' && expo <= real)
			(expo)++;
		swim = expo;
		while (swim > 2)
			(*med)[swim] = (*med)[swim-- - 1];
		*pre > 0 ? (*med)[swim] = '.' : 0;
		expo -= 2;
		*pre -= expo;
	}
	else
	{
		real = end + *pre;
		while ((*med)[expo] <= '0' && expo <= real)
			expo++;
		((*med)[i] = (*med)[expo]);
		*pre > 0 ? ((*med)[i + 1] = '.') : 0;
		i += 2;
		swim = expo + 1;
		while (swim <= real)
			(*med)[i++] = (*med)[swim++];
		while (i < why)
			(*med)[i++] = '0';
		*expo -= 2;
	}
}

void		print_expo_double(long double nbr, size_t *flags, int *wid,
			int *pre)
{
	t_bits	tally;
	char	*med;
	int		expo;
	int		j;
	int		i;

	j = 0;
	i = 1;
	get_bits(&tally, &nbr, flags, pre);
	!(*flags & (INF | NAN)) ? med = (char *)malloc(tally.size * 2) : 0;
	!(*flags & (INF | NAN)) ? ft_bzero(med, tally.size) : 0;
	!(*flags & (INF | NAN)) ? j = putfloat(&med, &tally, flags, pre) : 0;
	!(*flags & (INF | NAN)) && med[0] != 0 ? i = 0 : 0;
	adjustment_wid_pre(flags, wid, pre, j);
	fill_width(flags, wid, pre);
	(*flags & (INF | NAN)) && EJECT(3) ? inf_handler(flags, wid, pre) : 0;
	while (i <= j && EJECT(1) && !(*flags & (INF | NAN)))
		g_buff__.g_buff[g_buff__.g_count++] = med[i++];
	while ((*wid)-- > 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = (*flags << 56) >> 56;
}
