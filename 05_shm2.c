#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main ()
{
    /* セグメントIDの生成 */
    char* file_path = "./key_data.dat";
    int id = 42;
    key_t key = ftok(file_path, id);
    if(-1 == key) {
                warn("Failed to acquire key" );
        return EXIT_FAILURE;
    }

    /* 共有メモリにアタッチ */
    int segment_id  = shmget(key, 0, 0);
    char* shared_memory = (char*)(shmat(segment_id, 0, 0));
    printf ("shared memory attached at address %p\n", shared_memory);

    /* 共有メモリの読み込み */
    printf ("%s\n", shared_memory);

    /* 共有メモリのデタッチ */
    shmdt(shared_memory);

    return EXIT_SUCCESS;
}
