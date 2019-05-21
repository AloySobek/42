/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:11:36 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/21 21:12:14 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		bi(size_t *flags, int howmuch, int left)
{
	if (left)
	{
		*flags <<= howmuch;
		*flags >>= howmuch;
	}
	else
	{
		*flags >>= howmuch;
		*flags <<= howmuch;
	}
	return (1);
}

int		width_collector(const char **str, va_list *list, size_t *flags,
		int *wid)
{
	int check;

	if (**str == '*')
	{
		*wid = va_arg(*list, int);
		if (*wid < 0)
		{
			*wid *= -1;
			!(*flags & BIA) ? (*flags |= BIA) : 0;
		}
		(*str)++;
	}
	else
	{
		if ((check = ft_atoi(*str)) > 0)
			*wid = check;
		while (**str >= 48 && **str <= 57 && !CONV(**str))
			(*str)++;
	}
	return (1);
}

int		precision_collector(const char **str, va_list *list, size_t *flags,
		int *pre)
{
	*flags |= POI;
	(*str)++;
	if (**str == '*')
	{
		*pre = va_arg(*list, int);
		*pre < 0 ? *flags ^= POI : 0;
		(*str)++;
	}
	else
	{
		*pre = ft_atoi(*str);
		while (**str >= 48 && **str <= 57 && !CONV(**str))
			(*str)++;
	}
	return (1);
}

int		length_modifier_collector(const char **str, size_t *flags)
{
	if (**str == 'h' && *(*str + 1) == 'h')
		(!(*flags & J) && !(*flags & Z) && bi(flags, 8, 1)) ? *flags |= HH : 0;
	else if (**str == 'l' && *(*str + 1) == 'l')
		(!(*flags & J) && !(*flags & Z) && bi(flags, 8, 1)) ? *flags |= LL : 0;
	else if (**str == 'h' && *(*str - 1) != 'h' && *(*str + 1) != 'h')
		(!(*flags & J) && !(*flags & Z) && bi(flags, 8, 1)) ? *flags |= H : 0;
	else if (**str == 'l' && *(*str - 1) != 'l' && *(*str + 1) != 'l')
		(!(*flags & J) && !(*flags & Z) && bi(flags, 8, 1)) ? *flags |= L : 0;
	else if (**str == 'j' && bi(flags, 8, 1))
		*flags |= J;
	else if (**str == 'z' && bi(flags, 8, 1))
		*flags |= Z;
	else if (**str == 't' && bi(flags, 8, 1))
		*flags |= T;
	else if (**str == 'L' && bi(flags, 8, 1))
		*flags |= BL;
	else
		return (0);
	return (1);
}

void	color_chooser(char **str, size_t *flags)
{
	*str += 2;
		
}

void	flags_collector(const char **str, va_list *list, size_t *flags,
		int *wid, int *pre)
{
	while (!CONV(**str) && !(*flags & UND))
	{
		if (**str == '-')
			*flags |= BIA;
		else if (**str == '+')
			*flags |= PLU;
		else if (**str == ' ')
			*flags |= SPA;
		else if (**str == '#')
			*flags |= HAS;
		else if (**str == '0' && ((*(*str - 1) >= 0 && *(*str - 1) < 48) ||
				*(*str - 1) > 57) && (*flags |= FLO))
			*flags |= 48;
		else if (**str == '@' && *(*str + 1) == '{')
			;//color_chooser(str, flags);
		else if (**str == '.' && precision_collector(str, list, flags, pre))
			continue;
		else if (((**str >= 48 && **str <= 57) || **str == '*') &&
				width_collector(str, list, flags, wid))
			continue;
		else if (length_modifier_collector(str, flags))
			;
		else if (**str != 'h' && **str != 'l' && (*flags |= UND) && EJECT(1))
			print_any_char(**str, flags, wid);
		(*str)++;
	}
	if ((*flags & BIA || *flags & POI) && *pre >= 0 && bi(flags, 8, 0))
		*flags |= 32;
	*flags |= (**str) << 16;
}
