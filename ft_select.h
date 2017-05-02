/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 08:55:15 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/02 15:25:10 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

#include <unistd.h>
#include "./libft/libft.h"
#include "./ft_printf/ft_printf.h"

typedef struct		s_lig_and_col
{
	int				argc;
	int				col;
	int				lig;
	int				fin_col;
	int				max_col;
	int				max_lig;
	int				max_len;
	int				*tab_va;
}					t_lig_and_col;

void				print_argv(int argc, char **argv, t_lig_and_col *lig_col,
		int nbr);

#endif
