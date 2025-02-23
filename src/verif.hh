#ifndef VERIF_HH
#define VERIF_HH

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdlib.h>

#include <map>

#include "params.hh"

// part 1 checker
void verify_phys_to_virt(void * mem_map, uint64_t (*fun)(uint64_t));
void verify_virt_to_phys(void * mem_map, uint64_t (*fun)(uint64_t));
void verify_PPN_VPN_map(void * mem_map, std::map<uint64_t, uint64_t> &PPN_VPN_map);

// part 5 checker
int checkParity(uint32_t encoded);

#endif
