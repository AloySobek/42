/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnikia <cnikia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:52:48 by cnikia            #+#    #+#             */
/*   Updated: 2019/04/29 19:45:42 by cnikia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fillit.h"

int		main(int argc, char **argv)
{
	int		fd;
	int		a;
	t_lst	*tet;
	t_lst	*test;

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit source_file\n");
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	tet = coords(fd);
	test = tet;
	a = 0;
	while (test)
	{
		a++;
		test = test->next;
		if (a > 26)
			fillit_list_exit(7, &tet);
	}
	if (!(ft_fillit(tet, 2)))
		fillit_list_exit(6, &tet);
	fillit_list_exit(10, &tet);
	return (0);
}
