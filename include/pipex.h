/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:21:10 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/02/18 15:05:33 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h> /* for close, read, write, unlink, dup, dup2, execve, fork, pipe */
# include <fcntl.h> /* for open, */
# include <string.h> /* for strerror */
# include <stdlib.h> /* for malloc, free, exit */
# include <stdio.h> /* for perror, strerror, access */
# include <sys/wait.h> /* for waitpid, wait, */
#include "../include/colors.h" /* color codes for printf*/
#include "../lib/libft/libft.h" /*libft library*/


typedef struct s_data
{
	int pipe_fd[2];
	char **cmd1;
	char **cmd2;
	char **paths;
}			t_data;



int				error_1(const char *error_message);
char			*error_null(const char *error_message);
void			exit_1(const char *error_msg);

void	init_struct(t_data	*data, char **argv, char **envp);
char	**parse_cmd_args(char *arg);
