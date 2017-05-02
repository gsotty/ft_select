/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:31:26 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/02 16:59:52 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>

int		taille_win(t_lig_and_col *lig_col)
{
	struct winsize		win;

	ioctl(0, TIOCGWINSZ, &win);
	lig_col->col = win.ws_col;
	lig_col->lig = win.ws_row;
	return (0);
}

int		f_putchar(int c)
{
	return (write(1, &c, 1));
}

int		main(int argc, char **argv, char **env)
{
	int				ret;
	int				cont;
	char			buf[3];
	char			buf_term[MAX_CANON];
	char			*test;
	char			*name_term;
	struct termios	term;
	int				x;
	int				z;
	int				max_len;
	int				colon;
	int				ligne;
	char			*res;
	char			*clstr;
	t_lig_and_col	lig_col;
	int				pos;

	pos = 1;
	x = 0;
	cont = 0;
	z = 0;
	ft_memset(&lig_col, '\0', sizeof(t_lig_and_col));
	if ((lig_col.tab_va = ft_memalloc(sizeof(int) * argc)) == NULL)
		return (-1);
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
	ft_memset(buf, '\0', 3);
	taille_win(&lig_col);
	ft_memset(buf_term, '\0', MAX_CANON);
	while (argv[x] != NULL)
	{
		if (lig_col.max_len < ft_strlen(argv[x]))
			lig_col.max_len = ft_strlen(argv[x]);
		x++;
	}
	lig_col.max_len++;
	if ((res = tgetstr("vi", NULL)) == NULL)
		return (-1);
	tputs(res, 0, f_putchar);
	if ((res = tgetstr("cl", NULL)) == NULL)
		return (-1);
	tputs(res, 0, f_putchar);
	print_argv(argc, argv, &lig_col, 1);
	if ((res = tgetstr("ho", NULL)) == NULL)
		return (-1);
	tputs(res, 0, f_putchar);
//	if (tcgetattr(0, &term) == -1)
//		return (-1);
//	term.c_lflag = (ICANON | ECHO);
//	if (tcsetattr(0, TCSADRAIN, &term) == -1)
//		return (-1);
//	exit(0);


	colon = 0;
	ligne = 0;
	while (1)
	{
		taille_win(&lig_col);
		if ((res = tgetstr("cl", NULL)) == NULL)
			return (-1);
		tputs(res, 0, f_putchar);
		print_argv(argc, argv, &lig_col, pos);
		ft_memset(buf, '\0', 3);
		ret = read(0, buf, 3);
	//	ft_printf("%d, %d, %d\n", buf[0], buf[1], buf[2]);
		if (buf[0] == 4 || (buf[0] == 27 && buf[1] == 0 && buf[2] == 0))
		{
			if ((res = tgetstr("ve", NULL)) == NULL)
				return (-1);
			tputs(res, 0, f_putchar);
			if ((res = tgetstr("cl", NULL)) == NULL)
				return (-1);
			tputs(res, 0, f_putchar);
			if (tcgetattr(0, &term) == -1)
				return (-1);
			term.c_lflag = (ICANON | ECHO);
			if (tcsetattr(0, TCSADRAIN, &term) == -1)
				return (-1);
			exit(0);
		}
		else if (buf[0] == 27)
		{
			if (buf[1] == 91)
			{
				if (buf[2] == 'A')
				{
					if ((res = tgetstr("cl", NULL)) == NULL)
						return (-1);
					tputs(res, 0, f_putchar);
					if (pos > 1)
					{
						print_argv(argc, argv, &lig_col, pos - 1);
						pos--;
						ligne--;
					}
					else
					{
						pos = (argc - 1);
						print_argv(argc, argv, &lig_col, pos);
					}
				}
				if (buf[2] == 'B')
				{
					if ((res = tgetstr("cl", NULL)) == NULL)
						return (-1);
					tputs(res, 0, f_putchar);
					if (pos < (argc - 1))
					{
						print_argv(argc, argv, &lig_col, pos + 1);
						pos++;
						ligne++;
					}
					else
					{
						pos = 1;
						print_argv(argc, argv, &lig_col, pos);
					}
				}
				if (buf[2] == 'C')
				{
					if (pos < ((argc) - lig_col.max_lig))
					{
						if ((res = tgetstr("cl", NULL)) == NULL)
							return (-1);
						tputs(res, 0, f_putchar);
						print_argv(argc, argv, &lig_col,
								pos + lig_col.max_lig);
					//	if ((res = tgetstr("cm", NULL)) == NULL)
					//		return (-1);
					//	tputs(tgoto(res, colon + 1, ligne), 0, f_putchar);
						pos = pos + lig_col.max_lig;
						colon++;
					}
				//	else
				//	{
				//		if ((res = tgetstr("cm", NULL)) == NULL)
				//			return (-1);
				//		colon = 0;
				//		tputs(tgoto(res, colon, ligne + 1), 0, f_putchar);
				//		ligne++;
				//	}
				}
				if (buf[2] == 'D')
				{
					if (pos > lig_col.max_lig)
					{
						if ((res = tgetstr("cl", NULL)) == NULL)
							return (-1);
						tputs(res, 0, f_putchar);
						print_argv(argc, argv, &lig_col,
								pos - lig_col.max_lig);
					//	if ((res = tgetstr("cm", NULL)) == NULL)
					//		return (-1);
					//	tputs(tgoto(res, colon - 1, ligne), 0, f_putchar);
						pos = pos - lig_col.max_lig;
						colon--;
					}
				//	else
				//	{
				//		if ((res = tgetstr("cm", NULL)) == NULL)
				//			return (-1);
				//		colon = col;
				//		tputs(tgoto(res, colon, ligne - 1), 0, f_putchar);
				//		ligne--;
				//	}
				}
			}
		}
		else if (buf[0] == 12 && buf[1] == 0 && buf[2] == 0)
		{
			if ((res = tgetstr("cl", NULL)) == NULL)
				return (-1);
			tputs(res, 0, f_putchar);
		}
		else if (buf[0] == 32 && buf[1] == 0 && buf[2] == 0)
		{
			if ((res = tgetstr("cl", NULL)) == NULL)
				return (-1);
			tputs(res, 0, f_putchar);
			if (lig_col.tab_va[pos] == pos)
				lig_col.tab_va[pos] = 0;
			else
				lig_col.tab_va[pos] = pos;
			if (pos < (argc - 1))
			{
				print_argv(argc, argv, &lig_col, pos + 1);
				pos++;
				ligne++;
			}
			else
			{
				pos = 1;
				print_argv(argc, argv, &lig_col, pos);
			}
		}
		else if (buf[0] == 127 && buf[1] == 0 && buf[2] == 0)
		{
			if (colon != 0)
			{
				if ((res = tgetstr("cm", NULL)) == NULL)
					return (-1);
				tputs(tgoto(res, colon - 1, ligne), 0, f_putchar);
				colon--;
				if ((res = tgetstr("dc", NULL)) == NULL)
					return (-1);
				tputs(res, 0, f_putchar);
			}
		}
		else if (buf[0] == 126 && buf[1] == 0 && buf[2] == 0)
		{
			if ((res = tgetstr("dc", NULL)) == NULL)
				return (-1);
			tputs(res, 0, f_putchar);
		}
		else if (buf[1] == 0 && buf[2] == 0)
		{
			if ((res = tgetstr("im", NULL)) == NULL)
				return (-1);
			tputs(tgoto(res, colon - 1, ligne), 0, f_putchar);
			ft_printf("%c", buf[0]);
			colon++;
			if ((res = tgetstr("ei", NULL)) == NULL)
				return (-1);
			tputs(tgoto(res, colon - 1, ligne), 0, f_putchar);
		}
	}
	ft_printf("%s\n", buf_term);
	if ((res = tgetstr("ve", NULL)) == NULL)
		return (-1);
	tputs(res, 0, f_putchar);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (0);
}
