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

/* SERVER */

typedef enum e_server_state
{
	OFF,
	ON
}						t_server_state;

# define CONNECTION_CHECK_INTERVAL 100000 // Sleep duration in microseconds

typedef struct s_server
{
	struct sigaction	sa;
	char				char_accumulator;
	int					bit_index;
	t_server_state		connection;
}						t_server;

/* CLIENT */

# define WAITER_FEEDBACK_ATTEMPTS 100

typedef enum e_server_feedback
{
	RECEIVED = 0,
	RESET = 1
}						t_server_feedback;

typedef struct s_client
{
	struct sigaction	sa;
	unsigned int		len;
	int					active;
	long long			sent_bit;
	long long			received_bit;
	t_server_feedback	server_feedback;
}						t_client;

#endif