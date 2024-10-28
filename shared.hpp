#include <stdlib.h>
#include <semaphore.h>

#ifndef _SHARED_MEMORY_H
#define _SHARED_MEMORY_H

// Semaphore names for shared memory
static const char* semNameEmpty = "sem_empty_slots";
static const char* semNameMutex = "sem_protect";
static const char* semNameFull = "sem_filled_slots";
static const char* sharedMemName = "ProdCons_Shared_Mem";

// Buffer settings
static const int maxBufferSize = 2;
struct BufferTable {
    int slot[2];          // Circular buffer array with 2 slots
    int writePos;         // Index where producer writes
    int readPos;          // Index where consumer reads
};

// Size of shared memory structure
static const int sharedMemSize = sizeof(struct BufferTable);

#endif
