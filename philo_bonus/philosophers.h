/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:16:42 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/08 17:37:18 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

# define SEMAPHORE_FORK		"pSemaphoreFork"
# define SEMAPHORE_WRITE	"pSemaphoreWrite"
# define SEMAPHORE_DEAD		"pSemaphoreDead"
# define SEMAPHORE_DEADW	"pSemaphoreDeadWrite"
# define SEMAPHORE_PHILO	"pSemaphorePhilo"
# define SEMAPHORE_PHILOEAT	"pSemaphorePhiloEat"

# define TYPE_EAT 	0
# define TYPE_SLEEP 1
# define TYPE_FORK 	2
# define TYPE_THINK	3
# define TYPE_DIED 	4
# define TYPE_OVER 	5

struct	s_state;

typedef struct s_philo
{
	pid_t			pid;
	int				pos;
	int				is_eating;
	int				fork_l;
	int				fork_r;
	int				eat_c;
	u_int64_t		limit;
	u_int64_t		last_eat;
	struct s_state	*state;
	sem_t			*mutex;
	sem_t			*eat;
}t_philo;

typedef struct s_state
{
	int			nb_philo;
	int			must_eat_count;
	u_int64_t	time_to_die;
	u_int64_t	time_to_eat;
	u_int64_t	time_to_sleep;
	u_int64_t	start;
	t_philo		*philo;
	sem_t		*fork_;
	sem_t		*write_;
	sem_t		*somebody_dead;
	sem_t		*dead_write;
}t_state;

int			ft_strlen(char *str);
int			ft_atoi(char *str);
void		ft_putnbr_fd(uint64_t n, int fd);
int			ft_strcpy(char *dst, const char *src);
uint64_t	get_time(void);
void		eat(t_philo *philo);
int			init(t_state *state, int argc, char **argv);
int			exit_error(char *str);
sem_t		*ft_sem_open(char const *name, int value);
void		*_loop_(void *_philo_);
char		*make_semaphore_name(char const *base, char *buffer, int position);
int			start_process(t_state *state);
int			all_clear(t_state *state);
void		display_message(t_philo *philo, int type);
void		take_forks(t_philo *philo);
void		clean_forks(t_philo *philo);

#endif