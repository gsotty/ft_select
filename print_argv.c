/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 08:48:03 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/02 16:24:45 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		print_word(char **argv, int x,
		t_lig_and_col *lig_col, int nbr)
{
	int				verif;
	int				z;
	int				y;
	int				tmp_col;

	y = 0;
	tmp_col = 0;
	while (y < lig_col->max_col)
	{
		z = 0;
		verif = 1;
		while (z < lig_col->argc)
		{
			if (lig_col->tab_va[z] == (x + tmp_col))
			{
				if (nbr == (x + tmp_col))
				{
					if (y + 1 < lig_col->max_col)
						ft_printf("\033[37;4;5;7m%s\033[0m%*c", argv[x + tmp_col],
								lig_col->max_len -
								ft_strlen( argv[x + tmp_col]), ' ');
					else
						ft_printf("\033[37;4;5;7m%s\033[0m", argv[x + tmp_col]);
				}
				else
				{
					if (y + 1 < lig_col->max_col)
						ft_printf("\033[4m%s\033[0m%*c", argv[x + tmp_col],
								lig_col->max_len -
								ft_strlen( argv[x + tmp_col]), ' ');
					else
						ft_printf("\033[4m%s\033[0m", argv[x + tmp_col]);
				}
				verif = 0;
				break ;
			}
			z++;
		}
		if (verif == 1)
		{
			if (nbr == (x + tmp_col))
			{
				if (y + 1 < lig_col->max_col)
					ft_printf("\033[7m%s\033[0m%*c", argv[x + tmp_col],
							lig_col->max_len -
							ft_strlen( argv[x + tmp_col]), ' ');
				else
					ft_printf("\033[7m%s\033[0m", argv[x + tmp_col]);
			}
			else
			{
				if (y + 1 < lig_col->max_col)
					ft_printf("%-*s", lig_col->max_len, argv[x + tmp_col]);
				else
					ft_printf("%s", argv[x + tmp_col]);
			}
		}
		tmp_col = tmp_col + lig_col->max_lig;
		y++;
	}
	write(1, "\n", 1);
}

static void		ft_while_print_argv(char **argv, int x,
		t_lig_and_col *lig_col, int nbr)
{

	if (x <= lig_col->fin_col || lig_col->fin_col == 0)
		print_word(argv, x, lig_col, nbr);
	else
	{
		lig_col->max_col = lig_col->max_col - 1;
		print_word(argv, x, lig_col, nbr);
		lig_col->max_col = lig_col->max_col + 1;
	}
	x++;
}

void			print_argv(int argc, char **argv, t_lig_and_col *lig_col,
		int nbr)
{
	int				x;

	x = 1;
	lig_col->argc = argc;
	if (lig_col->col < lig_col->max_len)
		lig_col->max_col = 1;
	else
		lig_col->max_col = (lig_col->col / lig_col->max_len);
	lig_col->max_lig = ((argc - 1) / lig_col->max_col);
	if ((lig_col->fin_col = ((argc - 1) / lig_col->max_col)) != 0)
		lig_col->max_lig++;
	while (x < lig_col->max_lig + 1)
	{
		ft_while_print_argv(argv, x, lig_col, nbr);
		x++;
	}
}
