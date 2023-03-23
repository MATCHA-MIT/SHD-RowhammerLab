#include "../shared.hh"
#include "../params.hh"

#define POOL_SIZE 1000
#define NUM_BINS 16

// TODO: Change this!
#define THRESHOLD 0

int main (int ac, char **av) {
  
  setvbuf(stdout, NULL, _IONBF, 0);

  if (getuid()) {
    printf("ERROR: Root permissions required!\n");
    exit(1);
  }

  // Allocate a large pool of memory (of size BUFFER_SIZE_MB) pointed to by allocated_mem
  allocated_mem = allocate_pages(BUFFER_SIZE_MB * 1024UL * 1024UL);
  setup_PPN_VPN_map(allocated_mem, PPN_VPN_map);

  // TODO: Fill in a victim addresses from your email! 
  uint64_t physVicAddr = 0;


  // TODO: List all addresses in row N-1 which have the same column bits

  // TODO: Check which one of these addresses maps to the same bank as the victim (aggressor #1)

  // TODO: Repeat for addresses in row N+1
 

  // TODO: Perform a rowhammer attack using the two aggressor rows derived

  return 0;
}

