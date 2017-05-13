/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_buf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 12:25:13 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/13 13:01:51 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

void	ft_print_buf(t_buf *buf, int max_len, int len)
{
	char	*str;

	if (!(str = ft_memalloc(sizeof(char) * ((max_len + 10) * buf->argc))))
		return ;
	if (buf->nbr[len] == 1 && len == buf->pos)
		ft_sprintf(str, "\033[37;4;5;7m%s\033[0m%*c", buf->tab_arg[len],
				(max_len - ft_strlen(buf->tab_arg[len])), ' ');
	else if (len == buf->pos)
		ft_sprintf(str, "\033[7m%s\033[0m%*c", buf->tab_arg[len], (max_len -
				ft_strlen(buf->tab_arg[len])), ' ');
	else if (buf->nbr[len] == 0)
		ft_sprintf(str, "%-*s", max_len, buf->tab_arg[len]);
	else if (buf->nbr[len] == 1)
		ft_sprintf(str, "\033[4m%s\033[0m%*c", buf->tab_arg[len], (max_len -
				ft_strlen(buf->tab_arg[len])), ' ');
	else
		return ;
	write(0, str, ft_strlen(str));
	free(str);
}

void	ft_print_buf_last(t_buf *buf, int len)
{
	char	*str;

	if (!(str = ft_memalloc(sizeof(char) * ((buf->max_len + 10) * buf->argc))))
		return ;
	if (buf->nbr[len] == 1 && len == buf->pos)
		ft_sprintf(str, "\033[37;4;5;7m%s\033[0m", buf->tab_arg[len]);
	else if (len == buf->pos)
		ft_sprintf(str, "\033[7m%s\033[0m", buf->tab_arg[len]);
	else if (buf->nbr[len] == 0)
		ft_sprintf(str, "%s", buf->tab_arg[len]);
	else if (buf->nbr[len] == 1)
		ft_sprintf(str, "\033[4m%s\033[0m", buf->tab_arg[len]);
	else
		return ;
	write(0, str, ft_strlen(str));
	free(str);
}
