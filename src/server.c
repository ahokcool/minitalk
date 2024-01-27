/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:51:32 by astein            #+#    #+#             */
/*   Updated: 2024/01/27 21:45:07 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static pid_t	g_client_pid;

/**
 * @brief	just printing a header to the terminal using 'put_header' 
 */
static void	put_header_server(void)
{
	char	*msg;
	char	*pid_server;

	pid_server = ft_itoa(getpid());
	msg = ft_strcat_multi(3, "ASTEINS MINITALK SERVER\n(PID SERVER: ",
			pid_server, ")\n");
	put_header("📭", msg);
	free_whatever("pp", msg, pid_server);
}

/**
 * @brief	just printing a header to the terminal using 'put_header' like:
 *
 * 				🔽---------------------------------------------------🔽
 * 				🔽                 RECEIVING MESSAGE                 🔽
 * 				🔽                (from PID: 247924)                 🔽
 * 				🔽---------------------------------------------------🔽
 * 
 * 		or
 * 

									* 				🔼---------------------------------------------------🔼				
 * 				🔼                  END OF MESSAGE                   🔼
 * 				🔼                (from PID: 247967)                 🔼
 * 				🔼---------------------------------------------------🔼
 * 
 * @param client_pid	the pid that should be shown in the msg
 * @param header		ft_true 	= HEADER message
 * 						ft_false	= FOOTER message
 */
static void	put_msg_frame(pid_t client_pid, t_bool header)
{
	char	*msg;
	char	*pid_client;

	pid_client = ft_itoa(client_pid);
	if (header)
	{
		msg = ft_strcat_multi(3, "RECEIVING MESSAGE\n(from PID: ", pid_client,
				")\n");
		put_header("🔽", msg);
	}
	else
	{
		write(1, "\n", 1);
		write(1, "\n", 1);
		msg = ft_strcat_multi(3, "END OF MESSAGE\n(from PID: ", pid_client,
				")\n");
		put_header("🔼", msg);
		put_header_server();
	}
	free_whatever("pp", msg, pid_client);
}

/**
 * @brief	receiving a message via only BIT_0 and BIT_1 (USR1 and USR2) signals
 * 
 * 			the reception of each signal is confirmed by sending a BIT_1 signal
 * 			back to the client. (only then will the client send the next signal)
 * 			
 * 			when the message is completed, the client sends a \0 and the server
 * 			responds with a BIT_1 to end the transmission
 * 
 * @param signal	signal that was recieved
 */
static void	receive_msg(int signal)
{
	static int	c;
	static int	bit_shift;

	if (signal == BIT_1)
		c |= (1 << bit_shift);
	bit_shift++;
	if (bit_shift == 8)
	{
		if (c != 0)
			write(1, &c, 1);
		bit_shift = 0;
		usleep(100);
		if (c == 0)
		{
			kill(g_client_pid, BIT_1);
			put_msg_frame(g_client_pid, ft_false);
			usleep(500);
			g_client_pid = 0;
		}
		else
			kill(g_client_pid, BIT_0);
		c = (int)0;
	}
	else
		kill(g_client_pid, BIT_0);
}

/**
 * @brief	handling the signals: BIT_0 and BIT_1 (USR1 and USR2)
 * 
 * 			-> see README.md for more info
 * 
 * @param signal	signal that was recieved
 * @param info 		used to get the pid of the client
 * @param context 	unused
 */
static void	handler(int signal, siginfo_t *info, void *context)
{
	(void)context;
	if (g_client_pid != info->si_pid)
	{
		if (signal == BIT_0)
		{
			kill(info->si_pid, BIT_0);
			return ;
		}
	}
	if (!g_client_pid)
	{
		if (signal == BIT_1)
		{
			g_client_pid = info->si_pid;
			kill(g_client_pid, BIT_1);
			put_msg_frame(g_client_pid, ft_true);
			sleep(1);
			return ;
		}
	}
	if (g_client_pid == info->si_pid)
		receive_msg(signal);
}

/**
 * @brief	- initializing the global 'g_client_pid' to zero
 * 			- printing the server header to the terminal
 * 			- creating a signal handler and liking the BIT_0 and BIT_1 signals
 * 				to the function 'handler'
 * 			- loop for ever (the signals will do the rest)
 * 
 */
int	main(void)
{
	struct sigaction	signal_action;

	g_client_pid = 0;
	put_header_server();
	signal_action.sa_handler = 0;
	signal_action.sa_flags = SA_SIGINFO | SA_NODEFER;
	signal_action.sa_sigaction = handler;
	sigaction(BIT_0, &signal_action, NULL);
	sigaction(BIT_1, &signal_action, NULL);
	while (1)
		pause();
}
