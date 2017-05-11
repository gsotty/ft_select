/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 18:06:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/11 16:13:04 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"
#include <term.h>
#include <stdlib.h>
#include <curses.h>

/*
** nbr est un tab de int ou il y a 4 possibiliter
** nbr[x] == 0 (rien)
** nbr[x] == 1 (surligner)
** nbr[x] == 2 (souligner)
** nbr[x] == 3 (souligner est surligner)
*/

static int			reset_term(void)
{
	struct termios	term;
	char			*name_term;

	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (0);
}

static int			prepare_term(void)
{
	struct termios	term;
	char			*name_term;

	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (0);
}

void			clear_win(void)
{
	char	*res;

	if ((res = tgetstr("cl", NULL)) == NULL)
	{
		if ((res = tgetstr("ve", NULL)) == NULL)
		{
			reset_term();
			exit(0);
		}
		tputs(res, 0, f_putchar);
		reset_term();
		exit(0);
	}
	tputs(res, 0, f_putchar);
}

void			read_ft_select(int argc, t_buf *buf)
{
	int		ret;
	char	*res;
	char	bufer[3];

	clear_win();
	ft_print_argv(argc - 1, buf);
	ft_memset(bufer, 0, 3);
	ret = read(0, bufer, 3);
	ft_printf("%d\n", buf->pos);
	ft_printf("%d, %d, %d\n", bufer[0], bufer[1], bufer[2]);
	if ((bufer[0] == 3 || bufer[0] == 4 || bufer[0] == 27)
			&& bufer[1] == 0 && bufer[2] == 0)
	{
		if ((res = tgetstr("ve", NULL)) == NULL)
		{
			clear_win();
			reset_term();
			exit(0);
		}
		tputs(res, 0, f_putchar);
		clear_win();
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
		clear_win();
		return_bar(buf);
		if ((res = tgetstr("ve", NULL)) == NULL)
		{
			clear_win();
			reset_term();
			exit(0);
		}
		tputs(res, 0, f_putchar);
		reset_term();
		exit(0);
	}
}

int				main(int argc, char **argv)
{
	int		x;
	char	*res;
	t_buf	buf;

	x = 1;
	if (argc == 1)
		return (0);
	prepare_term();
	if ((res = tgetstr("vi", NULL)) == NULL)
		return (-1);
	tputs(res, 0, f_putchar);
	clear_win();
	ft_memset(&buf, 0, sizeof(t_buf));
	if (!(buf.tab_arg = ft_memalloc(sizeof(char *) * argc)))
		return (-1);
	if (!(buf.nbr = ft_memalloc(sizeof(int) * argc)))
		return (-1);
	while (argv[x] != NULL)
	{
		buf.tab_arg[x - 1] = ft_strdup(argv[x]);
		x++;
	}
	ft_print_argv(argc - 1, &buf);
	while (1)
		read_ft_select(argc - 1, &buf);
	if ((res = tgetstr("ve", NULL)) == NULL)
		return (-1);
	tputs(res, 0, f_putchar);
	clear_win();
	reset_term();
	return (0);
}
