/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:42:37 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/02/19 16:06:40 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void execute_cmd(t_data *data, char **envp)
{
	
	if(execve(data->cmd[0],data->cmd, envp) == -1)
	{
		exit_1("Execve error");
	}
	//printf("in_fd: %d\nargv[1]%s\n,envp[0]%s\n", data->in_fd, argv[1], envp[0]);
}


void execute_child1(t_data *data, char **envp)
{
	//TODO: eval if the file has access
	data->cmd = data->cmd1;
	printf("executing child1 with %s\n",data->cmd[0]);
	dup2(data->in_fd,STDIN_FILENO);
	close(data->in_fd);
	dup2(data->pipe_fd[1],STDOUT_FILENO);
	close(data->pipe_fd[1]);
	execute_cmd(data, envp);
}





void pipex(t_data *data, char **argv, char **envp)
{
	pid_t	pid[2];
	
	pid[0] = fork();
	if (pid[0] == -1)
	{
		free_data(data);
		exit_1("fork failed");
	}
	if (pid[0] == 0)
		execute_child1(data, envp);
	pid[1] = fork();
	if (pid[1] == -1)
	{
		free_data(data);
		exit_1("fork failed");
	}
	(void)argv;
	// if (pid[1] == 0)
	// 	execute_child2(data, argv, envp);
}
