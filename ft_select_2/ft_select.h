/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 08:55:15 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/15 16:43:04 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <unistd.h>
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include <term.h>
# include <stdlib.h>
# include <curses.h>
# include <signal.h>
# include <sys/ioctl.h>

typedef struct		s_buf
{
	int		pos;
	int		argc;
	int		col;
	int		lig;
	int		max_len;
	int		max_lig;
	int		max_col;
	int		*nbr;
	char	**tab_arg;
}					t_buf;

void				read_ft_select(t_buf *buf);
void				signal_int(int x, siginfo_t *siginfo, void *context);
int					reset_term(void);
int					prepare_term(void);
void				signal_tstp(int x);
void				signal_cont(int x);
int					singletons(int x);
int					f_putchar(int c);
void				delete_bar(t_buf *buf);
void				return_bar(t_buf *buf);
void				space_bar(t_buf *buf);
void				fleche_directionnelle(char *bufer, t_buf *buf);
void				ft_print_buf(t_buf *buf, int max_len, int len);
void				ft_print_buf_last(t_buf *buf, int len);
int					ft_print_argv(t_buf *buf);

#endif
