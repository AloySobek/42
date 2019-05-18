/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double_g_f.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:22:49 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/18 20:08:34 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_double_g_f(long double nbr, size_t *flags, int *wid, int *pre)
{
	int expo;

	if (nbr >= 10)
	{
		while (nbr >= 10)
		{
			nbr /= 10;
			expo++;
		}
	}
	else if (nbr < 1)
	{
		while (nbr < 1)
		{
			nbr *= 10;
			expo--;
		}
	}
	if (!(*flags & POI))
		*pre = 6;
	if (*flags & POI && *pre == 0)
		*pre = 1;
	if (*pre > (expo >= -4))
	{
		*pre = (expo + 1);
		//hello;
	}
	else
	{
		*pre -= 1;
		//hello;
	}
}