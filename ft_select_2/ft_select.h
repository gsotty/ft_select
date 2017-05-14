/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 08:55:15 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/14 13:04:13 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <unistd.h>
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"

int					sig;

typedef struct		s_buf
{
	int		*nbr;
	int		pos;
	int		argc;
	int		col;
	int		lig;
	int		max_len;
	int		max_lig;
	int		max_col;
	char	**tab_arg;
}					t_buf;

int					f_putchar(int c);
void				clear_win(void);
void				delete_bar(t_buf *buf);
void				return_bar(t_buf *buf);
void				space_bar(t_buf *buf);
void				fleche_directionnelle(char *bufer, t_buf *buf);
void				ft_print_buf(t_buf *buf, int max_len, int len);
void				ft_print_buf_last(t_buf *buf, int len);
int					ft_print_argv(t_buf *buf);

#endif
