/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 16:47:08 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/30 20:19:59 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

size_t		ft_strlen(const char *s)
{
	const char *i;

	i = s;
	while (*i)
		i++;
	return (i - s);
}