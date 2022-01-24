/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:16:36 by mdiallo           #+#    #+#             */
/*   Updated: 2022/01/24 15:44:55 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_mutexes(t_state *state)
{
	int	i;

	pthread_mutex_init(&state->write_, NULL);
	pthread_mutex_init(&state->somebody_dead, NULL);
	pthread_mutex_lock(&state->somebody_dead);
	state->fork_ = (pthread_mutex_t *)malloc(sizeof(*(state->fork_)) * \
		state->nb_philo);
	if (!(state->fork_))
		return (1);
	i = 0;
	while (i < state->nb_philo)
		pthread_mutex_init(&state->fork_[i++], NULL);
	return (0);
}

static void	init_philos(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->nb_philo)
	{
		state->philo[i].pos = i + 1;
		state->philo[i].is_eating = 0;
		state->philo[i].fork_l = i;
		state->philo[i].fork_r = (i + 1) % state->nb_philo;
		state->philo[i].state = state;
		pthread_mutex_init(&state->philo[i].mutex, NULL);
		pthread_mutex_init(&state->philo[i].eat, NULL);
		pthread_mutex_lock(&state->philo[i].eat);
		i++;
	}
}

int	init(t_state *state, int argc, char **argv)
{
	state->nb_philo = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		state->must_eat_count = ft_atoi(argv[5]);
	else
		state->must_eat_count = 0;
	state->start = get_time();
	if (state->nb_philo > 200 || state->time_to_eat < 60
		|| state->time_to_die < 60 || state->time_to_sleep < 60
		|| state->must_eat_count < 0)
		return (1);
	state->fork_ = NULL;
	state->philo = (t_philo *)malloc(sizeof(*(state->philo)) * state->nb_philo);
	if (!(state->philo))
		return (1);
	init_philos(state);
	return (init_mutexes(state));
}
