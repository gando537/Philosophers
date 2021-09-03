/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:10:47 by mdiallo           #+#    #+#             */
/*   Updated: 2021/08/13 15:12:46 by mdiallo          ###   ########.fr       */
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
	int		i;
	char	semaphore[255];

	sem_unlink(SEMAPHORE_FORK);
	sem_unlink(SEMAPHORE_WRITE);
	sem_unlink(SEMAPHORE_DEAD);
	sem_unlink(SEMAPHORE_DEADW);
	if (state->philo)
	{
		i = 0;
		while (i < state->nb_philo)
		{
			make_semaphore_name(SEMAPHORE_PHILO, (char*)semaphore, i);
			sem_unlink(semaphore);
			make_semaphore_name(SEMAPHORE_PHILOEAT, (char*)semaphore, i++);
			sem_unlink(semaphore);
		}
		free(state->philo);
	}
	return (1);
}