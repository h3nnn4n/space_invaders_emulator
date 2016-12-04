#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>

#include "utils.h"
#include "types.h"
#include "emulator.h"
#include "graphics.h"
#include "disassembler.h"

int main(int argc, char *argv[]) {
    FILE *f = NULL;
    _cpu_info cpu;

    if ( argc == 1 ) {
        printf("Usage: %s file\n", argv[0]);
        return EXIT_FAILURE;
    } else {
        init_cpu(&cpu);
        off_t buffer_size = -1;
        f = fopen(argv[1], "rb");
        buffer_size = fsize( argv[1] );

        if ( fread(cpu.memory, buffer_size, 1, f) != 1 ) {
            printf("Something went weird while reding into buffer\n");
        }

        fclose(f);

        printf("Opening: %s\nFile contains: %lu bytes\n", argv[1], buffer_size);
    }

    sdl_init();

    while ( 1 ) {
        /*cpu.pc += disassembler(cpu.memory, cpu.pc);*/
        emulator ( &cpu );

        if ( cpu.cycles > 16667 ) {
            cpu.cycles -= 16667;

            if ( cpu.interrupt_addr == 0x10 ) {
                cpu.interrupt_addr = 0x08;
            } else {
                cpu.interrupt_addr = 0x10;
            }

            emulate_INTERRUPT( &cpu );
            update_screen ( &cpu );
            SDL_Delay(16);
        }

        /*if ( cpu.instructions_executed > 100000 )*/
            /*break;*/
    }

    sdl_quit();

    return 0;
}
