/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:26:30 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/27 02:02:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		inf_handler(size_t *flags, int *wid, int *pre)
{
	if (*flags & NAN)
		if (!(*flags & BIG) && (g_buff__.g_buff[g_buff__.g_count++] = 'n'))
		{
			g_buff__.g_buff[g_buff__.g_count++] = 'a';
			g_buff__.g_buff[g_buff__.g_count++] = 'n';
		}
		else
		{
			g_buff__.g_buff[g_buff__.g_count++] = 'N';
			g_buff__.g_buff[g_buff__.g_count++] = 'A';
			g_buff__.g_buff[g_buff__.g_count++] = 'N';
		}
	else if (*flags & INF)
	{
		if (!(*flags & BIG) && (g_buff__.g_buff[g_buff__.g_count++] = 'i'))
		{
			g_buff__.g_buff[g_buff__.g_count++] = 'n';
			g_buff__.g_buff[g_buff__.g_count++] = 'f';
		}
		else if (*flags & BIG && (g_buff__.g_buff[g_buff__.g_count++] = 'I'))
		{
			g_buff__.g_buff[g_buff__.g_count++] = 'N';
			g_buff__.g_buff[g_buff__.g_count++] = 'F';
		}
	}
}

void		get_bits(t_bits *tally, long double *nbr, size_t *flags, int *pre)
{
	int		size;

	(*tally).nbr.nbr = *nbr;
	(*tally).mant = *(long long *)&(*tally).nbr.nbr;
	(*tally).expo = (*tally).nbr.array[4] - 16383;
	(*tally).sign = (*tally).nbr.array[4] >> 15;
	*nbr != *nbr ? (*flags |= NAN) && (*pre = 0) : 0;
	*nbr && *nbr == (*nbr * 10) ? (*flags |= INF) && (*pre = 0) : 0;
	(*tally).sign ? *flags |= NEG : 0;
	if ((*tally).expo < 0)
		(*tally).size = ((*tally).expo - 63) * -1;
	else if ((*tally).expo <= 63 && (*tally).expo >= 0)
	{
		(*tally).size = 64;
		(*tally).size < *pre ? (*tally).size += *pre : 0;
	}
	else
		(*tally).size = (*tally).expo;
}

void		pass_zero(char **med, size_t *flags, int che, int *pre)
{
	if (((SPEC) == 'g' || (SPEC) == 'G') && !(*flags & HAS) &&
		(*med)[che + *pre] == '0')
	{
		while ((*med)[che + *pre] == '0')
			(*pre)--;
		(*med)[*pre] == '.' ? (*pre)-- : 0;
	}
}

/*void		fill_str(char **med, int zer, int che, int *pre)
{
	int i;
	int cou;

	i = 0;
	cou = 1;
	while (!(*med)[i])
		i++;
	zer ? (*med)[(*cou)++] = '0' : 0;
	while (i <= che)
		(*med)[cou++] = ((*med)[bit++] + '0');
	*pre > 0 ? (*med)[cou++] = '.' : 0;
	bit = che + 2;
	while (bit <= *pre + che + 2)
		(*med)[cou++] = (*med)[bit++] + '0';
}*/

int			putfloat(char **med, t_bits *tally, size_t *flags, int *pre)
{
	int		end;
	int		cou;
	int		bit;
	int 	tes;

	cou = 1;
	bit = 64;
	end = (*tally).expo > 0 ? (*tally).expo / 2 + 1 : 2;
	while (bit-- > 0)
	{
		if ((*tally).mant & (1L << bit))
			(*tally).expo >= 0 ? add_power(med, (*tally).expo, end) :
			add_power_neg(med, (*tally).expo, end + 2);
		(*tally).expo--;
	}
	bit = 1;
	while (!(*med)[bit])
		bit++;
	(*tally).nbr.array[4] - 16383 < 0 ? (*med)[cou++] = '0' : 0;
	while (bit <= end)
		(*med)[cou++] = ((*med)[bit++] + '0');
	*pre > 0 ? (*med)[cou++] = '.' : 0;
	end += 2;
	bit = cou;
	tes = (*tally).nbr.array[4] - 16383 - 63;
	tes < 0 ? tes *= -1 : 0;
	while (end < tes)
		(*med)[cou++] = (*med)[end++] + '0';
	roundd(med, pre, bit, end);
	while (end++ <= *pre + 3)
		(*med)[cou++] = '0';
	*flags & EXP ? calc_expo(med, pre, bit);
	pass_zero(med, flags, end, pre);
	!(*flags & (INF | NAN)) && *flags & EXP ? add_expo(med, end + *pre, flags, &bit) && (*pre += 4) : 0;
	return (bit + *pre);
}

void		print_double(long double nbr, size_t *flags, int *wid, int *pre)
{
	t_bits	tally;
	char	*med;
	int		i;
	int		j;

	j = 0;
	i = 1;
	get_bits(&tally, &nbr, flags, pre);
	!(*flags & (INF | NAN)) ? med = (char *)malloc(tally.size * 2) : 0;
	!(*flags & (INF | NAN)) ? ft_bzero(med, tally.size) : 0;
	!(*flags & (INF | NAN)) ? j = putfloat(&med, &tally, flags, pre) : 0;
	!(*flags & (INF | NAN)) && med[0] >= '0' ? i = 0 : 0;
	adjustment_wid_pre(flags, wid, pre, j - i);
	fill_width(flags, wid, pre);
	(*flags & (INF | NAN)) && EJECT(3) ? inf_handler(flags, wid, pre) : 0;
	while (i < j && EJECT(1) && !(*flags & (INF | NAN)))
		g_buff__.g_buff[g_buff__.g_count++] = med[i++];
	while ((*wid)-- > 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = (*flags << 56) >> 56;
	!(*flags & (INF | NAN)) ? free(med) : 0;
}
