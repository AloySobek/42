/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:26:30 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/06 17:12:45 by vrichese         ###   ########.fr       */
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

void				roundd(char **str, int *pre, int sta, int end)
{
	int				flag;
	int				n;

	n = sta + (*pre > 0 ? *pre : 0);
	flag = 0;
	if ((*str)[n + 2] >= '5')
	{
		if ((*str)[n + 2] == '5')
			while (end > n + 2)
				if ((*str)[end--] > '0' && (flag = 1))
					break ;
		if ((*str)[n + 2] > '5')
			(*str)[n + 1] != '.' ? ++(*str)[n + 1] : ++(*str)[n];
		else if ((*str)[n + 2] == '5')
		{
			if ((*str)[n + 1] != '.')
				(*str)[n + 1] % 2 != 0 || flag ? ++(*str)[n + 1] : 0;
			else
				(*str)[n] % 2 != 0 || flag ? ++(*str)[n] : 0;
		}
	}
	while ((*str)[n + 1] > '9' && (*str)[n + 1] != '.')
	{
		(*str)[n + 1] -= 10;
		(*str)[n] != '.' ? ++(*str)[n] : ++(*str)[n - 1];
		n--;
	}
	while (n > 0 && (*str)[n] > '9')
	{
		(*str)[n] -= 10;
		++(*str)[n - 1];
		(*str)[n - 1] < '0' ? (*str)[n - 1] += '0' : 0;
		n--;
	}
}

void		get_bits(t_bits *tally, long double *nbr, size_t *flags, int *pre)
{
	(*tally).nbr.nbr = *nbr;
	(*tally).mant = *(long long *)&(*tally).nbr.nbr;
	(*tally).expo = (*tally).nbr.array[4] - 16383;
	(*tally).bit = 64;
	(*tally).exp = (*tally).expo;
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

void		pass_zero(char **med, size_t *flags, int *pre, int sta)
{
	int n;

	n = sta + (*pre > 0 ? *pre : 0);
	if (!(*flags & HAS))
	{
		while ((*med)[n--] == '0')
			(*pre)--;
		(*med)[n + 1] == '.' ? (*pre)-- : 0;
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
	int		i;
	int		flag;

	size = (*tally).exp;
	(*tally).expo = expo(med, (*tally).mid, (*tally).mid + (*tally).size);
	if ((*tally).expo < *pre && (*tally).expo >= -4)
	{
		*pre > 0 ? *pre -= ((*tally).expo + 1) : 0;
		roundd(med, pre, ((*tally).mid - 2), ((*tally).mid + (*tally).size));
		i = 0;
		while (i++ < *pre)
			(*med)[cou++] = '0';
		pass_zero(med, flags, pre, (*tally).mid - 1);
	}
	else
	{
		*pre > 0 ? *pre -= 1 : 0;
		(*tally).expo = calc_expo(med, pre, (*tally).mid, (*tally).mid + (*tally).size);
		(*tally).mid = 3;
		roundd(med, pre, (*tally).mid - 2, (*tally).mid + (*tally).size + ((*tally).expo > 0 ? (*tally).expo : 0));
		if ((*med)[0] > '0')
		{
			(*med)[2] = (*med)[1];
			(*med)[1] = '.';
			(*tally).expo++;
			(*tally).mid = 2;
		}
		i = 0;
		while (i++ < *pre)
			(*med)[cou++] = '0';
		pass_zero(med, flags, pre, (*tally).mid - 1);
		(*tally).expo != 0 ? add_expo(med, flags, tally, pre) && ((*pre) += 4) : 0;
	}
	return ((*tally).mid + *pre);
}

int		expo_handler(char **med, t_bits *tally, size_t *flags, int *pre,
		int cou)
{
	(*tally).exp = calc_expo(med, pre, (*tally).mid, (*tally).mid + (*tally).size);
	(*tally).mid = 3;
	roundd(med, pre, (*tally).mid - 2, (*tally).mid + (*tally).size + ((*tally).exp > 0 ? (*tally).exp : 0));
	if ((*med)[0] > '0')
	{
		(*med)[2] = (*med)[1];
		(*med)[1] = '.';
		(*tally).exp++;
		(*tally).mid = 2;
	}
	(*tally).expo = (*tally).exp;
	while ((*tally).exp++ < *pre)
		(*med)[cou++] = '0';
	*pre <= 0 && !(*flags & HAS) ? (*tally).mid-- : 0;
	add_expo(med, flags, tally, pre);
	return ((*tally).mid + *pre);
}

void		main_loop(t_long *whole, t_long *fract)

int			putfloat(char **med, t_bits *tally, size_t *flags, int *pre)
{
	t_long	whole;
	t_long	fract;
	int		cou;

	init_long(&whole, 0);
	init_long(&fract, 0);
	cou = 1;
	while ((*tally).bit-- > 0)
	{
		if ((*tally).mant & (1L << (*tally).bit))
			(*tally).exp >= 0 ? restorer(&whole, (*tally).exp, 2)
			: restorer(&fract, -(*tally).exp, 5);
		(*tally).exp--;
	}
	while (--(whole.len) >= 0)
		(*med)[cou++] = whole.nbr[whole.len] + '0';
	(*med)[cou++] = '.';
	(*tally).mid = cou;
	fract.power -= fract.len;
	(*tally).size = fract.len + (fract.power > 0 ? fract.power : 0);
	while (fract.power-- > 0)
		(*med)[cou++] = '0';
	while (--(fract.len) >= 0)
		(*med)[cou++] = fract.nbr[fract.len] + '0';
	free(whole.nbr);
	free(fract.nbr);
	if (SPEC == 'e' || SPEC == 'E')
		return (expo_handler(med, tally, flags, pre, cou));
	if (SPEC == 'g' || SPEC == 'G')
		return (g_handler(med, tally, flags, pre, cou));
	roundd(med, pre, ((*tally).mid - 2), ((*tally).mid + (*tally).size));
	fract.len = 0;
	while (fract.len++ < *pre)
		(*med)[cou++] = '0';
	*pre == 0 && !(*flags & HAS) ? (*tally).mid-- : 0;
	return ((*tally).mid + *pre);
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
