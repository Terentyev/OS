[BITS 32]
[global start]
[extern k_main] ; this is in the c file

start:
    call k_main

    cli ; stop interrupts
    hlt ; halt the CPU
