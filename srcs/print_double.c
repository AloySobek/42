/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:26:30 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/31 15:55:42 by vrichese         ###   ########.fr       */
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
	(*tally).bit = 64;
	(*tally).nbr.nbr = *nbr;
	(*tally).mant = *(long long *)&(*tally).nbr.nbr;
	(*tally).expo = (*tally).nbr.array[4] - 16383;
	(*tally).sign = (*tally).nbr.array[4] >> 15;
	(*tally).mid = (*tally).expo > 0 ? (*tally).expo / 2 + 1 : 2;
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
			int cou)
{
	int		size;

	size = (*tally).size;
	(*tally).size = expo(med, (*tally).bit, (*tally).size);
	if ((*tally).size < *pre && (*tally).size >= -4)
	{
		*pre > 0 ? *pre -= ((*tally).size + 1) : 0;
		roundd(med, pre, (*tally).bit - 1, (*tally).mid);
		while (cou <= *pre + (*tally).bit)
			(*med)[cou++] = '0';
		pass_zero(med, flags, pre, (*tally).bit);
	}
	else
	{
		*pre > 0 ? *pre -= 1 : 0;
		(*tally).size = calc_expo(med, pre, (*tally).bit, size);
		//å(*tally).bit -= (*tally).size;
		if (*pre + (*tally).size <= 0 && (*flags & HAS))
			roundd(med, pre, (*tally).bit - 2, (*tally).mid);
		else
			roundd(med, pre, (*tally).bit - 1, (*tally).mid);
		while (cou <= *pre + (*tally).bit)
			(*med)[cou++] = '0';
		pass_zero(med, flags, pre, (*tally).bit);
		if ((*tally).size != 0 && add_expo(med, flags, tally, pre))
			*pre += 4;
	}
	return ((*tally).bit + *pre);
}

int		expo_handler(char **med, t_bits *tally, size_t *flags, int *pre,
		int cou)
{
	(*tally).size = calc_expo(med, pre, (*tally).bit, (*tally).expo);
	(*tally).bit = 2;
	*pre > 0 || *flags & HAS ? ++(*pre) : 0;
	roundd(med, pre, (*tally).bit, (*tally).mid);
	if ((*med)[0] > '0')
	{
		(*med)[2] = (*med)[1];
		(*med)[1] = '.';
		(*tally).size++;
		(*pre)--;
	}
	while (cou <= *pre + (*tally).bit)
		(*med)[cou++] = '0';
	add_expo(med, flags, tally, pre);
	(*tally).size < 0 ? (*tally).size *= -1 : 0;
	return ((*tally).bit + *pre);
}

int			putfloat(char **med, t_bits *tally, size_t *flags, int *pre)
{
	int		cou;

	cou = 1;
	while ((*tally).bit-- > 0)
	{
		if ((*tally).mant & (1L << (*tally).bit))
			(*tally).expo >= 0 ? add_power(med, (*tally).expo, (*tally).mid) :
			add_power_neg(med, (*tally).expo, (*tally).mid + 2);
		(*tally).expo--;
	}
	while (!(*med)[++(*tally).bit] && (*tally).bit < (*tally).mid)
		;
	while ((*tally).bit <= (*tally).mid)
		(*med)[cou++] = ((*med)[(*tally).bit++] + '0');
	(*med)[cou++] = '.';
	(*tally).bit = cou - 2;
	(*tally).mid += 2;
	if ((*tally).expo > 0)
		(*tally).expo += (*tally).mid;
	else
		(*tally).expo = -(*tally).expo + (*tally).mid;
	while ((*tally).mid < (*tally).expo)
		(*med)[cou++] = (*med)[(*tally).mid++] + '0';
	if (SPEC == 'e' || SPEC == 'E')
		return (expo_handler(med, tally, flags, pre, cou - 1));
	if (SPEC == 'g' || SPEC == 'G')
		return (g_handler(med, tally, flags, pre, cou));
	roundd(med, pre, (*tally).bit, (*tally).mid);
	while (cou <= *pre + (*tally).bit)
		(*med)[cou++] = '0';
	return ((*tally).bit + *pre);
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
