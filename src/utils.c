/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:04:02 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/15 17:08:27 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	write_error(char *str)
{
	perror(str);
	exit(-1);
}

void	free_pipes(int index, int **pipes)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(pipes[i]);
	}
	free(pipes);
}

void	create_pipes(int pnum, int ***pipes)
{
	int	i;

	*pipes = (int **)malloc((pnum + 1) * sizeof(int *));
	if (!(*pipes))
		write_error("Error with malloc the double pointer\n");
	i = 0;
	while (i < pnum + 1)
	{
		(*pipes)[i] = (int *)malloc(2 * sizeof(int));
		if (!(*pipes)[i])
		{
			free_pipes(i, *pipes);
			write_error("Error with malloc a pipe\n");
		}
		i++;
	}
	i = 0;
	while (i < pnum + 1)
	{
		if (pipe((*pipes)[i]) == -1)
			write_error("Error with creating pipe\n");
		i++;
	}
}

void	close_pipes(int i, int pnum, int ***pipes)
{
	int	j;

	j = 0;
	while (j < pnum + 1)
	{
		if (i != j)
			close((*pipes)[j][0]);
		if (i + 1 != j)
			close((*pipes)[j][1]);
		j++;
	}
}

void	close_pipes_parent(int pnum, int ***pipes)
{
	int	j;

	j = 0;
	while (j < pnum + 1)
	{
		if (j != pnum)
			close((*pipes)[j][0]);
		if (j != 0)
			close((*pipes)[j][1]);
		j++;
	}
}
