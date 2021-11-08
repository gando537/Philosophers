/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:10:47 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/08 17:22:38 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	exit_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (0);
}

int	all_clear(t_state *state)
{
	int	i;

	if (state->fork_)
	{
		i = 0;
		while (i < state->nb_philo)
			pthread_mutex_destroy(&state->fork_[i++]);
		free(state->fork_);
	}
	if (state->philo)
	{
		i = 0;
		while (i < state->nb_philo)
		{
			pthread_mutex_destroy(&state->philo[i].mutex);
			pthread_mutex_destroy(&state->philo[i++].eat);
		}
		free(state->philo);
	}
	pthread_mutex_destroy(&state->write_);
	pthread_mutex_destroy(&state->somebody_dead);
	return (1);
}
