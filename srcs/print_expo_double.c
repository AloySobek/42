/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expo_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 16:53:07 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/29 20:44:48 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		add_expo(char **str, size_t *flags, int expo, int cou)
{
	if (*flags & BIG)
		(*str)[cou++] = 'E';
	else
		(*str)[cou++] = 'e';
	if (expo >= 0)
		(*str)[cou++] = '+';
	else
		((*str)[cou++] = '-') && (expo *= -1);
	if (expo >= 10 && expo < 100)
	{
		(*str)[cou++] = expo / 10 + '0';
		(*str)[cou++] = expo % 10 + '0';
	}
	else if (expo >= 100)
	{
		(*str)[cou++] = expo / 100 + '0';
		(*str)[cou++] = (expo % 100) / 10 + '0';
		(*str)[cou++] = (expo % 100) % 10 + '0';
	}
	else
	{
		(*str)[cou++] = '0';
		(*str)[cou++] = expo + '0';
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
		*pre -= expo;
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

void			round_hex(char **med, int sta, int end, int *pre)
{
	return ;
}

int				puthex(char **med, t_bits *tally, size_t *flags, int *pre)
{
	long double nbr;
	int expo;
	int cou;

	expo = 0;
	cou = 0;
	nbr = (*tally).nbr.nbr;
	//if (nbr >= (*flags & BL ? 8 : 2))
	//	while (nbr >= ((*flags & BL) ? 15 : 2) && expo++ >= 0)
	//		nbr /= 2;
	//else
	//	while (nbr < ((*flags & BL) ? 8 : 1) && expo-- <= 0)
	//		nbr *= 2;
	(*med)[cou++] = (int)nbr > 9 ? (int)nbr + 87 : (int)nbr + 48;
	nbr -= (int)nbr;
	if ((*flags & POI))
		*pre > 0 || (*flags & HAS) ? (*med)[cou++] = '.' : 0;
	else
		(*med)[cou++] = '.';
	//while (nbr && (*flags & POI ? (*pre)-- > 0 : 1))
	{
	//	nbr *= 16;
	//	(*med)[cou++] = (int)nbr + ((int)nbr > 9 ? 87 : 48);
	//	nbr -= (int)nbr;
	}
	//if (*flags & POI)
	//	while ((*pre)-- > 0)
	//		(*med)[cou++] = '0';
	(*med)[cou++] = 'p';
	expo >= 0 ? (*med)[cou++] = '+' : ((*med)[cou++] = '-') && (expo *= -1);
	expo < 10 ? ((*med)[cou++] = expo + '0') : ((*med)[cou++] = expo / 10 + '0') && ((*med)[cou++ ] = expo % 10 + '0');
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
