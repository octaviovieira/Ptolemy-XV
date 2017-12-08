
//EXPERIMENT CONFIGURATION

#define EXP_TIP time      //[clock, energy, memory, time]
#define EXP_CAT pri_mem   //[pri_mem, sec_mem]
#define EXP_TAM 1024B     //[16B, 32B, 64B, 128B, 256B, 512B, 1024B][1KB, 2KB, 4KB, 8KB, 16KB, 32KB, 64KB]
#define EXP_ALG aes_enc   //[aes_enc, aes_dec, serp_enc, serp_dec]

//EXECUTION MACROS

#define STRF(TOK) #TOK
#define EXP_END(TP, CT, TM, AG) STRF(TP/CT/TM/AG.h)
#define EXP(TP, CT, TM, AG) EXP_END(TP,CT,TM,AG)
#include EXP(EXP_TIP,EXP_CAT,EXP_TAM,EXP_ALG)