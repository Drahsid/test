.set noreorder

.global entrypoint

.section .text, "ax"

entrypoint:
    la      $t2, main
    la      $sp, gBootStack
    la      $t0, __bss_start
    la      $t1, __bss_size
    la      $t3, gBootStackSize
    lw      $t3, 0x0($t3)
.wipeBss:
    sw      $zero, 0x0($t0)
    addi    $t1, $t1, -4
    bnez    $t1, .wipeBss
    addi    $t0, $t0, 4
    jr      $t2
    addu    $sp, $sp, $t3
    nop

