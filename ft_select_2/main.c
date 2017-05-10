/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 18:06:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/10 18:20:28 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

int		main(int argc, char **argv)
{
	int		x;
	char	**tab;

	x = 0;
	if (!(tab = ft_memalloc(sizeof(char *) * argc - 1)))
		return (-1);
	while (argv[x] != NULL)
	{
		tab[x - 1] = ft_strdup(argv[x]);
		x++;
	}
	ft_print_argv(argc - 1, tab);
	return (0);
}
