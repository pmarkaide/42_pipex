/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:42:37 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/05/04 19:12:18 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int execute_shell_cmd(t_data *data, char **envp)
{
	char *shell_cmd[4];
	shell_cmd[0] = data->shell;
    shell_cmd[1] = "-c";
    shell_cmd[2] = data->cmd[0];
    shell_cmd[3] = NULL;

	if (execve(data->shell, shell_cmd, envp) == -1)
    {
		ft_putstr_fd("execve failed\n",2);
		return (EXIT_FAILURE);
    }
	return (0);
}

int	execute_cmd(t_data *data, char **envp)
{
	int exit_code;

	if (execve(data->exec_path, data->cmd, envp) == -1)
	{
		exit_code = execute_shell_cmd(data, envp);
		return (exit_code);
	}
	return (0);
}

int	execute_child1(t_data *data, char **envp)
{
	int	in_fd;
	int exit_code;

	exit_code = 0;
	close(data->pipe_fd[0]);
	in_fd = open(data->infile, O_RDONLY);
	if (errno == ENOENT)
		free_data_and_exit(data, data->infile, NO_FILE);
	if (errno == EACCES)
		free_data_and_exit(data, data->infile, PERMISSION_DENIED);
	if (dup2(in_fd, STDIN_FILENO) == -1)
		free_data_and_exit(data, "dup2 error", -1);
	close(in_fd);
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
		free_data_and_exit(data, "dup2 error", -1);
	close(data->pipe_fd[1]);
	data->cmd = data->cmd1;
	cmd_is_directory(data);
	eval_executable(data);
	exit_code = execute_cmd(data, envp);
	return(exit_code);
}

void	execute_child2(t_data *data, char **envp)
{
	int	out_fd;
	close(data->pipe_fd[1]);
	out_fd = open(data->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (errno == ENOENT)
		free_data_and_exit(data, data->outfile, NO_FILE);
	if(errno == EACCES)
		free_data_and_exit(data, data->outfile, PERMISSION_DENIED);
	if (dup2(data->pipe_fd[0], STDIN_FILENO) == -1)
		free_data_and_exit(data, "dup2 error", -1);
	close(data->pipe_fd[0]);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		free_data_and_exit(data, "dup2 error", -1);
	close(out_fd);
	data->cmd = data->cmd2;
	cmd_is_directory(data);
	eval_executable(data);
	execute_cmd(data, envp);
}

int	pipex(t_data *data, char **envp)
{
	pid_t	pid[2];
	int		status1;
	int		status2;

	int exit_code;
	exit_code = 0;
	if (pipe(data->pipe_fd) == -1)
		error_1("pipe failed");
	pid[0] = fork();
	if (pid[0] == -1)
		free_data_and_exit(data, "fork failed",-1);
	if (pid[0] == 0)
		execute_child1(data, envp);
	pid[1] = fork();
	if (pid[1] == -1)
		free_data_and_exit(data, "fork failed", -1);
	if (pid[1] == 0)
		execute_child2(data, envp);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	waitpid(pid[0], &status1, 0);
	waitpid(pid[1], &status2, 0);
    if (WIFEXITED(status2) && WEXITSTATUS(status2) != EXIT_SUCCESS)
		exit_code = WEXITSTATUS(status2);
	return exit_code;
}
