/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexadouble.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 16:53:07 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/06 21:32:51 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			my_roundd(char **med, t_bits *tally, int sta)
{
	int			i;

	i = sta - 1;
	if ((*med)[i] != '.')
	{
		++(*med)[i];
		while ((*med)[i] >= 16)
		{
			(*med)[i - 1] != '.' ? ++(*med)[i - 1] : ++(*med)[i - 2] && i--;
			(*med)[i] -= 16;
			i--;
		}
	}
	else
	{
		++(*med)[i - 1];
		if ((*med)[i - 1] >= 16)
		{
			(*tally).exhibi += 4;
			(*med)[i - 1] -= 16;
		}
	}
}

int				compute_nbr(long double nbr)
{
	nbr *= 16;
	nbr -= (int)nbr;
	if ((int)(nbr * 16) % 2)
		return (1);
	else
		return (0);
}

void			transfer(char **med, size_t *flags, t_bits *tally)
{
	if (!(*flags & BL))
		(*med)[0] >= 2 ? (*med)[0] = 1 && ((*tally).exhibi += 1) : 0;
}

int				calc_expo(char **str, long double *nbr, size_t *flags,
				int *count)
{
	int			expo;

	expo = 0;
	*nbr < 0 ? *nbr *= -1 : 0;
	if (*nbr > (*flags & BL ? 15 : 2))
		while (*nbr > ((*flags & BL) ? 16 : 2) && expo++ >= 0)
			*nbr /= 2;
	else
		while (*nbr != 0 && *nbr < ((*flags & BL) ? 8 : 1) && expo-- <= 0)
			*nbr *= 2;
	(*str)[(*count)++] = (int)(*nbr);
	*nbr -= (int)(*nbr);
	(*str)[(*count)++] = '.';
	return (expo);
}

void			expo_add(char **str, size_t *flags, int *count, int expo)
{
	if (*flags & BIG)
		(*str)[(*count)++] = 'P';
	else
		(*str)[(*count)++] = 'p';
	if (expo >= 0)
		(*str)[(*count)++] = '+';
	else
		((*str)[(*count)++] = '-') && (expo *= -1);
	expo < 10 ? ((*str)[(*count)++] = expo + '0') : 0;
	expo >= 10 && expo < 100 ? ((*str)[(*count)++] = expo / 10 + '0')
	&& ((*str)[(*count)++] = expo % 10 + '0') : 0;
	if (expo >= 100 && expo < 1000)
	{
		(*str)[(*count)++] = expo / 100 + '0';
		(*str)[(*count)++] = (expo % 100) / 10 + '0';
		(*str)[(*count)++] = expo % 10 + '0';
	}
	if (expo >= 1000 && expo < 10000)
	{
		(*str)[(*count)++] = expo / 1000 + '0';
		(*str)[(*count)++] = (expo % 1000) / 100 + '0';
		(*str)[(*count)++] = (expo % 100) / 10 + '0';
		(*str)[(*count)++] = expo % 10 + '0';
	}
}

void			puthex2(char **str, t_bits *tally, size_t *flags, int *count)
{
	(*tally).tmp_ex = -1;
	while (++((*tally).tmp_ex) < *count)
	{
		if ((*str)[(*tally).tmp_ex] == '.')
			continue;
		if ((*str)[(*tally).tmp_ex] < 10)
			(*str)[(*tally).tmp_ex] += 48;
		else
			(*str)[(*tally).tmp_ex] += (*flags & BIG ? 55 : 87);
	}
	if (*flags & POI)
		(*tally).middle <= 0 && !(*flags & HAS) ? (*count)-- : 0;
	else
	{
		(*tally).nbr.nb == 0 && !(*flags & HAS) ? (*count)-- : 0;
		(*tally).nbr.nb != 0 && !(*tally).size && (*tally).exhibi == 0
		&& !(*flags & HAS) ? (*count)-- : 0;
	}
}

int				puthex(char **str, t_bits *tally, size_t *flags, int *pre)
{
	long double nbr;
	int			count;

	count = 0;
	(*tally).size = 0;
	nbr = (*tally).nbr.nb;
	(*tally).exhibi = calc_expo(str, &nbr, flags, &count);
	(*tally).middle = *pre;
	while (nbr && (*flags & POI ? (*pre)-- > 0 : 1))
	{
		(*tally).size = 1;
		nbr *= 16;
		(*str)[count++] = (int)nbr;
		nbr -= (int)nbr;
	}
	transfer(str, flags, tally);
	if ((int)(nbr * 16) > 8 || ((int)(nbr * 16) == 8 && compute_nbr(nbr)))
		my_roundd(str, tally, count);
	puthex2(str, tally, flags, &count);
	if (*flags & POI)
		while ((*pre)-- > 0)
			(*str)[count++] = '0';
	expo_add(str, flags, &count, (*tally).exhibi);
	return (count);
}

void			print_hexadouble(long double nbr, size_t *flags, int *wid,
				int *pre)
{
	t_bits		tally;
	char		*med;
	int			i;
	int			j;

	j = 0;
	i = 0;
	bits_handler(&tally, &nbr, flags, pre);
	!(*flags & (INF | NAN)) ? med = (char *)malloc(tally.size * 4) : 0;
	!(*flags & (INF | NAN)) ? ft_bzero(med, tally.size) : 0;
	!(*flags & (INF | NAN)) ? j = puthex(&med, &tally, flags, pre) : 0;
	adjustment_wid_pre(flags, wid, pre, j);
	fill_width(flags, wid);
	(*flags & (INF | NAN)) && EJECT(3) ? inf_handler(flags) : 0;
	while (i < j && EJECT(1) && !(*flags & (INF | NAN)))
		g_buff__.g_buff[g_buff__.g_count++] = med[i++];
	while ((*wid)-- > 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = (*flags << 56) >> 56;
	!(*flags & (INF | NAN)) ? free(med) : 0;
}
