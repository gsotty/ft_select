/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 18:05:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/18 11:41:07 by gsotty           ###   ########.fr       */
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

void	print_sur(t_buf *buf, int pos, int len)
{
	char	*tmp;

	tmp = ft_memalloc(sizeof(char) * (8 + len));
	ft_memcpy(tmp, "\033[7m", 4);
	ft_memcpy(tmp + 4, buf->tab_arg[pos], len);
	ft_memcpy(tmp + 4 + len, "\033[0m", 4);
	write(0, tmp, 8 + len);
	free(tmp);
}

void	print_sou(t_buf *buf, int pos, int len)
{
	char	*tmp;

	tmp = ft_memalloc(sizeof(char) * (8 + len));
	ft_memcpy(tmp, "\033[4m", 4);
	ft_memcpy(tmp + 4, buf->tab_arg[pos], len);
	ft_memcpy(tmp + 4 + len, "\033[0m", 4);
	write(0, tmp, 8 + len);
	free(tmp);
}

void	print_sur_et_sou(t_buf *buf, int pos, int len)
{
	char	*tmp;

	tmp = ft_memalloc(sizeof(char) * (15 + len));
	ft_memcpy(tmp, "\033[37;4;5;7m", 11);
	ft_memcpy(tmp + 11, buf->tab_arg[pos], len);
	ft_memcpy(tmp + 11 + len, "\033[0m", 4);
	write(0, tmp, 15 + len);
	free(tmp);
}

int		ft_print_argv(t_buf *buf)
{
	int		x;
	int		j;
	int		y;
	int		z;
	int		len_write;
	int		len;

	x = 0;
	j = 0;
	y = 0;
	z = 0;
	len = 0;
	len_write = 0;
	check_len_win(buf);
	buf->max_lig = buf->argc;
	while (buf->tab_arg[x] != NULL)
	{
		if (buf->max_len < (len = (int)ft_strlen(buf->tab_arg[x])))
			buf->max_len = len;
		x++;
	}
	len = 0;
	x = 0;
	tputs(tgetstr("cl", NULL), 0, f_putchar);
	z = ((buf->pos - (buf->max_lig * (buf->pos / buf->max_lig)))
						/ buf->lig);
	while (x < buf->lig && buf->tab_arg[j + (buf->lig * z)] != NULL)
	{
		tputs(tgoto(tgetstr("cm", NULL), ((buf->max_len + 1) * (y)), x), 1,
				f_putchar);
		len = ft_strlen(buf->tab_arg[j + (buf->lig * z)]);
		len_write = ((buf->max_len + 1) * y) + len;
		while (len_write > buf->col && len > 0)
		{
			len_write = ((buf->max_len + 1) * y) + len;
			len--;
		}
		if (buf->nbr[j + (buf->lig * z)] == 1 &&
				buf->pos == (j + (buf->lig * z)))
			print_sur_et_sou(buf, (j + (buf->lig * z)), len);
		else if (buf->pos == (j + (buf->lig * z)))
			print_sou(buf, (j + (buf->lig * z)), len);
		else if (buf->nbr[j + (buf->lig * z)] == 1)
			print_sur(buf, (j + (buf->lig * z)), len);
		else
			write(0, buf->tab_arg[j + (buf->lig * z)], len);
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
