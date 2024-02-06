/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:15:48 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/06 10:11:56 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_common
{
	long			n_philo;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			n_eat;
	pthread_mutex_t	write_mutex;
	unsigned int	start;
}				t_common;

typedef struct s_philo
{
	int				i;
	pthread_t		brain;
	pthread_mutex_t	lf;
	pthread_mutex_t	*rf;
	t_common		*all;
}					t_philo;

unsigned int	get_time(void);
void			ft_usleep(long ms);
long			ft_atol(char *s);

#endif