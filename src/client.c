/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:56:29 by astein            #+#    #+#             */
/*   Updated: 2024/02/26 23:27:14 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static t_client	g_client;

/**
 * @brief	just printing a header to the terminal using 'put_header' 
 */
static void	put_header_client(void)
{
	char	*msg;
	char	*pid_server;
	char	*pid_client;

	pid_server = ft_itoa(g_client.pid_server);
	pid_client = ft_itoa(getpid());
	msg = ft_strcat_multi(5, "ASTEINS MINITALK CLIENT\n(PID CLIENT: ",
			pid_client, ")\n(PID SERVER: ", pid_server, ")\n");
	put_header("💬", msg);
	free_whatever("ppp", msg, pid_server, pid_client);
}

/**
 * @brief	transmitting bit by bit the message stored in 'g_client.msg' to the
 * 			server with the pid 'g_client.pid_server'.
 * 
 * 			if the message is finished a \0 character will be transmitted to let
 * 			the server know that the transaction is over and he can close the
 * 			connection.
 */
static void	transmit_next_bit(void)
{
	static int	cur_char;
	static int	i;

	if (i == 8 && cur_char != 0)
	{
		ft_printf("%c", cur_char);
		cur_char = 0;
		i = 0;
	}
	if (!cur_char)
	{
		if (g_client.msg[0] == '\0')
			kill(g_client.pid_server, BIT_0);
		else
		{
			cur_char = g_client.msg[0];
			g_client.msg++;
			i = 0;
		}
	}
	if (cur_char && (cur_char >> i) & 1)
		kill(g_client.pid_server, BIT_1);
	else if (cur_char)
		kill(g_client.pid_server, BIT_0);
	i++;
}

/**
 * @brief	-> see README.md for more info
 * 
 * @param signal	signal that was recieved
 * @param info 		unused
 * @param context 	unused
 */
static void	handle_response(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (g_client.transmitting)
	{
		if (signal == BIT_0)
			transmit_next_bit();
		if (signal == BIT_1)
		{
			write(1, "\n\n", 2);
			if (g_client.msg[0] == '\0')
				put_exit_header(E_S, "!MESSAGE DELIVERED SUCCESSFULLY!");
			else
				put_exit_header(E_F, "!COMMUNICATION ERROR!");
		}
		return ;
	}
	if (!g_client.found_server && signal == BIT_0)
		g_client.found_server = 1;
	else if (g_client.found_server && !g_client.transmitting && signal == BIT_1)
	{
		g_client.transmitting = ft_true;
		put_header("🔜", "SERVER IS READY\n(start transmitting...)");
		usleep(500000);
		transmit_next_bit();
	}
}

/**
 * @brief	- checking if the arguments are correct
 * 				- argv[1] the message
 * 				- argv[2] a numeric pid > 0
 * 
 * 			- initializing all members of the global struct 'g_client'
 * 			- printing the client header to the terminal
 * 			- creating a signal handler and liking the BIT_0 and BIT_1 signals
 * 				to the function 'handle_response'
 * @param argc 
 * @param argv 
 */
static void	ini_client(int argc, char **argv)
{
	static int			i;
	struct sigaction	signal_action;

	if (argc != 3)
		put_exit_header(E_F, "!WRONG PARAMETERS!\n \n./minitalk <MSG> <PID>");
	while (argv[2][i])
	{
		if (!ft_isdigit(argv[2][i]))
			put_exit_header(E_F, "!WRONG SERVER PID!\n(not numeric)");
		i++;
	}
	g_client.pid_server = ft_atoi(argv[2]);
	if (g_client.pid_server <= 0)
		put_exit_header(E_F, "!WRONG SERVER PID!\n(pid <= 0)");
	g_client.msg = argv[1];
	g_client.found_server = ft_false;
	g_client.transmitting = ft_false;
	put_header_client();
	sigemptyset(&signal_action.sa_mask);
	signal_action.sa_flags = SA_SIGINFO;
	signal_action.sa_sigaction = handle_response;
	sigaction(BIT_0, &signal_action, NULL);
	sigaction(BIT_1, &signal_action, NULL);
}

/**
 * @brief	- check args and initialize 'g_client' via function 'ini_client'
 * 			- try to get a respond (BIT_0) from server a few times
 * 				- if YES
 * 					- ping server each second to get a go (BIT_1)
 * 						- if YES 	-> start transmitting
 * 						- if NO		-> try again :D
 * 				- if NO
 * 					- display connection error and exit
 * 
 * @param argc 
 * @param argv 
 */
int	main(int argc, char **argv)
{
	int	i;

	ini_client(argc, argv);
	i = -1;
	while (!g_client.found_server && i++ < CONNECTION_ATTEMPTS - 1)
	{
		put_header("🔴", "try to connect to server...");
		kill(g_client.pid_server, BIT_0);
		sleep(2);
	}
	if (i == CONNECTION_ATTEMPTS)
		put_exit_header(E_F, "CONNECTION ERROR\n(server doesnt respond)");
	put_header("🟠", "server did respond...");
	while (!g_client.transmitting)
	{
		put_header("🟡", "ping server to get a 'go'...");
		kill(g_client.pid_server, BIT_1);
		sleep(1);
	}
	while (1)
		;
}
