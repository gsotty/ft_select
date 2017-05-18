/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ft_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 15:55:40 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/18 16:06:26 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

static void		ft_signal(void)
{
	struct sigaction	act;

	ft_memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &signal_tstp;
	act.sa_flags = SA_SIGINFO | SA_NODEFER;
	sigaction(SIGTSTP, &act, NULL);
	ft_memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &signal_cont;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGCONT, &act, NULL);
	ft_memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &signal_int;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);
	ft_memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &signal_int;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGWINCH, &act, NULL);
}

static void		ft_sigwinch(t_buf *buf)
{
	struct winsize		win;

	g_sig = 0;
	ft_memset(&win, '\0', sizeof(win));
	ioctl(0, TIOCGWINSZ, &win);
	if (!(buf->col == win.ws_col && buf->lig == win.ws_row))
		ft_print_argv(buf);
}

void			read_ft_select(t_buf *buf)
{
	char				buffer[3];

	ft_signal();
	if (buf->argc == 0)
		ft_exit(-1, buf);
	ft_print_argv(buf);
	if (g_sig == SIGWINCH)
		ft_sigwinch(buf);
	ft_memset(buffer, 0, 3);
	read(0, buffer, 3);
	if (((buffer[0] == 3 || buffer[0] == 4 || buffer[0] == 26 ||
					buffer[0] == 27) && buffer[1] == 0 && buffer[2] == 0)
			|| g_sig == SIGINT)
		ft_exit(1, buf);
	else if (buffer[0] == 27)
		fleche_directionnelle(buffer, buf);
	else if (buffer[0] == 32 && buffer[1] == 0 && buffer[2] == 0)
		space_bar(buf);
	else if (buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0)
		return_bar(buf);
	else if ((buffer[0] == 127 || buffer[0] == 126) && buffer[1] == 0 &&
			buffer[2] == 0)
		delete_bar(buf);
}
