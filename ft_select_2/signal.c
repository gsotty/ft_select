/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:00:52 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/17 13:29:30 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

void	signal_int(int x, siginfo_t *siginfo, void *context)
{
	if (siginfo)
	{}
	if (context)
	{}
	singletons(x);
}

void	signal_tstp(int x, siginfo_t *siginfo, void *context)
{
	char	*res;

	if (siginfo)
	{}
	if (context)
	{}
	if ((res = tgetstr("ve", NULL)) == NULL)
	{
		tputs(tgetstr("cl", NULL), 0, f_putchar);
		reset_term();
		exit(0);
	}
	tputs(res, 0, f_putchar);
	tputs(tgetstr("cl", NULL), 0, f_putchar);
	reset_term();
	signal(x, SIG_DFL);
	ioctl(0, TIOCSTI, "\032");
}

void	signal_cont(int x)
{
	char	*res;

	if (x)
	{}
	prepare_term();
	if ((res = tgetstr("vi", NULL)) == NULL)
		return ;
	tputs(res, 0, f_putchar);
	ioctl(0, TIOCSTI, "");
	tputs(tgetstr("cl", NULL), 0, f_putchar);
}