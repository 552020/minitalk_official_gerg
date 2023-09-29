/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:35:53 by slombard          #+#    #+#             */
/*   Updated: 2023/09/26 16:47:41 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

extern t_client	g_client;

void	print_error_and_exit(char *error_msg)
{
	ft_printf("FAILED!\n");
	ft_printf("ERROR: %s\n", error_msg);
	exit(0);
}

int	waiting_server_feedback(void)
{
	static int	waiter;

	if (g_client.server_feedback == RECEIVED)
	{
		waiter = 0;
		return (0);
	}
	if (waiter++ > WAITER_FEEDBACK_ATTEMPTS)
		print_error_and_exit("Bit feedback failed.\n");
	return (g_client.server_feedback);
}

void	args_check(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("No no no! Usage is: ./client <server pid> <message>\n");
		exit(0);
	}
	else if (!(ft_atoi(argv[1]) > 0))
	{
		ft_printf("No no no! Please pay attention while copying the PID of the server!\n");
		exit(0);
	}
}
