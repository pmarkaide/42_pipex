/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:21:10 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/18 10:27:07 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft/libft.h" /* libft library */
# include <fcntl.h>              /* for open, O_DIRECTORY */
# include <stdlib.h>             /* for malloc, free, exit */
# include <sys/wait.h>           /* for waitpid, wait, */
# include <unistd.h>             /* for file r/w, dup2, execve, fork, pipe */
# include <errno.h>              /* for errno */

# define NO_FILE 1
# define PERMISSION_DENIED 126
# define COMMAND_NOT_FOUND 127
# define SEGFAULT 139
# define IS_DIRECTORY -1
# define EXEC_NOT_FOUND -2

typedef struct s_data
{
	int		pipe_fd[2];
	char	*infile;
	char	*outfile;
	char	**cmd1;
	char	**cmd2;
	char	*executable;
	char	**cmd;
	char	**paths;
	char	*shell;
}			t_data;

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
int			cmd_is_directory(t_data *data);
char		**clean_arguments(char *arg);
int			execute_child1(t_data *data, char **envp);
void		execute_child2(t_data *data, char **envp);
char		*allocate_result(const char *arg);
char		*remove_str_quotes(char *arg);
int			error_msg(char *msg);
void		close_pipes(t_data *data);

#endif /* PIPEX_H */