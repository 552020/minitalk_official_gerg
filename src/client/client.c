/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:08:32 by slombard          #+#    #+#             */
/*   Updated: 2023/09/26 16:38:30 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client	g_client;

int			waiting_for_sig(void);
void		error(char *error_msg);
void		args_check(int argc, char **argv);

static void	sig_handler(int sig)
{
	if (sig == SIGUSR2)
	{
		ft_printf("Transmission complete!\n");
		exit(0);
	}
	else if (sig == SIGUSR1)
	{
		g_client.waiter = 0;
		if (g_client.active)
		{
			if (++g_client.received_bit != g_client.sent_bit)
				error("Some anomaly happened!");
		}
	}
}

void	transmission_msg(char *msg, pid_t server_pid)
{
	char	c;
	char	i;

	while (*msg)
	{
		c = *msg;
		i = 0;
		while (i++ < 8)
		{
			g_client.waiter = 1;
			++g_client.sent_bit;
			if (c & 0b10000000)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			while (waiting_for_sig())
				usleep(10);
			c = c << 1;
		}
		++g_client.len;
		msg++;
	}
}

static void	transmission_zero(pid_t server_pid)
{
	int	i;

	i = 8;
	g_client.active = 0;
	while (i-- > 0)
	{
		kill(server_pid, SIGUSR2);
		usleep(1000);
	}
}

void	setup_signal_handler(void)
{
	sigemptyset(&g_client.sa.sa_mask);
	g_client.sa.sa_handler = sig_handler;
	sigaction(SIGUSR1, &g_client.sa, 0);
	sigaction(SIGUSR2, &g_client.sa, 0);
}

int	main(int argc, char **argv)
{
	args_check(argc, argv);
	setup_signal_handler();
	g_client.active = 1;
	ft_printf("The size of the message is  %i  bytes.\n", ft_strlen(argv[2]));
	ft_printf("The transmission has...");
	transmission_msg(argv[2], ft_atoi(argv[1]));
	transmission_zero(ft_atoi(argv[1]));
	error("The client did not get the bye-bye signal.");
	return (0);
}