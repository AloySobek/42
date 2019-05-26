/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexadouble.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 13:25:42 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/26 15:39:42 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_hexadouble(long double nbr, size_t *flags, int *wid, int *pre)
{
	t_bits tally;
	char *med;
	int j;
	int i;

	get_bits(&tally, &nbr, flags, pre);
	!(*flags & (INF | NAN)) ? med = (char *)malloc(tally.size * 2) : 0;
	!(*flags & (INF | NAN)) ? ft_bzero(med, tally.size) : 0;
	for (int i = 0; i < sizeof(long double); ++i)
		;//printf("%x", c.bytes[i]);
}