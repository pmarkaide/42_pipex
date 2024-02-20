/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:21:10 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/02/20 16:44:57 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/colors.h"  /* color codes for printf*/
#include "../lib/libft/libft.h" /*libft library*/
#include <fcntl.h>              /* for open, */
#include <stdio.h>              /* for perror, strerror, access */
#include <stdlib.h>             /* for malloc, free, exit */
#include <string.h>             /* for strerror */
#include <sys/wait.h>           /* for waitpid, wait, */
#include <unistd.h>             /* for close, read, write, unlink, dup, dup2, execve, fork, pipe */

typedef struct s_data
{
	int		pipe_fd[2];
	char	*infile;
	char	*outfile;
	char	**cmd1;
	char	**cmd2;
	char	*exec_path;
	char	**cmd;
	char	**paths;
}			t_data;

int			error_1(const char *error_message);
char		*error_null(const char *error_message);
void		exit_1(const char *error_msg);
void		free_data(t_data *data);
void		free_data_and_exit(t_data *data, const char *error_msg);
void		init_struct(t_data *data, char **argv, char **envp);
char		**parse_cmd_args(char *arg);
char		**parse_paths(char **envp);
void		pipex(t_data *data, char **envp);
void		execute_cmd(t_data *data, char **envp);
void		get_executable_path(t_data *data);
