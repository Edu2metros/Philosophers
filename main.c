#include "philo.h"

long get_time()
{
    struct timeval current_time;
    long milliseconds;

    gettimeofday(&current_time, NULL);
    milliseconds = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
    return milliseconds;
}

void fill_info_data(t_data *data, char **argv)
{
    data->number_philos = ft_atoi(argv[1]);
    data->time_die = ft_atoi(argv[2]);
    data->time_eat = ft_atoi(argv[3]);
    data->time_sleep = ft_atoi(argv[4]);
    if (argv[5] != NULL)
        data->number_philos_eat = ft_atoi(argv[5]);
    else
        data->number_philos_eat = -1;
    data->flag_die = 0;
    data->time_init = get_time();
}

void init_philo_struct(t_data *data)
{
    int i;
    i = 0;
    data->philo = malloc(sizeof(t_philo) * data->number_philos);
    while (i < data->number_philos)
    {
        data->philo[i].philo_id = 0;
        data->philo[i].last_time_eat = 0;
        i++;
    }
}

void forks_init(t_data *data)
{
    int i = 0;
    data->forks = malloc(sizeof(int) * data->number_philos);
    while (i < data->number_philos)
        data->forks[i++] = 0;
    i = 0;
    data->fork_m = malloc(sizeof(pthread_mutex_t) * data->number_philos);
    while (i < data->number_philos)
        pthread_mutex_init(&data->fork_m[i++], NULL);
}

t_data **control_struct(void)
{
    static t_data *result;
    return (&result);
}

t_data *init(char **argv)
{
    t_data *data;
    data = malloc(sizeof(t_data));
    fill_info_data(data, argv);
    init_philo_struct(data);
    forks_init(data);
    *control_struct() = data;
    return (data);
}


void print_instance(t_data *data, int id, char *msg)
{
    long time;
    if (data->flag_die == 1)
        return;
    time = get_time() - data->time_init;
    printf("%ld %d %s\n", time, id + 1, msg);
}

void philo_eat(t_data *data, int id)
{
    int left_fork = id;
    int right_fork = (id + 1) % data->number_philos;
    if (id % 2 == 0)
    {
        pthread_mutex_lock(&data->fork_m[right_fork]);
        pthread_mutex_lock(&data->fork_m[left_fork]);
    }
    else
    {
        pthread_mutex_lock(&data->fork_m[left_fork]);
        pthread_mutex_lock(&data->fork_m[right_fork]);
    }

    print_instance(data, id, "has taken a fork");
    data->philo[id].last_time_eat = get_time();
    print_instance(data, id, "is eating");
    usleep(data->time_eat * 1000);
    pthread_mutex_unlock(&data->fork_m[left_fork]);
    pthread_mutex_unlock(&data->fork_m[right_fork]);
}


void philo_sleep_n_think(t_data *data, int id)
{
    print_instance(data, id, "is sleeping");
    usleep(data->time_sleep * 1000);
    print_instance(data, id, "is thinking");
}

void *routine(void *arg)
{
    int id = *(int *)arg;
    t_data *data = *control_struct();

    while (data->flag_die == 0)
    {
        if (id % 2 == 0)
            usleep(300);
        if (data->flag_die == 0)
            philo_eat(data, id);
        if (data->flag_die == 0)
            philo_sleep_n_think(data, id);
    }
    return NULL;
}


void wait_all_threads(int philo_len, pthread_t *thread_id)
{
    for (int i = 0; i < philo_len; i++)
    {
        pthread_join(thread_id[i], NULL);
    }
}
int philo_dead(t_philo *philo, t_data *data)
{
    long die;
    die = get_time() - philo->last_time_eat;
    if(die >= data->time_die)
    {
        printf("morreu\n");
        printf("%ld\n", die);
        data->flag_die = 1;
        return(1);
    }
    return(0);
}

void big_brother(t_data *data)
{
    if (data->number_philos == 1)
        return;

    while (1)
    {
        for (int id = 0; id < data->number_philos; id++)
        {
            if (philo_dead(&data->philo[id], data))
                return;
        }
    }
}

void init_threads(t_data *data)
{
    pthread_t thread_id[data->number_philos];

    for (int i = 0; i < data->number_philos && data->flag_die == 0; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&thread_id[i], NULL, routine, id);
    }
    big_brother(data);
    wait_all_threads(data->number_philos, thread_id);
}


void philosophers(char **argv)
{
    t_data *data;
    data = init(argv);
    init_threads(data);
}

int main(int argc, char **argv)
{
    if (!check_args(argc, argv))
        return (EXIT_FAILURE);
    philosophers(argv);
    return (EXIT_SUCCESS);
}