/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:16:36 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/08 17:47:11 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_semaphores(t_state *state)
{
	sem_unlink(SEMAPHORE_FORK);
	sem_unlink(SEMAPHORE_WRITE);
	sem_unlink(SEMAPHORE_DEAD);
	sem_unlink(SEMAPHORE_DEADW);
	state->fork_ = ft_sem_open(SEMAPHORE_FORK, state->nb_philo);
	state->write_ = ft_sem_open(SEMAPHORE_WRITE, 1);
	state->somebody_dead = ft_sem_open(SEMAPHORE_DEAD, 0);
	state->dead_write = ft_sem_open(SEMAPHORE_DEADW, 1);
	if (!(state->fork_) || !(state->write_) || !(state->somebody_dead)
		|| !(state->dead_write))
		return (1);
	return (0);
}

static int	init_philos(t_state *state)
{
	int		i;
	char	semaphore[255];

	i = 0;
	while (i < state->nb_philo)
	{
		state->philo[i].pos = i + 1;
		state->philo[i].is_eating = 0;
		state->philo[i].fork_l = i;
		state->philo[i].fork_r = (i + 1) % state->nb_philo;
		state->philo[i].eat_c = 0;
		state->philo[i].state = state;
		make_semaphore_name(SEMAPHORE_PHILO, (char *) semaphore, i);
		sem_unlink(semaphore);
		state->philo[i].mutex = ft_sem_open(semaphore, 1);
		if (!(state->philo[i].mutex))
			return (1);
		make_semaphore_name(SEMAPHORE_PHILOEAT, (char *) semaphore, i);
		sem_unlink(semaphore);
		state->philo[i].eat = ft_sem_open(semaphore, 0);
		if (!(state->philo[i].eat))
			return (1);
		i++;
	}
	return (0);
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
	if (state->nb_philo > 200 || state->time_to_eat < 60
		|| state->time_to_die < 60 || state->time_to_sleep < 60
		|| state->must_eat_count < 0)
		return (1);
	state->fork_ = NULL;
	state->philo = (t_philo *)malloc(sizeof(*(state->philo)) * state->nb_philo);
	if (!(state->philo))
		return (1);
	if (init_philos(state))
		return (1);
	return (init_semaphores(state));
}
