#include "atoc.h"


/* Register definitions */
addr reg[4] = {0x000};

byte ir = 0x00;
byte nz = 0x0;


/* ALU functions */
void cond(addr a) {
    nz = ((a >> (BYTE_SIZE-2)) & 0x2) | (BYTE(a) == 0);
}

addr and(addr *a, byte b) {
    return *a &= b | ~BYTE_MASK;
}

addr xor(addr *a, byte b) {
    return *a ^= b;
}

addr add(addr *a, byte b) {
    return *a = ADDR(*a + (signed char)b);
}

addr sub(addr *a, byte b) {
    return *a = ADDR(*a - (signed char)b);
}

addr (*alop[4])(addr*, byte) = {and, xor, add, sub};


/* Move instructions */
byte load(addr *ra) {
    byte temp = mem_get(*ra);
    *ra = ADDR(*ra + 1);
    return temp;
}

void mov(addr *ra, addr *rd) {
    *rd = *ra;
}

void swp(addr *ra, addr *rd) {
    addr temp = *rd;
    *rd = *ra;
    *ra = temp;
}

void st(addr *ra, addr *rd) {
    *ra = ADDR(*ra - 1);
    mem_set(*ra, BYTE(*rd));
    *rd = ADDR(*rd >> 8);
}

void ld(addr *ra, addr *rd) {
    *rd = ADDR(*rd << 8 | load(ra));
}

void (*mvop[4])(addr*, addr*) = { mov, swp, st, ld };


/* Instruction helper functions */
byte cc(byte i) {
    byte cond[4] = { nz & 0x1, ~(nz & 0x1), nz == 0x10, nz == 0x00 };
    return cond[(i >> 4) & 0x3];
}

void (*mm(byte i))(addr*, addr*) {
    return mvop[(i >> 2) & 0x3];
}

addr (*alu(byte i))(addr*, byte) {
    return alop[(i >> 2) & 0x3];
}

addr *ra(byte i) {
    return &reg[(i >> 4) & 0x3];
}

addr *rd(byte i) {
    return &reg[i & 0x3];
}


/* Opcode definitions */
void mr(byte i) {
    mm(i)(ra(i), rd(i));
}

void ca(byte i) {
    byte temp = load(&pc);
    if (cc(i)) alu(i)(rd(i), temp);
}

void ar(byte i) {
    cond(alu(i)(rd(i), BYTE(*ra(i))));
}

void am(byte i) {
    cond(alu(i)(rd(i), load(ra(i))));
}

void (*ops[4])(byte i) = { mr, ca, ar, am };


/* Simulation functions */
void fetch(void) {
    ir = load(&pc);
}

void exec(void) {
    ops[ir >> 6](ir);
}

byte halted(void) {
    return (ir == 0xff && mem[pc+1] == 0x02) || 
           (ir == 0xfb && mem[pc+1] == 0xfe);
}

void reset(addr entry) {
    reg[0] = 0x000;
    reg[1] = 0x000;
    reg[2] = 0x000;
    reg[3] = 0x000;
    nz = 0x0;
    ir = 0x0;

    pc = entry;
}

void step(void) {
    fetch();
    exec();
}
