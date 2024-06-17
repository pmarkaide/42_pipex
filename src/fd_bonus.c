/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:21:26 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/17 15:43:42 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	open_infile(t_data *data)
{
	if(data->here_doc == 1)
		here_doc(data);
	data->in_fd = open(data->infile, O_RDONLY);
	if (errno == ENOENT)
		free_data_and_exit(data, data->infile, NO_FILE);
	if (errno == EACCES)
		free_data_and_exit(data, data->infile, PERMISSION_DENIED);
	if (errno == IS_DIRECTORY)
		free_data_and_exit(data, data->infile, IS_DIRECTORY);
}

void	open_outfile(t_data *data)
{
	if(data->here_doc == 1)
		data->out_fd = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		data->out_fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (errno == ENOENT)
		free_data_and_exit(data, data->outfile, NO_FILE);
	if (errno == EACCES)
		free_data_and_exit(data, data->outfile, PERMISSION_DENIED);
	if (errno == IS_DIRECTORY)
		free_data_and_exit(data, data->infile, IS_DIRECTORY);
}

void	close_open_fds(t_data *data)
{
	if (data->pipe_fd[0] != -1)
		close(data->pipe_fd[0]);
	if (data->pipe_fd[1] != -1)
		close(data->pipe_fd[1]);
	if (data->in_fd != -1)
		close(data->in_fd);
	if (data->out_fd != -1)
		close(data->out_fd);
}

void	dup2_or_exit(t_data *data, int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) < 0)
		free_data_and_exit(data, "dup2 error", -1);
}

void	dup_file_descriptors(t_data *data, int cmd, int read_end)
{
	if (cmd == 0)
	{
		open_infile(data);
		dup2_or_exit(data, data->in_fd, STDIN_FILENO);
		close(data->in_fd);
		dup2_or_exit(data, data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[1]);
	}
	else if (cmd == data->num_cmds - 1)
	{
		open_outfile(data);
		dup2_or_exit(data, read_end, STDIN_FILENO);
		close(read_end);
		dup2_or_exit(data, data->out_fd, STDOUT_FILENO);
		close(data->out_fd);
	}
	else
	{
		dup2_or_exit(data, read_end, STDIN_FILENO);
		close(read_end);
		dup2_or_exit(data, data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[1]);
	}
}
