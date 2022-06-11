// mstatus
#define MSTATUS_MPP_MASK (3UL << 11)
#define MSTATUS_MPP_M (3UL << 11)
#define MSTATUS_MPP_S (1UL << 11)
#define MSTATUS_MPP_U (0UL << 11)
#define MSTATUS_MIE (1UL << 3)

// sstatus
#define SSTATUS_SPP (1UL << 8)
#define SSTATUS_SPIE (1UL << 5)
#define SSTATUS_UPIE (1UL << 4)
#define SSTATUS_SIE (1UL << 1)
#define SSTATUS_UIE (1UL << 1)

// Supervisor Interrupt Enable
#define SIE_SEIE (1L << 9)  // external
#define SIE_STIE (1L << 5)  // timer
#define SIE_SSIE (1L << 1)  // software

// mstatus
static inline unsigned long r_mstatus() {
    unsigned long x;
    asm volatile("csrr %0, mstatus" : "=r" (x));
    return x;
}

static inline void w_mstatus(unsigned long x) {
    asm volatile("csrw mstatus, %0" : : "r" (x));
}

// sstatus
static inline unsigned long r_sstatus() {
    unsigned long x;
    asm volatile("csrr t0, sstatus");
    asm volatile("sd t0, (%0)" : "=r"(x));
    return x;
}

static inline void w_sstatus(unsigned long x) {
    asm volatile("csrw sstauts, %0" : : "r"(x));
}

static inline void w_mepc(unsigned long x) {
    asm volatile("csrw mepc, %0" : : "r"(x));
}

static inline void w_satp(unsigned long x) {
    asm volatile("csrw satp, %0" : : "r"(x));
}

static inline void w_mideleg(unsigned long x) {
    asm volatile("csrw mideleg, %0" : : "r"(x));
}

static inline void w_medeleg(unsigned long x) {
    asm volatile("csrw medeleg, %0" : : "r"(x));
}

static inline void w_stvec(unsigned long x) {
    asm volatile("csrw stvec, %0" : : "r"(x));
}

// Supervisor Interrupt Enable

static inline unsigned long r_sie() {
    unsigned long x;
    asm volatile("csrr %0, sie" : "=r"(x));
    return x;
}

static inline void w_sie(unsigned long x) {
    asm volatile("csrw sie, %0" : : "r"(x));
}

static inline void w_pmpaddr0(unsigned long x) {
    asm volatile("csrw pmpaddr0, %0" : : "r"(x));
}

static inline void w_pmpcfg0(unsigned long x) {
    asm volatile("csrw pmpcfg0, %0" : : "r"(x));
}

static inline unsigned long r_misa() {
    unsigned long x;
    asm volatile("csrr %0, misa" : "=r"(x));
    return x;
}

static inline unsigned long r_mvendorid() {
    unsigned long x;
    asm volatile("csrr %0, mvendorid" : "=r"(x));
    return x;
}

static inline unsigned long r_marchid() {
    unsigned long x;
    asm volatile("csrr %0, marchid" : "=r"(x));
    return x;
}

static inline unsigned long r_mimpid() {
    unsigned long x;
    asm volatile("csrr %0, mimpid" : "=r"(x));
    return x;
}

static inline unsigned long r_mhartid() {
    unsigned long x;
    asm volatile("csrr %0, mhartid" : "=r"(x));
    return x;
}

static inline void w_sepc(unsigned long x) {
    asm volatile("csrw sepc, %0" : : "r"(x));
}

static inline unsigned long r_sepc() {
    unsigned long x;
    asm volatile("csrr %0, sepc" : "=r"(x));
    return x;
}

static inline unsigned long r_scause() {
    unsigned long x;
    asm volatile("csrr %0, scause" : "=r"(x));
    return x;
}

static inline unsigned long r_stval() {
    unsigned long x;
    asm volatile("csrr %0, stval" : "=r"(x));
    return x;
}