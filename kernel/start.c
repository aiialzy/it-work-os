#include "log.h"
#include "riscv.h"
#include "math.h"

void main();

void print_misa() {
    int width = 0;
    char extensions[27];
    unsigned long misa = r_misa();

    width = (misa >> 62) & 0b11;
    width = pow_l(width, width + 4);

    int count = 0;
    for (int i=0; i<26; i++) {
        if (((misa >> i) & 1) == 1) {
            extensions[count++] = 'A' + i;
        }
    }
    extensions[count] = 0; 

    info("misa: 位宽:%d, 扩展指令集: %s", width, extensions);
}

void print_mvendorid() {
    info("mvendorid: %b", r_mvendorid());
}

void print_marchid() {
    info("marchid: %b", r_marchid());
}

void print_mimpid() {
    info("mimpid: %b", r_mimpid());
}

void print_mhartid() {
    info("mhartid: %b", r_mhartid());
}

void _start() {
    print_misa();
    print_mvendorid();
    print_marchid();
    print_mimpid();
    print_mhartid();

    info("设置mstatus");
    unsigned long x = r_mstatus();
    info("mstatus: %b", x);

    x &= ~MSTATUS_MPP_MASK;
    x |= MSTATUS_MPP_S;
    w_mstatus(x);

    info("mstatus: %b", r_mstatus());

    info("设置异常地址以便进入main");
    w_mepc((unsigned long)main);

    // 关闭分页
    w_satp(0);


    // 移交全部中断和异常给S模式
    w_medeleg(0xffff);
    w_mideleg(0xffff);
    w_sie(r_sie() | SIE_SEIE | SIE_STIE | SIE_SSIE);

    // 配置S模式可访问全部内存
    w_pmpaddr0(0x3fffffffffffffull);
    w_pmpcfg0(0xf);

    info("准备切换supervisor模式");
    // switch to supervisor mode and jump to main().
    asm volatile("mret");

}