#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "shared.hpp"

int main() {
    time_t seed;
    srand((unsigned) time(&seed));

    // Setup shared memory
    int shared_fd = shm_open(sharedMemName, O_CREAT | O_RDWR, 0666);
    ftruncate(shared_fd, sharedMemSize);
    struct BufferTable *sharedTable = static_cast<BufferTable*>(mmap(0, sharedMemSize, PROT_WRITE | PROT_READ, MAP_SHARED, shared_fd, 0));

    // Initialize semaphores
    sem_t *sem_full = sem_open(semNameFull, O_CREAT, 0666, 0);
    sem_t *sem_empty = sem_open(semNameEmpty, O_CREAT, 0666, maxBufferSize);
    sem_t *sem_mutex = sem_open(semNameMutex, O_CREAT, 0666, 1);

    // Producer loop
    for(int produceCount = 0; produceCount < 9; ++produceCount) {
        // Wait until there is empty space in the buffer
        sem_wait(sem_empty);
        sleep(rand() % 2 + 1); // wait random time
        sem_wait(sem_mutex);

        int item = rand() % 10;
        sharedTable->slot[sharedTable->writePos] = item;

        printf("Producer created item %d at position [%d]\n", sharedTable->slot[sharedTable->writePos], sharedTable->writePos);
        sharedTable->writePos = (sharedTable->writePos + 1) % maxBufferSize;

        sem_post(sem_mutex);
        sem_post(sem_full);
    }

    // Close and unlink semaphores
    sem_close(sem_full);
    sem_close(sem_empty);
    sem_close(sem_mutex);
    sem_unlink(semNameFull);
    sem_unlink(semNameEmpty);
    sem_unlink(semNameMutex);

    // Release shared memory resources
    munmap(sharedTable, sharedMemSize);
    close(shared_fd);
    shm_unlink(sharedMemName);

    return 0;
}
