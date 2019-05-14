/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_any_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 13:25:24 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/13 17:49:30 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			unisize(const wchar_t *s)
{
	int		size;

	size = 0;
	while (*s)
	{
		if (*s <= 0x7F)
			size++;
		else if (*s <= 0x7FF)
			size += 2;
		else if (*s <= 0xFFFF)
			size += 3;
		else
			size += 4;
		s++;
	}
	return (size);
}

int			unistrlen(const wchar_t *s)
{
	int		size;

	size = 0;
	while (*s++)
		size++;
	return (size);
}

int			print_any_string(wchar_t *s, size_t *flags, int *wid, int *pre)
{
	char	*str;
	int		i;

	if (!s)
		s = L"(null)";
	*wid -= (((unistrlen(s) > *pre && *flags & POI) ? (*pre) : unistrlen(s)));
	if (!(str = (char *)malloc((*wid > 0 ? *wid : 0) + (unisize(s) > *pre &&
		*flags & POI ? *pre : unisize(s)))))
		return (0);
	i = 0;
	if (!(*flags & BIA))
		while ((*wid)-- > 0)
			str[i++] = (*flags << 56) >> 56;
	if (*flags & POI)
		while (*s && (*pre)-- > 0)
			*flags & UNI && *s > 127 ? uni(*s++, &str, &i) : (str[i++] = *s++);
	else
		while (*s)
			*flags & UNI && *s > 127 ? uni(*s++, &str, &i) : (str[i++] = *s++);
	while ((*wid)-- > 0)
		str[i++] = (*flags << 56) >> 56;
	write(1, str, i);
	free(str);
	return (i);
}
