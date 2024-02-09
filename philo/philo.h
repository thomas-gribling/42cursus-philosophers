/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:15:48 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/09 09:57:55 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define MSG_FORK "%04u %d has taken a fork\n"
# define MSG_EAT "%04u %d is eating\n"
# define MSG_SLEEP "%04u %d is sleeping\n"
# define MSG_THINK "%04u %d is thinking\n"
# define MSG_DIE "%04u %d died\n"

typedef struct s_common
{
	long			n_philo;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			n_eat;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	unsigned int	start;
	int				dead;
}					t_common;

typedef struct s_philo
{
	int				i;
	int				eating;
	unsigned int	last_eat;
	pthread_t		brain;
	pthread_mutex_t	lf;
	pthread_mutex_t	*rf;
	t_common		*all;
}					t_philo;

void			put_message(char *msg, t_philo *phi);
unsigned int	get_time(void);
void			ft_usleep(long ms);

long			ft_atol(char *s);
int				ft_strcmp(char *s1, char *s2);

#endif