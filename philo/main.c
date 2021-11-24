/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:17:02 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/23 17:17:41 by mdiallo          ###   ########.fr       */
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
			pthread_mutex_lock(&state->philo[i++].eat);
		j++;
	}
	display_message(&state->philo[0], TYPE_OVER);
	pthread_mutex_unlock(&state->somebody_dead);
	return ((void *) 0);
}

static void	*_manager_(void *_philo_)
{
	t_philo	*philo;

	philo = (t_philo *) _philo_;
	while (42)
	{
		pthread_mutex_lock(&philo->mutex);
		if (!philo->is_eating && get_time() > philo->limit)
		{
			display_message(philo, TYPE_DIED);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->state->somebody_dead);
			return ((void *) 0);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(1000);
	}
}

static void	*_loop_(void *_philo_)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *) _philo_;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->state->time_to_die;
	if (pthread_create(&tid, NULL, &_manager_, _philo_) != 0)
		return ((void *) 1);
	pthread_detach(tid);
	while (42)
	{
		take_forks(philo);
		eat(philo);
		clean_forks(philo);
		display_message(philo, TYPE_THINK);
	}
	return ((void *) 0);
}

static int	_threads_(t_state *state)
{
	int			i;
	pthread_t	tid;
	void		*philo;

	if (state->must_eat_count > 0)
	{
		if (pthread_create(&tid, NULL, &_manager_c, (void *) state) != 0)
			return (1);
		pthread_detach(tid);
	}
	i = 0;
	while (i < state->nb_philo)
	{
		philo = (void *)(&state->philo[i]);
		if (pthread_create(&tid, NULL, &_loop_, philo) != 0)
			return (1);
		pthread_detach(tid);
		usleep(100);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_state	state;

	if (argc < 5 || argc > 6)
		return (exit_error("error: bad arguments\n"));
	if (init(&state, argc, argv) != 0)
		return (all_clear(&state) && \
		exit_error("Error: initialization failed\n"));
	if (_threads_(&state))
		return (all_clear(&state) && exit_error("Error: started failed\n"));
	pthread_mutex_lock(&state.somebody_dead);
	pthread_mutex_unlock(&state.somebody_dead);
	all_clear(&state);
	return (0);
}
