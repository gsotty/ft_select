/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_buf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 12:25:13 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/11 16:04:01 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

void	ft_print_buf(t_buf *buf, int max_len, int len)
{
	if (buf->nbr[len] == 1 && len == buf->pos)
		ft_printf("\033[37;4;5;7m%s\033[0m%*c", buf->tab_arg[len], (max_len -
				ft_strlen(buf->tab_arg[len])), ' ');
	else if (len == buf->pos)
		ft_printf("\033[7m%s\033[0m%*c", buf->tab_arg[len], (max_len -
				ft_strlen(buf->tab_arg[len])), ' ');
	else if (buf->nbr[len] == 0)
		ft_printf("%-*s", max_len, buf->tab_arg[len]);
	else if (buf->nbr[len] == 1)
		ft_printf("\033[4m%s\033[0m%*c", buf->tab_arg[len], (max_len -
				ft_strlen(buf->tab_arg[len])), ' ');
	else
		return ;
}

void	ft_print_buf_last(t_buf *buf, int len)
{
	if (buf->nbr[len] == 1 && len == buf->pos)
		ft_printf("\033[37;4;5;7m%s\033[0m", buf->tab_arg[len]);
	else if (len == buf->pos)
		ft_printf("\033[7m%s\033[0m", buf->tab_arg[len]);
	else if (buf->nbr[len] == 0)
		ft_printf("%s", buf->tab_arg[len]);
	else if (buf->nbr[len] == 1)
		ft_printf("\033[4m%s\033[0m", buf->tab_arg[len]);
	else
		return ;
}
