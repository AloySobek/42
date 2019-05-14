/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:26:30 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/13 21:19:07 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			print_double(long double nbr, size_t *flags, int *wid, int *pre)
{
	long double	roundd;
	ssize_t	interm;
	char	*result; 
	int		i;

	    (nbr < 0)   ? (nbr *= -1) && (*flags |= NEG) : 0;
	!(*flags & POI) ?          *pre = 6              : 0;
	result   = (char *)malloc(1000);
	interm   = (ssize_t)nbr;
	roundd   = 1;
	i        = 1;
	while ((interm /= 10) && i++ >= 0)
		roundd *= 10;
	interm = (ssize_t)nbr;
	*wid -= *pre > 0 ? *pre + 1 : 0;
	*wid -= i;
	i = 0;
	if (*wid && !(*flags & BIA))
	while ((*wid)-- > 0)
		result[i++] = (*flags << 56) >> 56;
	if (interm == 0)
		result[i++] = '0';
	while (interm)
	{
		result[i++] = (ssize_t)(interm / (ssize_t)roundd) + '0';
		interm %= (ssize_t)roundd;
		roundd /= 10;
	}
	if (*pre)
		result[i++] = '.';
	roundd = 0.5;
	interm = *pre;
	while (interm-- > 0)
		roundd /= 10;
	nbr   -= (ssize_t)nbr;
	nbr   += roundd;
	while ((nbr *= 10) > 0 && (*pre)--)
	{
		result[i++] = (long long)nbr + 48;
		roundd *= 10;
		nbr -= (long long)nbr;
	}
	while ((*pre)-- > 0)
		result[i++] = '0';
	while ((*wid)-- > 0)
		result[i++] = (*flags << 56) >> 56;
	return (write(1, result, i));
}
