/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_any_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:33:25 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/13 16:03:20 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			print_any_char(wchar_t c, size_t *flags, int *wid)
{
	char	*str;
	int		i;

	str = (char *)malloc(*wid > 0 ? *wid : 1 + 5);
	i = 0;
	(*wid)--;
	if (!(*flags & BIA))
		while ((*wid)-- > 0)
			str[i++] = (*flags << 56) >> 56;
	*flags & UNI && c > 127 ? uni(c, &str, &i) : (str[i++] = c);
	while ((*wid)-- > 0)
		str[i++] = (*flags << 56) >> 56;
	write(1, str, i);
	free(str);
	return (i);
}
