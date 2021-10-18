/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:01:14 by tlemma            #+#    #+#             */
/*   Updated: 2021/10/18 17:30:44 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

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

int main(int argc, char *argv[])
{
	int fd[2];
		// fd[0] = read
		// fd[1] = write

	if (pipe(fd) == -1)
		printf("Error with opening the pipe.\n");

	int pid = fork();
	if (pid < 0)
		printf("Error with forking!");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execve("ls", "ls -la", NULL);
		close(fd[1]);
	}
	
	return (0);
}