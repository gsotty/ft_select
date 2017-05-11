/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 08:55:15 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/11 11:57:09 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <unistd.h>
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"

typedef struct		s_buf
{
	int		*nbr;
	char	**tab;
}					t_buf;

int		ft_print_argv(int argc, t_buf *buf);

#endif
