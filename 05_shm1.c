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
	printf ("key as %d\n", key);

    /* �Z�O�����g�̊��� */
    int shared_segment_size = 0x6400;
    int segment_id = shmget(key, shared_segment_size,
                          IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    if(-1==segment_id) {
                warn( " :Failed to acquire segment" );
        return EXIT_FAILURE;
    }
	printf ("segment id as %d\n", segment_id);


    /* ���L�������ɃA�^�b�` */
    char* shared_memory = (char*) (shmat(segment_id, 0, 0));
    printf ("shared memory attached at address %p\n", shared_memory);

    warn("Writing step 1 to shared memory");
    /* ���L�������ւ̏����� */
    sprintf (shared_memory, "Step 1 Hello, world.");
    warn("Hit any key to continue");
    getchar();

    warn("Writing step 2 to shared memory");
    /* ���L�������ւ̏����� */
    sprintf (shared_memory, "Step 2 This is step 2.");

    warn("Hit any key to close shared memory");
    getchar();

    /* ���L�������̃f�^�b�` */
    shmdt(shared_memory);
    /* ���L�������̉�� */
    shmctl (segment_id, IPC_RMID, 0);

    return EXIT_SUCCESS;
}
