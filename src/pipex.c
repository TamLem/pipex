/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:01:14 by tlemma            #+#    #+#             */
/*   Updated: 2021/11/02 17:34:45 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	child_p(int p, int fd[], int fd_file[])
{
	char	**path;

	if (p == 1)
	{
		path = g_pa.path1;
		dup2(fd_file[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	if (p == 2)
	{
		path = g_pa.path2;
		dup2(fd[0], STDIN_FILENO);
		dup2(fd_file[1], STDOUT_FILENO);
	}
	close(fd[0]);
	close(fd[1]);
	if (p == 1)
		while (execve(*path, g_pa.cmd1, NULL) && *path)
			path++;
	if (p == 2)
		while (execve(*path, g_pa.cmd2, NULL) && *path)
			path++;
}

void	err(int res, char c, char *info)
{
	if ((res >= 0 && c != 'a') || res == 1)
		return ;
	if (c == 'a')
		perror("usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n");
	if (c == 'f')
		perror(info);
	if (c == 'p')
		perror("pipe");
	if (c == 'k')
		perror("fork");
	if (c == 'x')
		perror(info);
	if (c != 'a')
		free_args();
	exit (-1);
}

static void	init_args(char *argv[], char *envp[])
{
	g_pa.infile = argv[1];
	g_pa.outfile = argv[4];
	g_pa.cmd1 = ft_split(argv[2], ' ');
	g_pa.cmd2 = ft_split(argv[3], ' ');
	g_pa.path1 = ft_getpath(envp, *(g_pa.cmd1));
	g_pa.path2 = ft_getpath(envp, *(g_pa.cmd2));
}

int	main(int argc, char *argv[], char *envp[])
{
	int			fd_file[2];
	int			fd[2];
	int			pid1;
	int			pid2;

	err(argc == 5, 'a', argv[0]);
	init_args(argv, envp);
	err(fd_file[0] = open(g_pa.infile, O_RDONLY), 'f', argv[1]);
	err(fd_file[1] = open(g_pa.outfile, O_RDWR
			| O_CREAT, S_IRWXU), 'f', argv[4]);
	check_cmds(&g_pa);
	err(pipe(fd), 'p', NULL);
	err(pid1 = fork(), 'k', NULL);
	if (pid1 == 0)
		child_p(1, fd, fd_file);
	err(pid2 = fork(), 'k', NULL);
	if (pid2 == 0)
		child_p(2, fd, fd_file);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_args();
	return (1);
}
