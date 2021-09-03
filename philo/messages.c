/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:16:49 by mdiallo           #+#    #+#             */
/*   Updated: 2021/08/06 19:38:41 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static char	*get_message(int type)
{
	if (type == TYPE_EAT)
		return (" is eating\n");
	else if (type == TYPE_SLEEP)
		return (" is sleeping\n");
	else if (type == TYPE_FORK)
		return (" has taken a fork\n");
	else if (type == TYPE_THINK)
		return (" is thinking\n");
	else if (type == TYPE_OVER)
		return ("must eat count reached\n");
	return (" died\n");
}

void	display_message(t_philo *philo, int type)
{
	static int	done;
	
	done = 0;
	pthread_mutex_lock(&philo->state->write_);
	if (!done)
	{
		ft_putnbr_fd(get_time(), 1);
		write(1, "\t", 1);
		if (type != TYPE_OVER)
			ft_putnbr_fd(philo->pos, 1);
		if (type >= TYPE_DIED)
			done = 1;
		write(1, get_message(type), ft_strlen(get_message(type)));
	}
	pthread_mutex_unlock(&philo->state->write_);
}
