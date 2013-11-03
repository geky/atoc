; Simple Assembly

.hello
    "Hello World" 0

.entry
    set2 b, .hello

.loop
    ld a, b
    tst a
    brz .done

    push2 b
    set2 b, .stdout
    st a, b
    pop2 b
    br .loop

.done
    halt


; Direct opcodes

.hello
    "Hello World" 0

.entry
    ld b, pc
    .hello.h
    ld b, pc
    .hello.l

.loop
    ld a, b
    and a, a
    caddz pc
    $(.done - .)

    st b, sp
    st b, sp
    ld b, pc
    .stdout.h
    ld b, pc
    .stdout.l
    st a, b
    ld b, sp
    ld b, sp
    subi pc, pc
    $(. - .loop)

.done
    subi pc, pc
    0x01


; Hexadecimal
.hello
    48 65 6c 6c 6f 20 57 6f 72 6c 64 21 00

.entry
    3d .hello.h 3d .hello.l

.loop
    1c
    80
    4b $(.done - .)

    29 29
    3d .stdout.h 3d .stdout.l
    18
    2d 2d
    ff $(. - .loop)

.done
    ff 02


; Object file dump
; stdout = 0x12

.hello 0x200, 13
    48 65 6c 6c 6f 20 57 6f 72 6c 64 21 00

.entry 0x100, 21
    3d 02 3d 00
    1c 80 4b 0b
    29 29 
    3d 00 3d 13
    18
    2d 2d
    ff 0f
    ff 02
    
