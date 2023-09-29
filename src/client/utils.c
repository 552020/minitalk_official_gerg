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

void	error(char *error_msg)
{
	ft_printf("FAILED!\n");
	ft_printf("ERROR: %s\n", error_msg);
	ft_printf("Buuut %i  bytes were succesfully sent.\n", g_client.len);
	exit(0);
}

int	waiting_for_sig(void)
{
	if (g_client.waiter == 0)
		return (0);
	if (g_client.waiter++ > 100)
		error("Client didn't receive a signal from the server in time.");
	return (g_client.waiter);
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
