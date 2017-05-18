/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:07:40 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/18 15:29:02 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

void	return_bar(t_buf *buf)
{
	int		x;

	x = 0;
	while (x <= buf->argc)
	{
		if (buf->nbr[x] == 1)
		{
			write(1, buf->tab_arg[x], ft_strlen(buf->tab_arg[x]));
			write(1, " ", 1);
		}
		x++;
	}
	write(1, "\n", 1);
	ft_exit(1, buf);
}
