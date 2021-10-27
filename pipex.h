/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:34:56 by tlemma            #+#    #+#             */
/*   Updated: 2021/10/27 16:34:17 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include "./libft/libft.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

typedef struct	pipex_args
{
	char	*infile;
	char	**cmd1;
	char	**cmd2;
	char	*outfile;
	char	**path1;
	char	**path2;
}		pipe_args;

char	*ft_strjoin2(char *s1, char *s2);


#endif

