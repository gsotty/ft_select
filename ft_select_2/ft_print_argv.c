/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 18:05:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/11 15:29:25 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "./ft_select.h"

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
		while (y < buf->max_col && buf->tab_arg[x + tmp_col] != NULL)
		{
			if ((y + 1) < buf->max_col && buf->tab_arg[x
					+ tmp_col + 1] != NULL)
				ft_print_buf(buf, buf->max_len, (x + tmp_col));
			else
				ft_print_buf_last(buf, (x + tmp_col));
			tmp_col = tmp_col + buf->max_lig;
			y++;
		}
		write(1, "\n", 1);
		x++;
	}
}

static void		ft_print_argv_col(int argc, t_buf *buf, struct winsize win)
{

	buf->max_col = 1;
	buf->max_lig = 1;
	while ((buf->max_len * (buf->max_col + 1)) < win.ws_col)
		buf->max_col++;
	while ((buf->max_col * buf->max_lig) <= argc && buf->max_col > 0)
		buf->max_lig++;
	while (((buf->max_col - 1) * buf->max_lig) > argc && buf->max_col > 0)
		buf->max_col--;
	ft_while_print_argv(buf);
}

static void		ft_print_argv_no_col(int argc, t_buf *buf)
{
	int		x;

	x = 0;
	while (buf->tab_arg[x] != NULL)
	{
		if (buf->tab_arg[x + 1] != NULL)
			ft_print_buf(buf, buf->max_len, x);
		else
			ft_print_buf_last(buf, x);
		x++;
	}
	ft_printf("\n");
}

static void		ft_printf_argv_no_lig(int argc, t_buf *buf)
{
	int		x;

	x = 0;
	while (buf->tab_arg[x] != NULL)
	{
		ft_print_buf_last(buf, x);
		write(1, "\n", 1);
		x++;
	}
}

int				ft_print_argv(int argc, t_buf *buf)
{
	int					x;
	struct winsize		win;

	x = 0;
	buf->argc = argc;
	ioctl(0, TIOCGWINSZ, &win);
	buf->max_len = 0;
	while (buf->tab_arg[x] != NULL)
	{
		if (buf->max_len < ft_strlen(buf->tab_arg[x]))
			buf->max_len = ft_strlen(buf->tab_arg[x]);
		x++;
	}
	buf->max_len++;
	if (win.ws_col >= (buf->max_len * argc))
		ft_print_argv_no_col(argc, buf);
	else if (win.ws_col < buf->max_len)
		ft_printf_argv_no_lig(argc, buf);
	else
		ft_print_argv_col(argc, buf, win);
	return (0);
}
