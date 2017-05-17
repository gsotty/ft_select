/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 18:05:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/17 15:51:05 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "./ft_select.h"

static void		ft_while_print_argv_no_lig(t_buf *buf)
{
	int		j;
	int		x;
	int		y;
	int		tmp_col;

	x = 0;
	j = ((buf->pos - (buf->max_lig * (buf->pos / buf->max_lig)))
			/ (buf->lig - 1));
	j = ((buf->lig - 1) * j);
	while ((x < ((buf->lig - 1) + j)) && (x < (buf->max_lig)))
	{
		y = 0;
		tmp_col = 0;
		while (y < buf->max_col && ((x + tmp_col) < buf->argc) &&
				buf->tab_arg[x + tmp_col] != NULL)
		{
			if ((y + 1) < buf->max_col && buf->tab_arg[x
					+ tmp_col + 1] != NULL)
				ft_print_buf(buf, buf->max_len, (x + tmp_col));
			else
				ft_print_buf_last(buf, (x + tmp_col));
			tmp_col = tmp_col + buf->max_lig;
			y++;
		}
		write(0, "\n", 1);
		x++;
	}
}

static void		ft_while_print_argv(t_buf *buf)
{
	int		x;
	int		y;
	int		tmp_col;

	x = 0;
	while (x < buf->max_lig)
	{
		y = 0;
		tmp_col = 0;
		while (y < buf->max_col && ((x + tmp_col) < buf->argc) &&
				buf->tab_arg[x + tmp_col] != NULL)
		{
			if ((y + 1) < buf->max_col && buf->tab_arg[x
					+ tmp_col + 1] != NULL)
				ft_print_buf(buf, buf->max_len, (x + tmp_col));
			else
				ft_print_buf_last(buf, (x + tmp_col));
			tmp_col = tmp_col + buf->max_lig;
			y++;
		}
		write(0, "\n", 1);
		x++;
	}
}

static void		ft_print_argv_col(t_buf *buf, struct winsize win)
{
	buf->max_col = 0;
	buf->max_lig = 1;
	while ((buf->max_len * (buf->max_col + 1)) < win.ws_col)
		buf->max_col++;
	while ((buf->max_col * buf->max_lig) < buf->argc && buf->max_col > 0)
		buf->max_lig++;
	while (((buf->max_col - 1) * buf->max_lig) > buf->argc && buf->max_col > 0)
		buf->max_col--;
	if (buf->max_col == 0)
	{
		buf->max_col = 1;
		buf->max_lig = buf->argc;
	}
	if (buf->max_lig < buf->lig)
		ft_while_print_argv(buf);
	else
		ft_while_print_argv_no_lig(buf);
}

int				ft_print_argv(t_buf *buf)
{
	int					x;
	struct winsize		win;

	x = 0;
	ioctl(0, TIOCGWINSZ, &win);
	buf->max_len = 0;
	buf->col = win.ws_col;
	buf->lig = win.ws_row;
	buf->max_col = 0;
	while (buf->tab_arg[x] != NULL)
	{
		if (buf->max_len < (int)ft_strlen(buf->tab_arg[x]))
			buf->max_len = ft_strlen(buf->tab_arg[x]);
		x++;
	}
	buf->max_len++;
	ft_print_argv_col(buf, win);
	return (0);
}
