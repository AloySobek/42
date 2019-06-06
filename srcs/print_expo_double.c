/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expo_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 16:53:07 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/06 17:03:07 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		add_expo(char **str, size_t *flags, t_bits *tally, int *pre)
{
	int cou;

	cou = (*tally).mid + (pre > 0 ? *pre : 0);
	if (*flags & BIG)
		(*str)[cou++] = 'E';
	else
		(*str)[cou++] = 'e';
	if ((*tally).expo >= 0)
		(*str)[cou++] = '+';
	else
		((*str)[cou++] = '-') && ((*tally).expo *= -1);
	if ((*tally).expo >= 10 && (*tally).expo < 100)
	{
		(*str)[cou++] = (*tally).expo / 10 + '0';
		(*str)[cou++] = (*tally).expo % 10 + '0';
	}
	else if ((*tally).expo >= 100)
	{
		(*str)[cou++] = (*tally).expo / 100 + '0';
		(*str)[cou++] = ((*tally).expo % 100) / 10 + '0';
		(*str)[cou++] = ((*tally).expo % 100) % 10 + '0';
		(*pre)++;
	}
	else
	{
		(*str)[cou++] = '0';
		(*str)[cou++] = (*tally).expo + '0';
	}
	return (1);
}

int		calc_expo(char **med, int *pre, int sta, int end)
{
	int swim;
	int expo;
	int i;

	expo = 0;
	if ((*med)[1] != '0')
	{
		while ((*med)[expo] != '.' && expo < sta)
			expo++;
		swim = expo + 1;
		while (--swim > 2)
			(*med)[swim] = (*med)[swim - 1];
		*pre > 0 || (*med)[2] != '.' ? (*med)[swim] = '.' : 0;
		expo -= 2;
	}
	else
	{
		while ((*med)[expo] <= '0' && expo < end)
			expo++;
		if ((*med)[expo] < '1' || (*med)[expo] > '9')
			return (0);
		((*med)[1] = (*med)[expo]);
		*pre > 0 ? ((*med)[2] = '.') : 0;
		i = 3;
		swim = expo + 1;
		while (swim < end)
			(*med)[i++] = (*med)[swim++];
		while (i < end)
			(*med)[i++] = '0';
		expo -= 2;
		(*med)[2] != '.' ? expo += 1 : 0;
		expo *= -1;
	}
	return (expo);
}

void			my_roundd(char **med, int *expo, int sta)
{
	int i;

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
			*expo += 4;
			(*med)[i - 1] -= 16;
		}
	}
}

int			compute_nbr(long double nbr)
{
	nbr *= 16;
	nbr -= (int)nbr;
	if ((int)(nbr * 16) % 2)
		return (1);
	else
		return (0);
}

void			transfer(char **med, size_t *flags, int *expo)
{
	if (*flags & BL)
	{
		;
	}
	else
		(*med)[0] >= 2 ? (*med)[0] = 1 && (*expo += 1) : 0;
}

int				puthex(char **med, t_bits *tally, size_t *flags, int *pre)
{
	long double nbr;
	int expo;
	int cou;
	int test;
	int hello;
	int flag;

	expo = 0;
	cou = 0;
	flag = 0;
	nbr = (*tally).nbr.nbr;
	nbr < 0 ? nbr *= -1 : 0;
	if (nbr > (*flags & BL ? 15 : 2))
		while (nbr > ((*flags & BL) ? 16 : 2) && expo++ >= 0)
			nbr /= 2;
	else
		while (nbr != 0 && nbr < ((*flags & BL) ? 8 : 1) && expo-- <= 0)
			nbr *= 2;
	(*med)[cou++] = (int)nbr;
	nbr -= (int)nbr;
	(*med)[cou++] = '.';
	hello = *pre;
	while (nbr && (*flags & POI ? (*pre)-- > 0 : 1))
	{
		flag = 1;
		nbr *= 16;
		(*med)[cou++] = (int)nbr;
		nbr -= (int)nbr;
	}
	transfer(med, flags, &expo);
	if ((int)(nbr * 16) > 8 || ((int)(nbr * 16) == 8 && compute_nbr(nbr)))
		my_roundd(med, &expo, cou);
	int i = -1;
	while (++i < cou)
	{
		if ((*med)[i] == '.')
			continue;
		(*med)[i] < 10 ? (*med)[i] += 48 : ((*med)[i] += (*flags & BIG ? 55 : 87));
	}
	if (*flags & POI)
		hello <= 0 && !(*flags & HAS) ? cou-- : 0;
	else
	{
		(*tally).nbr.nbr == 0 && !(*flags & HAS) ? cou-- : 0;
		(*tally).nbr.nbr != 0 && !flag && expo == 0 && !(*flags & HAS) ? cou-- : 0;
	}
	if (*flags & POI)
		while ((*pre)-- > 0)
			(*med)[cou++] = '0';
	(*med)[cou++] = *flags & BIG ? 'P' : 'p';
	expo >= 0 ? (*med)[cou++] = '+' : ((*med)[cou++] = '-') && (expo *= -1);
	expo < 10 ? ((*med)[cou++] = expo + '0') : 0;
	expo >= 10 && expo < 100 ? ((*med)[cou++] = expo / 10 + '0') && ((*med)[cou++] = expo % 10 + '0') : 0;
	expo >= 100 && expo < 1000 ? ((*med)[cou++] = expo / 100 + '0') && ((*med)[cou++] = (expo % 100) / 10 + '0') && ((*med)[cou++] = expo % 10 + '0') : 0;
	if (expo >= 1000 && expo < 10000)
	{
		(*med)[cou++] = expo / 1000 + '0';
		(*med)[cou++] = (expo % 1000) / 100 + '0';
		(*med)[cou++] = (expo % 100) / 10 + '0';
		(*med)[cou++] = expo % 10 + '0';
	}
 	return (cou);
}

void	print_hexadouble(long double nbr, size_t *flags, int *wid, int *pre)
{
	t_bits tally;
	char *med;
	int i;
	int j;

	j = 0;
	i = 0;
	get_bits(&tally, &nbr, flags, pre);
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
