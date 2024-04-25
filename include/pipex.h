/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:21:10 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/04/25 21:09:11 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/colors.h"  /* color codes for printf*/
#include "../lib/libft/libft.h" /*libft library*/
#include <fcntl.h>              /* for open, */
#include <stdio.h>              /* for perror, strerror, access */
#include <stdlib.h>             /* for malloc, free, exit */
#include <string.h>             /* for strerror */
#include <sys/wait.h>           /* for waitpid, wait, */
#include <unistd.h>             /* for close, read, write, unlink, dup, dup2,
	execve, fork, pipe */
#include <errno.h>				/* for errno         */

#define NO_FILE 1
#define PERMISSION_DENIED 126
#define COMMAND_NOT_FOUND 127
#define INVALID_ARGUMENT 2
#define OPERATION_NOT_PERMITTED 1
#define IS_DIRECTORY -1

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
	char	*shell;
}			t_data;

int			error_1(const char *error_message);
char		*error_null(const char *error_message);
void		exit_1(const char *error_msg);
void		free_data(t_data *data);
void		free_data_and_exit(t_data *data, char *file, int exit_code);
void		init_struct(t_data *data, char **argv, char **envp);
char		**parse_cmd_args(char *arg);
char		**parse_paths(char **envp);
int			pipex(t_data *data, char **envp);
int			execute_cmd(t_data *data, char **envp);
void		eval_executable(t_data *data);
void		get_executable_path(t_data *data);
void		eval_executable_permissions(t_data *data);
void		cmd_is_directory(t_data *data);

