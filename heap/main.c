#include <stdio.h>
#include <stdint.h>

#define MEM_SIZE 256

struct chunk {
    uint8_t header;
    int size;
};

void* custom_malloc(int size, void** memory);
void custom_free(void* p_memory);

int main() {
    void* memory[MEM_SIZE] = {0};

    printf("sizeof void*: %ld\n", sizeof(void*));
    return 0;
}

void* custom_malloc(int size, void** memory) {
    void* mem_loc;

    int current_loc = 0;
    while(1) { 
        if (*memory[current_loc] & 0x0000000000000001 == 0x01) {

        }
    }
    
    return mem_loc;
}

