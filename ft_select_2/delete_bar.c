/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 11:47:45 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/13 13:17:10 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

void	delete_bar(t_buf *buf)
{
	int		x;
	int		y;
	int		*tmp_nbr;
	char	**tmp_tab;

	x = 0;
	y = 0;
	if (!(tmp_tab = ft_memalloc(sizeof(char *) * buf->argc)))
		return ;
	ft_memset(tmp_tab, 0, sizeof(char *) * buf->argc);
	if (!(tmp_nbr = ft_memalloc(sizeof(int) * buf->argc)))
		return ;
	ft_memset(tmp_nbr, 0, sizeof(int) * buf->argc);
	while (buf->tab_arg[x] != NULL)
	{
		tmp_tab[x] = NULL;
		if (x != buf->pos)
		{
			tmp_tab[y] = ft_strdup(buf->tab_arg[x]);
			tmp_nbr[y] = buf->nbr[x];
			y++;
		}
		free(buf->tab_arg[x]);
		x++;
	}
	free(buf->tab_arg);
	free(buf->nbr);
	if (!(buf->tab_arg = ft_memalloc(sizeof(char *) * buf->argc)))
		return ;
	ft_memset(buf->tab_arg, 0, sizeof(char *) * buf->argc);
	if (!(buf->nbr = ft_memalloc(sizeof(int) * buf->argc)))
		return ;
	ft_memset(buf->nbr, 0, sizeof(int) * buf->argc);
	x = 0;
	while (tmp_tab[x] != NULL)
	{
		buf->tab_arg[x] = ft_strdup(tmp_tab[x]);
		buf->nbr[x] = tmp_nbr[x];
		free(tmp_tab[x]);
		x++;
	}
	free(tmp_nbr);
	free(tmp_tab);
	if (buf->pos > 0)
		buf->pos--;
	buf->argc = buf->argc - 1;
}
