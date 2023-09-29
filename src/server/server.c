/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:08:28 by slombard          #+#    #+#             */
/*   Updated: 2023/08/11 22:58:55 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_server	g_server;

static void	init(void);
static void	signal_handler(int sig, siginfo_t *info, void *context);
void		build_and_write_char(int sig, pid_t client);

static void	init(void)
{
	g_server.char_accumulator = 0;
	g_server.bit_index = 0;
	g_server.connection = OFF;
	g_server.sa.sa_sigaction = signal_handler;
	g_server.sa.sa_flags = SA_SIGINFO;
	sigemptyset(&g_server.sa.sa_mask);
	sigaction(SIGUSR1, &g_server.sa, 0);
	sigaction(SIGUSR2, &g_server.sa, 0);
}

static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	sigaddset(&g_server.sa.sa_mask, SIGUSR1);
	sigaddset(&g_server.sa.sa_mask, SIGUSR2);
	(void)context;
	build_and_write_char(sig, info->si_pid);
	sigemptyset(&g_server.sa.sa_mask);
}

void	build_and_write_char(int sig, pid_t client)
{
	g_server.connection = ON;
	g_server.char_accumulator = g_server.char_accumulator << 1;
	if (sig == SIGUSR1)
		g_server.char_accumulator |= 1;
	if (++g_server.bit_index >= 8)
	{
		if (g_server.char_accumulator == 0)
		{
			kill(client, SIGUSR2);
			ft_printf("\nDone!\n");
			init();
		}
		else
			write(1, &g_server.char_accumulator, 1);
		g_server.char_accumulator = 0;
		g_server.bit_index = 0;
	}
	kill(client, SIGUSR1);
}

int	main(void)
{
	ft_printf("Server PID: %d.\n", getpid());
	init();
	while (1)
	{
		if (usleep(CONNECTION_CHECK_INTERVAL) == 0 && g_server.connection == ON)
		{
			ft_printf("Something is rotten in the state of this server! Let's restart it!\n");
			init();
		}
	}
}
