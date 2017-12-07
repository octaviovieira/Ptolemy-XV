
//CONFIGURAR EXPERIMENTO

#define EXP_TIP clock     //[clock, energy, memory, time]
#define EXP_CAT pri_mem   //[pri_mem, sec_mem]
#define EXP_TAM 32B       //[16B, 32B, 64B, 128B, 256B, 512B, 1024B]
#define EXP_ALG serp_enc  //[aes_enc, aes_dec, serp_enc, serp_dec]

//MACROS DE EXECUÇÃO

#define STRF(TOK) #TOK
#define EXP_END(TP, CT, TM, AG) STRF(TP/CT/TM/AG.h)
#define EXP(TP, CT, TM, AG) EXP_END(TP,CT,TM,AG)
#include EXP(EXP_TIP,EXP_CAT,EXP_TAM,EXP_ALG)