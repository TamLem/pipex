/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:34:56 by tlemma            #+#    #+#             */
/*   Updated: 2021/11/02 17:51:03 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

typedef struct	pipex_args
{
	char	*infile;
	char	*outfile;
	char	**cmd1;
	char	**cmd2;
	char	**path1;
	char	**path2;
}		pipe_args;

pipe_args	g_pa;

char	*ft_strjoin2(char *s1, char *s2);
char	**ft_getpath(char *keypairs[], char *cmd);
void	free_args();
void	err(int res, char c, char *info);
void	check_cmds();

#endif

