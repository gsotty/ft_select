/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 18:06:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/17 15:09:27 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

static int		struc_buf(t_buf *buf, int argc, char **argv)
{
	int		x;

	x = 1;
	if (!(buf->tab_arg = ft_memalloc(sizeof(char *) * argc)))
		return (-1);
	if (!(buf->nbr = ft_memalloc(sizeof(int) * argc)))
		return (-1);
	buf->argc = argc - 1;
	while (argv[x] != NULL)
	{
		buf->tab_arg[x - 1] = ft_strdup(argv[x]);
		x++;
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_buf	buf;

	if (argc == 1)
		return (0);
	prepare_term();
//	tputs(tgetstr("vi", NULL), 0, f_putchar);
	tputs(tgetstr("cl", NULL), 0, f_putchar);
	ft_memset(&buf, 0, sizeof(t_buf));
	if ((struc_buf(&buf, argc, argv)) == -1)
		return (-1);
	while (1)
		read_ft_select(&buf);
//	tputs(tgetstr("ve", NULL), 0, f_putchar);
	tputs(tgetstr("cl", NULL), 0, f_putchar);
	reset_term();
	return (0);
}
