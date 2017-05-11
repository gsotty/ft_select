/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 18:05:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/11 11:57:11 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "./ft_select.h"

static void		ft_while_print_argv(t_buf *buf, int max_len, int max_col,
		int max_lig)
{
	int		x;
	int		y;
	int		tmp_col;

	x = 0;
	while (x < max_lig)
	{
		y = 0;
		tmp_col = 0;
		while (y < max_col && buf->tab[x + tmp_col] != NULL)
		{
			if ((y + 1) < max_col && buf->tab[x + tmp_col + 1] != NULL)
				ft_printf("%-*s", max_len, buf->tab[x + tmp_col]);
			else
				ft_printf("%s", buf->tab[x + tmp_col]);
			tmp_col = tmp_col + max_lig;
			y++;
		}
		write(1, "\n", 1);
		x++;
	}
}

static void		ft_print_argv_col(int argc, t_buf *buf, int max_len,
		struct winsize win)
{
	int		max_lig;
	int		max_col;

	max_col = 0;
	max_lig = 1;
	while ((max_len * (max_col + 1)) < win.ws_col)
		max_col++;
	while ((max_col * max_lig) <= argc && max_col > 0)
		max_lig++;
	while (((max_col - 1) * max_lig) > argc && max_col > 0)
		max_col--;
	ft_while_print_argv(buf, max_len, max_col, max_lig);
}

static void		ft_print_argv_no_col(int argc, t_buf *buf, int max_len)
{
	int		x;

	x = 0;
	while (buf->tab[x] != NULL)
	{
		if (buf->tab[x + 1] != NULL)
			ft_printf("%-*s", max_len, buf->tab[x]);
		else
			ft_printf("%s", buf->tab[x]);
		x++;
	}
	ft_printf("\n");
}

static void		ft_printf_argv_no_lig(int argc, t_buf *buf)
{
	int		x;

	x = 0;
	while (buf->tab[x] != NULL)
	{
		ft_printf("%s\n", buf->tab[x]);
		x++;
	}
}

int				ft_print_argv(int argc, t_buf *buf)
{
	int					x;
	int					max_len;
	struct winsize		win;

	x = 0;
	max_len = 0;
	ioctl(0, TIOCGWINSZ, &win);
	while (buf->tab[x] != NULL)
	{
		if (max_len < ft_strlen(buf->tab[x]))
			max_len = ft_strlen(buf->tab[x]);
		x++;
	}
	max_len++;
	if (win.ws_col >= (max_len * argc))
		ft_print_argv_no_col(argc, buf, max_len);
	else if (win.ws_col < max_len)
		ft_printf_argv_no_lig(argc, buf);
	else
		ft_print_argv_col(argc, buf, max_len, win);
	return (0);
}
