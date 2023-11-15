/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:07:58 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/15 17:08:47 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

#define PROCESS_NUM 10

static void	child_routine(int pnum, int *i, int *x, int **pids, int ***pipes)
{
	*pids = (int *)malloc(pnum * sizeof(int));
	if (!(*pids))
		write_error("Error creating pids");
	(*pids)[*i] = fork();
	if ((*pids)[*i] == -1)
		write_error("Error with creating process\n");
	if ((*pids)[*i] == 0)
	{
		close_pipes(*i, pnum, pipes);
		if (read((*pipes)[*i][0], x, sizeof(int)) == -1)
			write_error("Error at reading\n");
		printf("(%d) Got %d\n", *i, *x);
		(*x)++;
		if (write((*pipes)[(*i) + 1][1], x, sizeof(int)) == -1)
			write_error("Error at writing\n");
		printf("(%d) Sent %d\n", *i, *x);
		close((*pipes)[*i][0]);
		close((*pipes)[(*i) + 1][1]);
		exit(0);
	}
	(*i)++;
}

static void	parent_routine(int pnum, int ***pipes)
{
	int	y;

	y = 5;
	printf("Main process sent %d\n", y);
	if (write((*pipes)[0][1], &y, sizeof(int)) == -1)
		write_error("Error at writing\n");
	if (read((*pipes)[pnum][0], &y, sizeof(int)) == -1)
		write_error("Error at reading\n");
	printf("The final result is %d\n", y);
	close((*pipes)[0][1]);
	close((*pipes)[pnum][0]);
}

int	main(int argc, char *argv[])
{
	int	*pids;
	int	**pipes;
	int	i;
	int	x;

	pipes = NULL;
	if (argc != 5)
	{
		perror("Wrong number of arguments\n");
		exit(-1);
	}
	(void)argv;
	create_pipes(PROCESS_NUM, &pipes);
	i = 0;
	while (i < PROCESS_NUM)
		child_routine(PROCESS_NUM, &i, &x, &pids, &pipes);
	close_pipes_parent(PROCESS_NUM, &pipes);
	parent_routine(PROCESS_NUM, &pipes);
	i = 0;
	while (i++ < PROCESS_NUM)
		wait(NULL);
	return (0);
}
