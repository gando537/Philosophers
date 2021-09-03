/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:16:22 by mdiallo           #+#    #+#             */
/*   Updated: 2021/07/21 16:04:51 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->fork_[philo->fork_l]);
	display_message(philo, TYPE_FORK);
	pthread_mutex_lock(&philo->state->fork_[philo->fork_r]);
	display_message(philo, TYPE_FORK);
}

void	clean_forks(t_philo *philo)
{
	display_message(philo, TYPE_SLEEP);
	pthread_mutex_unlock(&philo->state->fork_[philo->fork_l]);
	pthread_mutex_unlock(&philo->state->fork_[philo->fork_r]);
	usleep(philo->state->time_to_sleep * 1000);
}