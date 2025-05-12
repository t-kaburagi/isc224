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
    /* �Z�O�����gID�̐��� */
    char* file_path = "./key_data.dat";
    int id = 42;
    key_t key = ftok(file_path, id);
    if(-1 == key) {
                warn("Failed to acquire key" );
        return EXIT_FAILURE;
    }

    /* ���L�������ɃA�^�b�` */
    int segment_id  = shmget(key, 0, 0);
    char* shared_memory = (char*)(shmat(segment_id, 0, 0));
    printf ("shared memory attached at address %p\n", shared_memory);

    /* ���L�������̓ǂݍ��� */
    printf ("%s\n", shared_memory);

    /* ���L�������̃f�^�b�` */
    shmdt(shared_memory);

    return EXIT_SUCCESS;
}
