/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_arithmetic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:10:22 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/28 19:17:11 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
			if (power[n] > 9)
			{
				power[n] -= 10;
				++power[n - 1];
			}
	}
	n = m;
	z = cou;
	while (n >= 0)
		(*med)[z--] += power[n--];
	z = cou + 1;
	while (z--)
	{
		if ((*med)[z] > 9)
		{
			(*med)[z] -= 10;
			++((*med)[z - 1]);
		}
	}
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
			while (power[n] > 9)
			{
				power[n] -= 10;
				++power[n - 1];
			}
	}
	n = m;
	while (n--)
		(*med)[cou + n] += power[n];
	n = m;
	while (n--)
		while ((*med)[cou + n] > 9)
		{
			(*med)[cou + n] -= 10;
			++(*med)[cou + n - 1];
		}
}

void		roundd(char **str, int *pre, int sta, int end)
{
	int flag;
	int n;
	int i;

	n = sta + *pre;
	flag = 0;
	(*str)[n + 1] == '.' ? i = 2 : (i = 1);
	if ((*str)[n + i] >= '5')
	{
		if ((*str)[n + i] == '5')
			while (end > n + i)
				if ((*str)[end--] > '0' && (flag = 1))
					break ;
		if ((*str)[n + i] > '5')
			(*str)[n] += 1;
		else if ((*str)[n + i] == '5')
			(*str)[n] % 2 != 0 || flag ? ((*str)[n] += 1) : 0;
	}
	while ((*str)[n] > '9' && (*str)[n] != '.')
	{
		(*str)[n] -= 10;
		(*str)[n - 1] != '.' ? (*str)[n - 1] += 1 : 0;
		n--;
	}
	(*str)[n] == '.' && n != sta + *pre ? (*str)[--n]++ : 0;
	while (n >= 0 && (*str)[n] > '9')
	{
		(*str)[n] -= 10;
		(*str)[n - 1] += 1;
		(*str)[n - 1] < '0' ? (*str)[n - 1] += '0' : 0;
		n--;
	}
}
