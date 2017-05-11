/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:07:40 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/11 16:16:15 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

void	return_bar(t_buf *buf)
{
	int		x;

	x = 0;
	while (x < buf->argc)
	{
		if (buf->nbr[x] == 1 && buf->tab_arg[x + 1] != NULL)
			ft_printf("%s ", buf->tab_arg[x]);
		else if (buf->nbr[x] == 1)
			ft_printf("%s", buf->tab_arg[x]);
		x++;
	}
	write(1, "\n", 1);
}
