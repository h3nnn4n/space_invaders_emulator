#ifndef EMULATOR_H
#define EMULATOR_H

#include "types.h"

unsigned short int emulator     ( _cpu_info *cpu ) ;
void               emulate_ADD  ( _cpu_info *cpu ) ;
void               emulate_CALL ( _cpu_info *cpu ) ;

#endif /* EMULATOR_H */