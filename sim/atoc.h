#ifndef ATOC
#define ATOC


/* Word size information */
#ifndef ADDR_SIZE
#define ADDR_SIZE 12
#endif

#ifndef BYTE_SIZE
#define BYTE_SIZE 8
#endif

typedef unsigned char byte;
typedef unsigned int addr;

#define ADDR_MASK ((1<<ADDR_SIZE)-1)
#define BYTE_MASK ((1<<BYTE_SIZE)-1)

#define ADDR(x) ((addr)((x) & ADDR_MASK))
#define BYTE(x) ((byte)((x) & BYTE_MASK))


/* Register definitions */
extern addr reg[4];
#define pc reg[0x3]
extern byte ir;
extern byte nz;


/* Accessable memory */
extern byte mem[1 << ADDR_SIZE];

byte mem_get(addr loc);
void mem_set(addr loc, byte val);


/* Simulate */
byte halted(void);
void reset(addr entry);
void fetch(void);
void exec(void);
void step(void);


#endif
