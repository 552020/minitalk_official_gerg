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

int			waiting_server_feedback(void);
void		print_error_and_exit(char *error_msg);
void		args_check(int argc, char **argv);

static void	sig_handler(int sig)
{
	if (sig == SIGUSR2)
	{
		ft_printf("Transmission complete!\n");
		exit(0);
	}
	else if (sig == SIGUSR1)
		g_client.server_feedback = RECEIVED;
}

void	send_msg(char *msg, pid_t server_pid)
{
	char	c;
	char	i;

	while (*msg)
	{
		c = *msg;
		i = 0;
		while (i++ < 8)
		{
			g_client.server_feedback = RESET;
			if (c & 0b10000000)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			while (waiting_server_feedback())
				usleep(10);
			c = c << 1;
		}
		msg++;
	}
}

static void	send_zero(pid_t server_pid)
{
	int	i;

	i = 8;
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
	send_msg(argv[2], ft_atoi(argv[1]));
	send_zero(ft_atoi(argv[1]));
	print_error_and_exit("Something went wrong: I didn't get SIGUSR2.");
	return (0);
}