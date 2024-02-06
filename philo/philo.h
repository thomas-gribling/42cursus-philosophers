/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:15:48 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/06 11:33:26 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define MSG_FORK "%04d %d has taken a fork\n"
# define MSG_EAT "%04d %d is eating\n"
# define MSG_SLEEP "%04d %d is sleeping\n"
# define MSG_THINK "%04d %d is thinking\n"
# define MSG_DIE "%04d %d died\n"

typedef struct s_common
{
	long			n_philo;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			n_eat;
	pthread_mutex_t	write_mutex;
	unsigned int	start;
	int				dead;
}					t_common;

typedef struct s_philo
{
	int				i;
	pthread_t		brain;
	pthread_mutex_t	lf;
	pthread_mutex_t	*rf;
	t_common		*all;
}					t_philo;

void			put_message(char *msg, t_philo phi);
unsigned int	get_time(void);
void			ft_usleep(long ms);

long			ft_atol(char *s);

#endif