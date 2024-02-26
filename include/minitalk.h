/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:54:01 by astein            #+#    #+#             */
/*   Updated: 2024/02/26 23:20:29 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../lib/libft/libft_gnl_printf.h"
# include <signal.h>
# include <unistd.h>

# define CONNECTION_ATTEMPTS 5
# define BIT_0 SIGUSR1
# define BIT_1 SIGUSR2
# define E_S EXIT_SUCCESS
# define E_F EXIT_FAILURE

typedef struct s_client
{
	pid_t	pid_server;
	char	*msg;
	t_bool	found_server;
	t_bool	transmitting;
}			t_client;

void		put_header(char *symbol, char *msg);
void		put_exit_header(int exit_status, char *msg);

#endif