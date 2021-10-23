/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:01:14 by tlemma            #+#    #+#             */
/*   Updated: 2021/10/23 16:03:42 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int get_args(int argc, char *argv[])
{
	int i = 0;
	
	while(i < argc)
	{
		printf("arg %d: %s\n", i, argv[i]);
		i++;
	}
	
	return (0);
}

char **ft_getpath(char *keypairs[], char *cmd)
{
	int 	i;
	char	*keypair;
	char	**path;

	i = 0;
	keypair = NULL;
	path = NULL;
	while (keypairs[i])
	{
		keypair = ft_strnstr(keypairs[i], "PATH=", 5);
		if (keypair != NULL)
		{
			keypair = ft_strnstr(keypair, "/", 6);
			path = ft_split(keypair, ':');
			break ;
		}
		i++;
	}
	i = 0;
	while(path[i])
	{
		path[i] = ft_strjoin2(path[i], "/");
		path[i] = ft_strjoin2(path[i], cmd);
		i++;
	}
	return (path);
}

void	init_args(pipe_args *pa, int argc, char *argv[], char *envp[])
{
	int		i;

	i = 0;
	pa->infile = argv[1];
	pa->cmd1 = ft_split(argv[2], ' ');
	pa->cmd2 = ft_split(argv[3], ' ');
	pa->outfile = argv[4];
	pa->path1 = ft_getpath(envp, *(pa->cmd1));
	pa->path2 = ft_getpath(envp, *(pa->cmd2));
}

void	child_p(int p, int fd[], pipe_args *pa, char **path)
{
	if (p == 1)
		dup2(fd[1], STDOUT_FILENO);
	if (p == 2)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (p == 1)
		while(execve(*path++, pa->cmd1, NULL) && *path);
	if (p == 2)
		while(execve(*path++, pa->cmd2, NULL) && *path);
	// while(printf("%s\n%s\n%s\n", *path++, pa->cmd2[1], NULL) && *path);
	printf("Error occured");
}

int main(int argc, char *argv[], char *envp[])
{
	char	**path;
	int		i;

	if (argc < 5)
		return (0);
	i = 0;
	pipe_args pa;
	init_args(&pa, argc, argv, envp);
	// printf("%s\n", pa.cmd2[2]);
	// return 0;
	int fd[2]; // fd[0] = read , fd[1] = write
	if (pipe(fd) == -1)
		printf("Error with opening the pipe.\n");
	int pid1 = fork();
	if (pid1 < 0)
		printf("Error with forking!");
	if (pid1 == 0)
	{
		child_p(1, fd, &pa, pa.path1);
	}
	
	int pid2 = fork();
	if (pid2 < 0)
		return (3);
	if (pid2 == 0)
	{
		child_p(2, fd, &pa, pa.path2);
		// path = ft_getpath(envp, pa.cmd2[0]);
		// dup2(fd[0], STDIN_FILENO);
		// close(fd[1]);
		// close(fd[0]);
		// while(execve(*path++, pa.cmd2, NULL) && *path);
		// printf("Error occured");
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (0);
}