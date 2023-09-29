/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 23:26:44 by slombard          #+#    #+#             */
/*   Updated: 2023/09/26 16:37:10 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum
{
	OFF,
	ON
}						e_server_state;

# define CONNECTION_CHECK_INTERVAL 100000 // Sleep duration in microseconds

typedef struct s_server
{
	struct sigaction	sa;
	char				char_accumulator;
	int					bit_index;
	e_server_state		connection;
}						t_server;

typedef struct s_client
{
	struct sigaction	sa1;
	struct sigaction	sa2;
	unsigned int		len;
	int					active;
	long long			sent_bit;
	long long			received_bit;
	int					waiter;
}						t_client;

#endif