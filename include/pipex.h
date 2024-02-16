/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:21:10 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/02/16 16:28:44 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h> /* for close, read, write, unlink, dup, dup2, execve, fork, pipe */
# include <fcntl.h> /* for open, */
# include <string.h> /* for strerror */
# include <stdlib.h> /* for malloc, free, exit */
# include <stdio.h> /* for perror, strerror, access */
# include <sys/wait.h> /* for waitpid, wait, */
#include "../include/colors.h" /* color codes for printf*/


int				error_1(const char *error_message);
char			*error_null(const char *error_message);
void			exit_1(const char *error_msg);