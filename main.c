/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:31:26 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/11 13:36:06 by gsotty           ###   ########.fr       */
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

char	**creat_arg(int argc, char **argv)
{
	int		x;
	char	**arg;

	x = 1;
	if ((arg = ft_memalloc(sizeof(char *) * argc)) == NULL)
		return (NULL);
	while (argv[x] != NULL)
	{
		arg[x - 1] = ft_strdup(argv[x]);
		x++;
	}
	return (arg);
}

void	free_tab(char **arg)
{
	int	x;

	x = 0;
	while (arg[x] != NULL)
	{
		free(arg[x]);
		x++;
	}
	free(arg);
}

char	**del_arg(int argc, char **arg, int pos)
{
	int		x;
	int		y;
	char	**tmp_arg;

	x = 0;
	y = 0;
	if ((tmp_arg = ft_memalloc(sizeof(char *) * argc)) == NULL)
		return (NULL);
	while (arg[x] != NULL)
	{
		if (x != pos)
		{
			tmp_arg[y] = ft_strdup(arg[x]);
			y++;
		}
		x++;
	}
	free_tab(arg);
	if ((arg = ft_memalloc(sizeof(char *) * argc - 1)) == NULL)
		return (NULL);
	x = 0;
	while (tmp_arg[x] != NULL)
	{
		arg[x] = ft_strdup(tmp_arg[x]);
		x++;
	}
	return (arg);
}

int		main(int argc, char **argv, char **env)
{
	char			**arg;
	int				ret;
	int				cont;
	char			buf[3];
	char			buf_term[MAX_CANON];
	char			*test;
	char			*name_term;
	struct termios	term;
	int				j;
	int				x;
	int				z;
	int				max_len;
	int				colon;
	int				ligne;
	char			*res;
	char			*clstr;
	t_lig_and_col	lig_col;
	int				pos;

	pos = 0;
	x = 0;
	cont = 0;
	z = 0;
	arg = creat_arg(argc, argv);
	ft_memset(&lig_col, '\0', sizeof(t_lig_and_col));
	lig_col.argc = (argc - 1);
	if ((lig_col.tab_va = ft_memalloc(sizeof(int) * lig_col.argc)) == NULL)
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
	while (arg[x] != NULL)
	{
		if (lig_col.max_len < ft_strlen(arg[x]))
			lig_col.max_len = ft_strlen(arg[x]);
		x++;
	}
	lig_col.max_len++;
	if ((res = tgetstr("vi", NULL)) == NULL)
		return (-1);
	tputs(res, 0, f_putchar);
	if ((res = tgetstr("cl", NULL)) == NULL)
		return (-1);
	tputs(res, 0, f_putchar);
	print_argv(arg, &lig_col, 0);
	if ((res = tgetstr("ho", NULL)) == NULL)
		return (-1);
	tputs(res, 0, f_putchar);

	colon = 0;
	ligne = 0;
	while (1)
	{
		taille_win(&lig_col);
		x = 0;
		while (arg[x] != NULL)
		{
			if (lig_col.max_len < ft_strlen(arg[x]))
				lig_col.max_len = ft_strlen(arg[x]);
			x++;
		}
		if ((res = tgetstr("cl", NULL)) == NULL)
			return (-1);
		tputs(res, 0, f_putchar);
		print_argv(arg, &lig_col, pos);
		ft_memset(buf, '\0', 3);
		ret = read(0, buf, 3);
		ft_printf("%d, %d, %d\n", buf[0], buf[1], buf[2]);
		if (buf[0] == 4 || (buf[0] == 27 && buf[1] == 0 && buf[2] == 0))
		{
			if ((res = tgetstr("ve", NULL)) == NULL)
				return (-1);
			tputs(res, 0, f_putchar);
			if ((res = tgetstr("cl", NULL)) == NULL)
				return (-1);
			tputs(res, 0, f_putchar);
			if ((res = tgetstr("ve", NULL)) == NULL)
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
					if (pos > 0)
					{
						print_argv(arg, &lig_col, pos - 1);
						pos--;
					}
					else
					{
						pos = lig_col.argc - 1;
						print_argv(arg, &lig_col, pos);
					}
				}
				if (buf[2] == 'B')
				{
					if ((res = tgetstr("cl", NULL)) == NULL)
						return (-1);
					tputs(res, 0, f_putchar);
					if (pos < (lig_col.argc - 1))
					{
						print_argv(arg, &lig_col, pos + 1);
						pos++;
					}
					else
					{
						pos = 0;
						print_argv(arg, &lig_col, pos);
					}
				}
				if (buf[2] == 'C')
				{
					if (pos < (lig_col.argc - lig_col.max_lig))
					{
						if ((res = tgetstr("cl", NULL)) == NULL)
							return (-1);
						tputs(res, 0, f_putchar);
						print_argv(arg, &lig_col, pos + lig_col.max_lig);
						pos = pos + lig_col.max_lig;
					}
				}
				if (buf[2] == 'D')
				{
					if (pos > (lig_col.max_lig - 1))
					{
						if ((res = tgetstr("cl", NULL)) == NULL)
							return (-1);
						tputs(res, 0, f_putchar);
						print_argv(arg, &lig_col, pos - lig_col.max_lig);
						pos = pos - lig_col.max_lig;
					}
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
			if (lig_col.tab_va[pos] == 1)
				lig_col.tab_va[pos] = 0;
			else
				lig_col.tab_va[pos] = 1;
			if (pos < (lig_col.argc - 1))
			{
				print_argv(arg, &lig_col, pos + 1);
				pos++;
			}
			else
			{
				pos = 0;
				print_argv(arg, &lig_col, pos);
			}
		}
		else if (buf[0] == 10 && buf[1] == 0 && buf[2] == 0)
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
			j = 0;
			while (j < lig_col.argc)
			{
				if (lig_col.tab_va[j] == 1)
				{
					write(0, arg[j], ft_strlen(arg[j]));
					write(0, " ", 1);
				}
				j++;
			}
			write(0, "\n", 1);
			return (0);
		}
		else if (buf[0] == 127 && buf[1] == 0 && buf[2] == 0)
		{
			arg = del_arg(lig_col.argc, arg, pos);
			lig_col.argc -= 1;
			if ((res = tgetstr("cl", NULL)) == NULL)
				return (-1);
			tputs(res, 0, f_putchar);
			print_argv(arg, &lig_col, pos);
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
