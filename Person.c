#include "global.h"
#include "Person.h"

void take_personInput()
{
    for (int i = 0; i < num_groups; i++)
    {
        groups[i].groupID = i;

        int no_of_people;
        scanf("%d", &no_of_people);

        groups[i].no_of_people = no_of_people;
        groups[i].person_in_grp = (person_ADT *)malloc(sizeof(person_ADT) * no_of_people);
        for (int j = 0; j < no_of_people; j++)
        {
            scanf("%s %c %d %d %d", groups[i].person_in_grp[j].name, &groups[i].person_in_grp[j].fanof_H_A_N, &groups[i].person_in_grp[j].reach_time, &groups[i].person_in_grp[j].patience_time, &groups[i].person_in_grp[j].enrage_value);

            // printf("_name=%s_ %c %d %d %d\n", groups[i].person_in_grp[j].name, groups[i].person_in_grp[j].fanof_H_A_N, groups[i].person_in_grp[j].reach_time, groups[i].person_in_grp[j].patience_time, groups[i].person_in_grp[j].enrage_value);

            groups[i].person_in_grp[j].groupID = i;
            groups[i].person_in_grp[j].is_at_exit = false;
            groups[i].person_in_grp[j].is_enraged = false;
            groups[i].person_in_grp[j].seat_receive_time = INVALID;
            groups[i].person_in_grp[j].seat_receive_zone = INVALID;
            groups[i].person_in_grp[j].seat_receive_zone = INVALID;
        }
    }
}
void create_personThread()
{
    for (int i = 0; i < num_groups; i++)
    {
        for (int j = 0; j < groups[i].no_of_people; j++)
        {
            if (pthread_create(&groups[i].person_in_grp[j].personThread, NULL, person_thread_func, &groups[i].person_in_grp[j]) != 0)
            {
                printf("Error creating personThread\n");
                exit(1);
            }
            pthread_mutex_init(&groups[i].person_in_grp[j].person_mutex, NULL);
        }
    }
}
void join_personThread()
{
    for (int i = 0; i < num_groups; i++)
    {
        for (int j = 0; j < groups[i].no_of_people; j++)
        {
            pthread_join(groups[i].person_in_grp[j].personThread, NULL);
            pthread_mutex_destroy(&groups[i].person_in_grp[j].person_mutex);
        }
    }
}
struct timespec get_absoluteTime_1(int given_time)
{
    int time_now = time(NULL) - simulation_startTime;

    struct timeval val;
    struct timespec spec;

    int timeInMs = (given_time - (time_now + 1)) * 1000;
    gettimeofday(&val, NULL);

    spec.tv_sec = time(NULL) + timeInMs / 1000;
    spec.tv_nsec = val.tv_usec * 1000 + 1000 * 1000 * (timeInMs % 1000);
    spec.tv_sec += spec.tv_nsec / (1000 * 1000 * 1000);
    spec.tv_nsec %= (1000 * 1000 * 1000);
}
struct timespec get_absoluteTime_2(int given_time)
{
    int time_now = time(NULL) - simulation_startTime;

    struct timeval val;
    struct timespec spec;

    int timeInMs = (given_time - (time_now)) * 1000;
    gettimeofday(&val, NULL);

