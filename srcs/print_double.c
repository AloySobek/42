/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:26:30 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/30 19:25:50 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		inf_handler(size_t *flags)
{
	if (*flags & NAN)
	{
		if (!(*flags & BIG) && EJECT(3) && (BUFF.g_buff[BUFF.g_count++] = 'n')
			&& (BUFF.g_buff[BUFF.g_count++] = 'a'))
			BUFF.g_buff[BUFF.g_count++] = 'n';
		else if (EJECT(3) && (BUFF.g_buff[BUFF.g_count++] = 'N'))
		{
			BUFF.g_buff[BUFF.g_count++] = 'A';
			BUFF.g_buff[BUFF.g_count++] = 'N';
		}
	}
	else if (*flags & INF)
	{
		if (!(*flags & BIG) && EJECT(3) && (BUFF.g_buff[BUFF.g_count++] = 'i'))
		{
			BUFF.g_buff[BUFF.g_count++] = 'n';
			BUFF.g_buff[BUFF.g_count++] = 'f';
		}
		else if (*flags & BIG && EJECT(3) && (BUFF.g_buff[BUFF.g_count++] = 'I')
				&& (BUFF.g_buff[BUFF.g_count++] = 'N'))
			BUFF.g_buff[BUFF.g_count++] = 'F';
	}
}

void		get_bits(t_bits *tally, long double *nbr, size_t *flags, int *pre)
{
	(*tally).nbr.nbr = *nbr;
	(*tally).mant = *(long long *)&(*tally).nbr.nbr;
	(*tally).expo = (*tally).nbr.array[4] - 16383;
	(*tally).sign = (*tally).nbr.array[4] >> 15;
	*nbr != *nbr ? (*flags |= NAN) && (*pre = 0) : 0;
	*nbr && *nbr == (*nbr * 10) ? (*flags |= INF) && (*pre = 0) : 0;
	(*tally).sign ? *flags |= NEG : 0;
	*flags & NAN && *flags & NEG ? (*flags ^= NEG) : 0;
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

void		pass_zero(char **med, size_t *flags, int *pre, int bit)
{
	int flag;

	flag = 0;
	if (!(*flags & HAS))
	{
		if ((*med)[1] == '0')
			flag = 1;
		while ((*med)[bit + *pre - 1] == '0')
			(*pre)--;
		flag && (*flags & POI && *pre == -1) ? (*pre)++ : 0;
		(*med)[bit + *pre - 1] == '.' ? (*pre)-- : 0;
	}
}

int			expo(char **med, int sta, int end)
{
	int expo;
	int i;

	i = 1;
	expo = 0;
	(*med)[0] > '0' ? i = 0 : 0;
	if ((*med)[i] != '0')
	{
		while ((*med)[expo] != '.' && expo < sta)
			expo++;
		expo -= 2;
	}
	else
	{
		while ((*med)[expo] <= '0' && expo < end)
			expo++;
		if ((*med)[expo] < '1' || (*med)[expo] > '9')
			return (0);
		expo -= 2;
		(*med)[2] != '.' ? expo += 1 : 0;
		expo *= -1;
	}
	return (expo);
}

int			g_handler(char **med, t_bits *tally, size_t *flags, int *pre,
			int mid, int cou, int bit)
{
	int		size;

	size = (*tally).size;
	(*tally).size = expo(med, bit, (*tally).size);
	if ((*tally).size < *pre && (*tally).size >= -4)
	{
		*pre > 0 ? *pre -= ((*tally).size + 1) : 0;
		roundd(med, pre, bit - 1, mid);
		while (cou <= *pre + bit)
			(*med)[cou++] = '0';
		pass_zero(med, flags, pre, bit);
	}
	else
	{
		*pre > 0 ? *pre -= 1 : 0;
		(*tally).size = calc_expo(med, pre, bit, size);
		if (*pre + (*tally).size <= 0 && (*flags & HAS))
			roundd(med, pre, bit - 2, mid);
		else
			roundd(med, pre, bit - 1, mid);
		while (cou <= *pre + bit)
			(*med)[cou++] = '0';
		pass_zero(med, flags, pre, bit);
		if ((*tally).size != 0 && add_expo(med, flags, (*tally).size, pre, bit))
			(*pre += 4);
	}
	return (bit + *pre);
}

int			putfloat(char **med, t_bits *tally, size_t *flags, int *pre)
{
	int		mid;
	int		cou;
	int		bit;

	mid = (*tally).expo > 0 ? (*tally).expo / 2 + 1 : 2;
	(*tally).size = (*tally).expo - 63;
	(*tally).size < 0 ? (*tally).size *= -1 : 0;
	bit = 64;
	cou = 1;
	while (bit-- > 0)
	{
		if ((*tally).mant & (1L << bit))
			(*tally).expo >= 0 ? add_power(med, (*tally).expo, mid) :
			add_power_neg(med, (*tally).expo, mid + 2);
		(*tally).expo--;
	}
	while (!(*med)[++bit] && bit < mid)
		;
	while (bit <= mid)
		(*med)[cou++] = ((*med)[bit++] + '0');
	*pre > 0 || (*flags & HAS) ? (*med)[cou++] = '.' : 0;
	bit = cou;
	mid += 2;
	while (mid < (*tally).size + 4)
		(*med)[cou++] = (*med)[mid++] + '0';
	if (SPEC == 'g' || SPEC == 'G')
		return (g_handler(med, tally, flags, pre, mid, cou, bit));
	if (SPEC == 'e' || SPEC == 'E')
		(*tally).size = calc_expo(med, pre, bit, (*tally).size);
	if ((SPEC == 'e' || SPEC == 'E') && *pre + (*tally).size <= 0 && (*flags & HAS))
		roundd(med, pre, bit - 2, mid);
	else
		roundd(med, pre, bit - 1, mid);
	if ((*med)[0] > '0')
	{
		(*med)[2] = (*med)[1];
		(*med)[1] = '.';
		(*tally).size++;
		(*pre)--;
	}
	while (cou <= *pre + bit)
		(*med)[cou++] = '0';
	SPEC == 'e' || SPEC == 'E' ? add_expo(med, flags, (*tally).size, pre, bit) : 0;
	(*tally).size < 0 ? (*tally).size *= -1 : 0;
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
	!(*flags & (INF | NAN)) ? med = (char *)malloc(tally.size * 4) : 0;
	!(*flags & (INF | NAN)) ? ft_bzero(med, tally.size) : 0;
	!(*flags & (INF | NAN)) ? j = putfloat(&med, &tally, flags, pre) : 0;
	!(*flags & (INF | NAN)) && med[0] >= '0' ? i = 0 : 0;
	adjustment_wid_pre(flags, wid, pre, j - i);
	fill_width(flags, wid);
	(*flags & (INF | NAN)) && EJECT(3) ? inf_handler(flags) : 0;
	SPEC == 'e' || SPEC == 'E' ? j += 4 : 0;
	while (i < j && EJECT(1) && !(*flags & (INF | NAN)))
		BUFF.g_buff[BUFF.g_count++] = med[i++];
	while ((*wid)-- > 0 && EJECT(1))
		BUFF.g_buff[BUFF.g_count++] = (*flags << 56) >> 56;
	!(*flags & (INF | NAN)) ? free(med) : 0;
}
