/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:17:02 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/24 17:33:20 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*_manager_c(void *_state_)
{
	t_state	*state;
	int		i;
	int		j;

	state = (t_state *)_state_;
	j = 0;
	while (j < state->must_eat_count)
	{
		i = 0;
		while (i < state->nb_philo)
			sem_wait(state->philo[i++].eat);
		j++;
	}
	display_message(&state->philo[0], TYPE_OVER);
	sem_post(state->somebody_dead);
	return ((void *) 0);
}

static void	*_manager_(void *_philo_)
{
	t_philo	*philo;

	philo = (t_philo *) _philo_;
	while (42)
	{
		sem_wait(philo->mutex);
		if (get_time() > philo->limit)
		{
			display_message(philo, TYPE_DIED);
			sem_post(philo->mutex);
			sem_post(philo->state->somebody_dead);
			return ((void *) 0);
		}
		sem_post(philo->mutex);
		usleep(1000);
	}
}

void	*_loop_(void *_philo_)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *) _philo_;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->state->time_to_die;
	if (pthread_create(&tid, NULL, &_manager_, _philo_) != 0)
		exit (1);
	pthread_detach(tid);
	while (42)
	{
		sem_wait(philo->state->frk);
		take_forks(philo);
		sem_post(philo->state->frk);
		eat(philo);
		clean_forks(philo);
		display_message(philo, TYPE_THINK);
	}
	exit (0);
}

static int	_threads_(t_state *state)
{
	pthread_t	tid;

	if (state->must_eat_count > 0)
	{
		if (pthread_create(&tid, NULL, &_manager_c, (void *) state) != 0)
			return (1);
		pthread_detach(tid);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	t_state	state;

	if (argc < 5 || argc > 6)
		return (exit_error("error: bad arguments\n"));
	if (init(&state, argc, argv) != 0)
		return (all_clear(&state) && \
		exit_error("Error: initialization failed\n"));
	if (_threads_(&state) || start_process(&state))
		return (all_clear(&state) && exit_error("Error: started failed\n"));
	sem_wait(state.somebody_dead);
	i = 0;
	while (i < state.nb_philo)
		kill(state.philo[i++].pid, SIGKILL);
	all_clear(&state);
	return (0);
}
