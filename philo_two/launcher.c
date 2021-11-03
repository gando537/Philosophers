/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:52:06 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/03 17:16:52 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philosopher *philo)
{
	t_rules *rules;

	rules = philo->rules;
	sem_wait(rules->forks);
	action_print(rules, philo->id, "\033[36m has taken a fork\033[00m");
	sem_wait(rules->forks);
	action_print(rules, philo->id, "\033[36m has taken a fork\033[00m");
	sem_wait(rules->meal_check);
	action_print(rules, philo->id, "\033[33m is eating\033[00m");
	philo->t_last_meal = timestamp();
	sem_post(rules->meal_check);
	smart_sleep(rules->time_eat, rules);
	(philo->x_ate)++;
	sem_post(rules->forks);
	sem_post(rules->forks);
}

void	*p_thread(void *void_philosopher)
{
	int				i;
	t_philosopher	*philo;
	t_rules			*rules;

	i = 0;
	philo = (t_philosopher *)void_philosopher;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(15000);
	while (!(rules->dieded))
	{
		philo_eats(philo);
		if (rules->all_ate)
			break ;
		action_print(rules, philo->id, "\033[32m is sleeping\033[00m");
		smart_sleep(rules->time_sleep, rules);
		action_print(rules, philo->id, "\033[35m is thinking\033[00m");
		i++;
	}
	return (NULL);
}

void	exit_launcher(t_rules *rules, t_philosopher *philos)
{
	int i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(philos[i].thread_id, NULL);
	sem_close(rules->forks);
	sem_close(rules->writing);
	sem_close(rules->meal_check);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_mealcheck");
}

void	death_checker(t_rules *r, t_philosopher *p)
{
	int i;

	while (!(r->all_ate))
	{
		i = -1;
		while (++i < r->nb_philo && !(r->dieded))
		{
			sem_wait(r->meal_check);
			if (time_diff(p[i].t_last_meal, timestamp()) > r->time_death)
			{
				action_print(r, i, "\033[31m died\033[00m");
				r->dieded = 1;
			}
			sem_post(r->meal_check);
			usleep(100);
		}
		if (r->dieded)
			break ;
		i = 0;
		while (r->nb_eat != -1 && i < r->nb_philo && p[i].x_ate >= r->nb_eat)
			i++;
		if (i == r->nb_philo)
			r->all_ate = 1;
	}
}

int		launcher(t_rules *rules)
{
	int				i;
	t_philosopher	*phi;

	i = 0;
	phi = rules->philosophers;
	rules->first_timestamp = timestamp();
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, p_thread, &(phi[i])))
			return (1);
		phi[i].t_last_meal = timestamp();
		i++;
	}
	death_checker(rules, rules->philosophers);
	exit_launcher(rules, phi);
	return (0);
}
