/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expo_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 16:53:07 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/27 20:58:42 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	if (expo >= 10)
	{
		(*str)[cou++] = expo / 10 + '0';
		(*str)[cou++] = expo % 10 + '0';
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

	i = 1;
	expo = 0;
	(*med)[0] > '0' ? i = 0 : 0;
	if ((*med)[i] != '0')
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
		((*med)[i] = (*med)[expo]);
		*pre > 0 ? ((*med)[i + 1] = '.') : 0;
		i += 2;
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
