/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:14:38 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/15 17:08:36 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/printf/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>

void	write_error(char *str);
void	free_pipes(int index, int **pipes);
void	create_pipes(int pnum, int ***pipes);
void	close_pipes(int i, int pnum, int ***pipes);
void	close_pipes_parent(int pnum, int ***pipes);

#endif