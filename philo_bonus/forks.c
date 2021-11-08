/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:16:22 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/08 17:36:29 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->state->fork_);
	display_message(philo, TYPE_FORK);
	sem_wait(philo->state->fork_);
	display_message(philo, TYPE_FORK);
}

void	clean_forks(t_philo *philo)
{
	display_message(philo, TYPE_SLEEP);
	sem_post(philo->state->fork_);
	sem_post(philo->state->fork_);
	usleep(philo->state->time_to_sleep * 1000);
}
