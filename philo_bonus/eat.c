/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:15:55 by mdiallo           #+#    #+#             */
/*   Updated: 2021/08/13 15:07:54 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->mutex);
	philo->is_eating = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->state->time_to_die;
	display_message(philo, TYPE_EAT);
	usleep(philo->state->time_to_eat * 1000);
	philo->eat_c++;
	philo->is_eating = 0;
	sem_post(philo->mutex);
	sem_post(philo->eat);
}