/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_arithmetic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:10:22 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/01 19:58:10 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		add_power(char **med, int pwr, int cou)
{
	char	power[pwr / 2 + 2];
	int		n;
	int		m;
	int		z;

	m = pwr / 2;
	ft_bzero(power, m + 2);
	power[m] = 1;
	while (pwr-- && (n = m + 1))
	{
		while (n--)
			power[n] *= 2;
		n = m + 1;
		while (n--)
			power[n] > 9 ? (power[n] -= 10) >= 0 && ++power[n - 1] : 0;
	}
	n = m;
	z = cou;
	while (n >= 0)
		(*med)[z--] += power[n--];
	z = cou + 1;
	while (z--)
		(*med)[z] > 9 ? ((*med)[z] -= 10) >= 0 && ++((*med)[z - 1]) : 0;
}

void		add_power_neg(char **med, int pwr, int cou)
{
	char	power[-pwr + 2];
	int		n;
	int		m;

	pwr *= -1;
	m = pwr;
	ft_bzero(power, m + 2);
	power[m - 1] = 1;
	while (pwr-- && (n = m))
	{
		while (n--)
			power[n] *= 5;
		n = m;
		while (n--)
			while (power[n] > 9 && (power[n] -= 10) >= 0)
				++power[n - 1];
	}
	n = m;
	while (n--)
		(*med)[cou + n] += power[n];
	while (m--)
		while ((*med)[cou + m] > 9 && ((*med)[cou + m] -= 10) >= 0)
			++(*med)[cou + m - 1];
}

void		roundd(char **str, int *pre, int sta, int end)
{
	int flag;
	int n;

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
				(*str)[n]  % 2 != 0 || flag ? ++(*str)[n] : 0;
	}
	while ((*str)[n + 1] > '9' && (*str)[n + 1] != '.' && ((*str)[n--] -= 10) >= 0)
		(*str)[n] != '.' ? (*str)[n] += 1 : 0;
	(*str)[n] == '.' && n != sta + *pre ? (*str)[--n]++ : 0;
	while (n >= 0 && (*str)[n] > '9' && ((*str)[n--] -= 10) >= 0 && ++(*str)[n])
		(*str)[n] < '0' ? (*str)[n] += '0' : 0;
	j = 0;
	while (++j < 20)
		printf("%c", (*str)[j]);
}
