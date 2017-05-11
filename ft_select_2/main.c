/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 18:06:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/11 11:56:38 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

/*
** nbr est un tab de int ou il y a trois possibiliter
** nbr[x] = 0 (rien), nbr[x] = 1(souligner), nbr[x] == 2(souligner est
** surligner)
*/

int		main(int argc, char **argv)
{
	int		x;
	t_buf	buf;

	x = 1;
	if (argc == 1)
		return (0);
	ft_memset(&buf, 0, sizeof(t_buf));
	if (!(buf.tab = ft_memalloc(sizeof(char *) * argc)))
		return (-1);
	if (!(buf.nbr = ft_memalloc(sizeof(int) * argc)))
		return (-1);
	while (argv[x] != NULL)
	{
		buf.tab[x - 1] = ft_strdup(argv[x]);
		x++;
	}
	ft_print_argv(argc - 1, &buf);
	return (0);
}
