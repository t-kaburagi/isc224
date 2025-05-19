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
    int sem_id = semget(key, 1, sem_flags | IPC_CREAT);
    if(-1 == sem_id)
    {
        perror( "Failed to acquire semapore" );
        return EXIT_FAILURE;
    }

    /* セマフォの初期化 */
    union semun argument;
    unsigned short values[1];
    values[0] = 1;
    argument.array = values;
    semctl(sem_id, 0, SETALL, argument);

    /* プロセスBの実行を待つ */
    perror( "Waiting for post operation..." );
    struct sembuf operations[1];
    operations[0].sem_num = 0;
    operations[0].sem_op = WAIT;
    operations[0].sem_flg = SEM_UNDO;
    semop(sem_id, operations, 1);

    /* セマフォの解放 */
    int result = semctl(sem_id, 1, IPC_RMID, NULL);
    if(-1 == result)
    {
        perror(  "Failed to close semaphore" );
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

