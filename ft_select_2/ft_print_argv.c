/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 18:05:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/17 18:05:49 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "./ft_select.h"

void	check_len_win(t_buf *buf)
{
	struct winsize		win;

	ioctl(0, TIOCGWINSZ, &win);
	buf->lig = (win.ws_row - 1);
	buf->col = win.ws_col;
}

int		ft_print_argv(t_buf *buf)
{
	int		x;
	int		j;
	int		y;
	int		len_write;
	int		len;

	x = 0;
	j = 0;
	y = 0;
	len_write = 0;
	len = 0;
	check_len_win(buf);
	buf->max_col = 1;
	buf->max_lig = buf->argc;
	while (buf->tab_arg[x] != NULL)
	{
		if (buf->max_len < (int)ft_strlen(buf->tab_arg[x]))
			buf->max_len = (int)ft_strlen(buf->tab_arg[x]);
		x++;
	}
	x = 0;
	if ((buf->lig * buf->max_col) < buf->max_lig)
		buf->max_col++;
	tputs(tgetstr("cl", NULL), 0, f_putchar);
	while (x < buf->lig && buf->tab_arg[j] != NULL)
	{
		tputs(tgoto(tgetstr("cm", NULL), ((buf->max_len + 1) * y), x), 1,
				f_putchar);
		len = ft_strlen(buf->tab_arg[j]);
		len_write = ((buf->max_len + 1) * y) + len;
		while (len_write > buf->col && len > 0)
		{
			len_write = ((buf->max_len + 1) * y) + len;
			len--;
		}
		write(0, buf->tab_arg[j], len);
		if (x == (buf->lig - 1))
		{
			x = -1;
			y++;
		}
		x++;
		j++;
	}
	return (0);
}
