/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:15:48 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/05 09:04:48 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define SLEEPING 0
# define THINKING 1
# define EATING 2

# define MSG_BORN "%04u %d is born\n"
# define MSG_TOOK_FORK "%04u %d has taken a fork\n"
# define MSG_EATING "%04u %d is eating\n"
# define MSG_SLEEP "%04u %d is sleeping\n"
# define MSG_THINK "%04u %d is thinking\n"
# define MSG_DIED "%04u %d has died\n"

typedef struct s_philo
{
	int				state;
	pthread_t		t;
	pthread_mutex_t	fork;
}				t_philo;

typedef struct s_stats
{
	long		n_philos;
	long		n_eat;
	long		t_die;
	long		t_eat;
	long		t_sleep;
	int			i;
	unsigned	time_start;
	t_philo		**philos;	
}				t_stats;

void		create_philos(t_stats *st);

unsigned	get_time(void);
void		put_msg(t_stats *st, char *msg, int n);

long		ft_atol(char *s);

#endif