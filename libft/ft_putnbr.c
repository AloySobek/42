/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 18:19:13 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/05 18:23:17 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nbr)
{
	int	check[15];
	int count;
	int minus;

	(nbr < 0) ? (minus = -1) : (minus = 1);
	count = 0;
	while (nbr != 0)
	{
		check[count++] = (nbr % 10) * minus + '0';
		nbr /= 10;
	}
	if (!minus)
		check[count++] = '-';
	while (count-- >= 0)
		ft_putchar(check[count]);
}