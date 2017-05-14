/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fleche_directionnelle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:22:44 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/14 12:58:46 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	fleche_directionnelle(char *bufer, t_buf *buf)
{
	if (bufer[2] == 'A')
	{
		if (buf->pos > 0)
			buf->pos--;
		else
			buf->pos = buf->argc - 1;
	}
	if (bufer[2] == 'B')
	{
		if (buf->pos < buf->argc - 1)
			buf->pos++;
		else
			buf->pos = 0;
	}
	if (bufer[2] == 'C')
	{
		if (buf->pos < (buf->argc - buf->max_lig))
			buf->pos = buf->pos + buf->max_lig;
	}
	if (bufer[2] == 'D')
	{
		if (buf->pos >= buf->max_lig)
			buf->pos = buf->pos - buf->max_lig;
	}
}
