#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *__buf;
};

enum SEMAPHORE_OPERATION
{
    UNLOCK = -1,
    WAIT = 0,
    LOCK = 1,
};

int main()
{
    /* セマフォの確保 */
    const key_t key = 112;
    int sem_flags = 0666;
    int sem_id = semget(key, 1, sem_flags);
    if(-1 == sem_id)
    {
        perror( "Failed to acquire semapore" );
        return EXIT_FAILURE;
    }

    perror( "Unlock semaphore" );

    /* セマフォにポスト */
    struct sembuf operations[1];
    operations[0].sem_num = 0;
    operations[0].sem_op = UNLOCK;
    operations[0].sem_flg = SEM_UNDO;
    semop(sem_id, operations, 1);

    return EXIT_SUCCESS;
}

