/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ft_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 15:55:40 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/18 12:56:46 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

void		read_ft_select(t_buf *buf)
{
	char				*res;
	char				bufer[3];
	struct sigaction	act;
	struct winsize		win;

	ft_memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &signal_tstp;
	act.sa_flags = SA_SIGINFO | SA_NODEFER;
	sigaction(SIGTSTP, &act, NULL);
	ft_memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &signal_cont;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGCONT, &act, NULL);
	if (buf->argc == 0)
	{
		if ((res = tgetstr("ve", NULL)) == NULL)
		{
			tputs(tgetstr("cl", NULL), 0, f_putchar);
			reset_term();
			exit(0);
		}
		tputs(res, 0, f_putchar);
		tputs(tgetstr("cl", NULL), 0, f_putchar);
		reset_term();
		exit(0);
	}
	tputs(tgetstr("cl", NULL), 0, f_putchar);
	ft_print_argv(buf);
	ft_memset(bufer, 0, 3);
	ft_memset(&win, '\0', sizeof(win));
	ft_memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &signal_int;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGWINCH, &act, NULL);
	if (g_sig == SIGWINCH)
	{
		g_sig = 0;
		ioctl(0, TIOCGWINSZ, &win);
		if (!(buf->col == win.ws_col && buf->lig == win.ws_row))
		{
			tputs(tgetstr("cl", NULL), 0, f_putchar);
			ft_print_argv(buf);
			tputs(tgetstr("cl", NULL), 0, f_putchar);
			ft_print_argv(buf);
		}
	}
	read(0, bufer, 3);
	if (((bufer[0] == 3 || bufer[0] == 4 || bufer[0] == 26 || bufer[0] == 27)
				&& bufer[1] == 0 && bufer[2] == 0) || g_sig == SIGINT)
	{
		g_sig = 0;
		if ((res = tgetstr("ve", NULL)) == NULL)
		{
			tputs(tgetstr("cl", NULL), 0, f_putchar);
			reset_term();
			exit(0);
		}
		tputs(res, 0, f_putchar);
		tputs(tgetstr("cl", NULL), 0, f_putchar);
		reset_term();
		exit(0);
	}
	else if (bufer[0] == 27)
	{
		if (bufer[1] == 91)
			fleche_directionnelle(bufer, buf);
	}
	else if (bufer[0] == 32 && bufer[1] == 0 && bufer[2] == 0)
		space_bar(buf);
	else if (bufer[0] == 10 && bufer[1] == 0 && bufer[2] == 0)
	{
		tputs(tgetstr("cl", NULL), 0, f_putchar);
		return_bar(buf);
		if ((res = tgetstr("ve", NULL)) == NULL)
		{
			tputs(tgetstr("cl", NULL), 0, f_putchar);
			reset_term();
			exit(0);
		}
		tputs(res, 0, f_putchar);
		reset_term();
		exit(0);
	}
	else if ((bufer[0] == 127 || bufer[0] == 126) && bufer[1] == 0 &&
			bufer[2] == 0)
		delete_bar(buf);
}