    spec.tv_sec = time(NULL) + timeInMs / 1000;
    spec.tv_nsec = val.tv_usec * 1000 + 1000 * 1000 * (timeInMs % 1000);
    spec.tv_sec += spec.tv_nsec / (1000 * 1000 * 1000);
    spec.tv_nsec %= (1000 * 1000 * 1000);
}
int allocate_seat(person_ADT *person)
{
    char fanof_H_A_N = person->fanof_H_A_N;
    if (fanof_H_A_N == 'H')
    {
        pthread_mutex_lock(&zone_mutex);
        if (zone_H_capacity > 0)
        {
            int time_now = time(NULL) - simulation_startTime;

            zone_H_capacity--;
            person->seat_receive_zone = 'H';

            person->seat_receive_time = time_now;
            WHITE
            printf("t = %ld: %s has got a seat in zone H\n", time(NULL) - simulation_startTime, person->name);
            RESET
        }
        if (person->seat_receive_time != INVALID)
        {
            pthread_mutex_unlock(&zone_mutex);
            return INVALID;
        }
        if (zone_N_capacity > 0)
        {
            int time_now = time(NULL) - simulation_startTime;

            zone_N_capacity--;
            person->seat_receive_zone = 'H';

            person->seat_receive_time = time_now;
            WHITE
            printf("t = %ld: %s has got a seat in zone N\n", time(NULL) - simulation_startTime, person->name);
            RESET
        }
        if (person->seat_receive_time != INVALID)
        {
            pthread_mutex_unlock(&zone_mutex);
            return INVALID;
        }
        pthread_mutex_unlock(&zone_mutex);
    }
    else if (fanof_H_A_N == 'A')
    {
        pthread_mutex_lock(&zone_mutex);
        if (zone_A_capacity > 0)
        {
            int time_now = time(NULL) - simulation_startTime;

            zone_A_capacity--;
            person->seat_receive_zone = 'A';

            person->seat_receive_time = time_now;
            WHITE
            printf("t = %ld: %s has got a seat in zone A\n", time(NULL) - simulation_startTime, person->name);
            RESET
        }
        if (person->seat_receive_time != INVALID)
        {
            pthread_mutex_unlock(&zone_mutex);
            return INVALID;
        }
        pthread_mutex_unlock(&zone_mutex);
    }
    else if (fanof_H_A_N == 'N')
    {
        pthread_mutex_lock(&zone_mutex);
        if (zone_H_capacity > 0)
        {
            int time_now = time(NULL) - simulation_startTime;

            zone_H_capacity--;
            person->seat_receive_zone = 'H';

            person->seat_receive_time = time_now;
            WHITE
            printf("t = %ld: %s has got a seat in zone H\n", time(NULL) - simulation_startTime, person->name);
            RESET
        }
        if (person->seat_receive_time != INVALID)
        {
            pthread_mutex_unlock(&zone_mutex);
            return INVALID;
        }
        if (zone_N_capacity > 0)
        {
            int time_now = time(NULL) - simulation_startTime;

            zone_N_capacity--;
            person->seat_receive_zone = 'H';

            person->seat_receive_time = time_now;
            WHITE
            printf("t = %ld: %s has got a seat in zone N\n", time(NULL) - simulation_startTime, person->name);
            RESET
        }
        if (person->seat_receive_time != INVALID)
        {
            pthread_mutex_unlock(&zone_mutex);
            return INVALID;
        }
        if (zone_A_capacity > 0)
        {
            int time_now = time(NULL) - simulation_startTime;

            zone_A_capacity--;
            person->seat_receive_zone = 'A';

            person->seat_receive_time = time_now;
            WHITE
            printf("t = %ld: %s has got a seat in zone A\n", time(NULL) - simulation_startTime, person->name);
            RESET
        }
        if (person->seat_receive_time != INVALID)
        {
            pthread_mutex_unlock(&zone_mutex);
            return INVALID;
        }
        pthread_mutex_unlock(&zone_mutex);
    }
    else
    {
        printf("Error in fanof_H_A_N\n");
        return INVALID;
        // exit(1);
    }
    return VALID;
}
int check_if_seatAllocated(person_ADT *person)
{
    if (person->seat_receive_time == INVALID)
    {
        pthread_mutex_lock(&zone_mutex);

        struct timespec abs_time = get_absoluteTime_1(person->patience_time + person->reach_time);

        if (pthread_cond_timedwait(&zone_cond, &zone_mutex, &abs_time) == 0)
        {
            pthread_mutex_unlock(&zone_mutex);
            return VALID;
        }
        else
        {
            pthread_mutex_unlock(&zone_mutex);

            int time_now = time(NULL) - simulation_startTime;
            int person_leave_time = person->reach_time + person->patience_time;

            if (time_now > person_leave_time)
            {
                PURPLE
                printf("%s could not get a seat\n", person->name);
                RESET
                return INVALID;
            }
        }
    }
    return VALID;
}
void leave_dueTo_badPerformance(person_ADT *person)
{
    if (person->seat_receive_time == INVALID)
    {
        return;
    }
    else
    {
        if (person->fanof_H_A_N == 'N')
        {
            sleep(spectating_time);
        }
        else if (person->fanof_H_A_N == 'H')
        {
            while (person->enrage_value > num_of_goalsBy_A)
            {
                pthread_mutex_lock(&scoreboard_mutex);
                struct timespec abs_time = get_absoluteTime_2(spectating_time + person->seat_receive_time);

                if (pthread_cond_timedwait(&scoreboard_cond, &scoreboard_mutex, &abs_time) == 0)
                {
                    pthread_mutex_unlock(&scoreboard_mutex);
                    continue;
                }
                else
                {
                    pthread_mutex_unlock(&scoreboard_mutex);
                    break;
                }
                pthread_mutex_unlock(&scoreboard_mutex);
            }
            if (person->enrage_value <= num_of_goalsBy_A)
            {
                person->is_enraged = true;
                printf("%d - E, %d - A, %d - H\n", person->enrage_value, num_of_goalsBy_A, num_of_goalsBy_H);
                RED
                    printf("t = %ld: %s is leaving due to the bad defensive performance of his team\n", time(NULL) - simulation_startTime, person->name);
                RESET
                return;
            }
        }
        else if (person->fanof_H_A_N == 'A')
        {
            while (person->enrage_value > num_of_goalsBy_H)
            {
                pthread_mutex_lock(&scoreboard_mutex);
                struct timespec abs_time = get_absoluteTime_2(spectating_time + person->seat_receive_time);

                if (pthread_cond_timedwait(&scoreboard_cond, &scoreboard_mutex, &abs_time) == 0)
                {
                    pthread_mutex_unlock(&scoreboard_mutex);
                    continue;
                }
                else
                {
                    pthread_mutex_unlock(&scoreboard_mutex);
                    break;
                }
                pthread_mutex_lock(&scoreboard_mutex);
            }
            if (person->enrage_value <= num_of_goalsBy_H)
            {
                person->is_enraged = true;
                RED
                    printf("t = %ld: %s is leaving due to the bad defensive performance of his team\n", time(NULL) - simulation_startTime, person->name);
                RESET
                return;
            }
        }
        else
        {
            RED
                printf("Error in leave_dueTo_badPerformance\n");
            RESET
            // exit(1);
        }
    }
}
void free_seat(person_ADT *person)
{
    int time_now = time(NULL) - simulation_startTime;

    pthread_mutex_lock(&zone_mutex);
    if (person->seat_receive_zone == 'H')
    {
        zone_H_capacity++;
        MAGENTA
        printf("t = %d: %s watched the match for %d seconds and is leaving\n", time_now, person->name, time_now);
        RESET
    }
    else if (person->seat_receive_zone == 'A')
    {
        zone_A_capacity++;
        MAGENTA
        printf("t = %d: %s watched the match for %d seconds and is leaving\n", time_now, person->name, time_now);
        RESET
    }
    else if (person->seat_receive_zone == 'N')
    {
        zone_N_capacity++;
        MAGENTA
        printf("t = %d: %s watched the match for %d seconds and is leaving\n", time_now, person->name, time_now);
        RESET
    }
    else
    {
        RED
            printf("Error in free_seat\n");
        RESET
        exit(1);
    }
    pthread_cond_broadcast(&zone_cond);
    pthread_mutex_unlock(&zone_mutex);

    person->is_at_exit = true;

    pthread_mutex_lock(&group_mutex);
    groups[person->groupID].no_of_people_at_exit++;

    CYAN
    printf("t = %ld: %s is waiting for their friends at the exit\n", time(NULL) - simulation_startTime, person->name);
    RESET

    if (groups[person->groupID].no_of_people_at_exit == groups[person->groupID].no_of_people)
    {
        GREEN
        printf("t = %ld: Group %d is leaving for dinner\n", time(NULL) - simulation_startTime, person->groupID + 1);
        RESET
    }
    pthread_cond_broadcast(&group_cond);
    pthread_mutex_unlock(&group_mutex);
}
void *person_thread_func(void *arg)
{

    person_ADT *person = (person_ADT *)arg;
    int reach_time = person->reach_time;

    sleep(reach_time);
    GREEN
    printf("t = %ld: %s has reached the stadium\n", time(NULL) - simulation_startTime, person->name);
    RESET

    while (true)
    {
        // CHANGE
        sleep(1);
        if (allocate_seat(person) == INVALID)
            break;

        // CHANGE
        sleep(1);
        if (check_if_seatAllocated(person) == VALID)
            continue;
        else
            return NULL;
    }

    leave_dueTo_badPerformance(person);
    free_seat(person);
    return NULL;
}