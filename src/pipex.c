/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:10:42 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/13 14:16:10 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		ft_printf("Error: No arguments given\n");
		return (1);
	}
	if (argc < 5)
	{
		ft_printf("Error: Too few arguments given\n");
		return (1);
	}
	(void)argv[0][0];
	return (0);
}