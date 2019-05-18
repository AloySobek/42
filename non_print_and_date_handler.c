/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_print_and_date_handler.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 13:49:25 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/18 20:05:07 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	non_printable_handler(va_list *list, size_t *flags, int *wid, int *pre)
{	
	char c;

	c = (char)va_arg(*list, int);
	if (c <= 10)
		;//print_0_10(c, flags, wid, pre);
	else if (c <= 20)
		;//print_10_20(c, flags, wid, pre);
	else if (c <= 31)
		;//print_20_31(c, flags, wid, pre);
}