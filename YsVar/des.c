#include <fecom.h>

#ifdef __cplusplus
extern "C"{
#endif

#define KEY_LENGTH 16

/* 1992-08-24 : This header must be included in the
                main program.
*/
UCHAR des_ip[64] = {   /* initial permutation */
    58,50,42,34,26,18,10, 2,
    60,52,44,36,28,20,12, 4,
    62,54,46,38,30,22,14, 6,
    64,56,48,40,32,24,16, 8,
    57,49,41,33,25,17, 9, 1,
    59,51,43,35,27,19,11, 3,
    61,53,45,37,29,21,13, 5,
    63,55,47,39,31,23,15, 7
  };

UCHAR des_rip[64] = {   /* inverse of the initial permutation */
    40, 8,48,16,56,24,64,32,
    39, 7,47,15,55,23,63,31,
    38, 6,46,14,54,22,62,30,
    37, 5,45,13,53,21,61,29,
    36, 4,44,12,52,20,60,28,
    35, 3,43,11,51,19,59,27,
    34, 2,42,10,50,18,58,26,
    33, 1,41, 9,49,17,57,25
  };

UCHAR des_e[48] = {   /* E bit-selection table */
    32, 1, 2, 3, 4, 5,
     4, 5, 6, 7, 8, 9,
     8, 9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32, 1
  };

UCHAR des_s[8][4][16] = {  /* primitive functions s */
    {{14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7},
     { 0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8},
     { 4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0},
     {15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13}},

    {{15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10},
     { 3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5},
     { 0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15},
     {13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9}},

    {{10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8},
     {13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1},
     {13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7},
     { 1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12}},

    {{ 7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15},
     {13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9},
     {10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4},
     { 3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14}},

    {{ 2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9},
     {14,11, 2,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6},
     { 4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14},
     {11, 8,12, 7, 1,14, 2,13, 6,15, 0, 9,10, 4, 5, 3}},

    {{12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11},
     {10,15, 4, 2, 7,12, 9, 5, 6, 1,13,14, 0,11, 3, 8},
     { 9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6},
     { 4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13}},

    {{ 4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1},
     {13, 0,11, 7, 4, 9, 1,10,14, 3, 5,12, 2,15, 8, 6},
     { 1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2},
     { 6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12}},

    {{13, 2, 8, 4, 6,15,11, 1,10, 9, 3,14, 5, 0,12, 7},
     { 1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2},
     { 7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8},
     { 2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11}}
  };
UCHAR des_p[32] = {    /* primitive function p */
    16, 7,20,21,
    29,12,28,17,
     1,15,23,26,
     5,18,31,10,
     2, 8,24,14,
    32,27, 3, 9,
    19,13,30, 6,
    22,11, 4,25
  };
UCHAR des_pc1[56] = {    /* permuted choice 1 */
    57,49,41,33,25,17, 9,
     1,58,50,42,34,26,18,
    10, 2,59,51,43,35,27,
    19,11, 3,60,52,44,36,
    63,55,47,39,31,23,15,
     7,62,54,46,38,30,22,
    14, 6,61,53,45,37,29,
    21,13, 5,28,20,12, 4
  };
UCHAR des_pc2[48] = {    /* permuted choice 2 */
    14,17,11,24, 1, 5,
     3,28,15, 6,21,10,
    23,19,12, 4,26, 8,
    16, 7,27,20,13, 2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
  };
UCHAR des_lshift[16] = {    /* iteration left shifts */
    1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
  };

UCHAR data_bit[64],key_bit[64], 
              data_lbit[32],data_rbit[32],
              frk_bit[32],er[50],
              key_cd[56],
              key_k[16][48],
              key_b[8],
              key_sb[8];
UCHAR key_h[16],data_h[16];
UCHAR key[16],data[16];
UCHAR edata[16],edata_h[16];
typedef    UCHAR unch ;

void f_cipher(UCHAR *r,UCHAR *k,UCHAR *frk);
void bit_xor(UCHAR *a,UCHAR *b,INT32 len,UCHAR *ab);
void key_calculation(UCHAR *keybit);
void left_shift(UCHAR *val,UCHAR shift);
void spilt_bit(UCHAR *data,INT32 len,UCHAR *databit);
void merge_bit(UCHAR *bit,INT32 len,UCHAR *data);
void des(INT32 encry_flag,UCHAR *key,UCHAR *data,UCHAR *edata);
void Tri_DES(INT32 sec_flag, UCHAR *Key_data, /* 16 bytes */ 
        UCHAR *in_data, UCHAR *out_data);
void DESDivKeys(const UCHAR *key,
                    const INT32 divnum,
                    UCHAR *divdata,
                    UCHAR *out_key);
INT32 DESEncrypt(const UCHAR *key,  /* key */
        const INT32 divnum,              /* divided times */
        UCHAR *divdata,       /* divided data */
        const INT32 ilen_in,            /* length of data */
        UCHAR *in,            /* Encrypt data(input) */
        UCHAR *out);          /* Encrypt data(output) */
INT32 DESDecrypt(const UCHAR *key,  /* key */
        const INT32 divnum,              /* divided times */
        UCHAR *divdata,       /* divided data */
        const INT32 ilen_in,            /* length of data */
        UCHAR *in,            /* Encrypt data(input) */
        UCHAR *out);          /* Encrypt data(output) */
INT32 DESMac(const UCHAR *key,  /* key */
        const INT32 divnum,              /* divided times */
        UCHAR *divdata,       /* divided data */
        const INT32 ilen_in,            /* length of data */
        UCHAR *in,            /* Encrypt data(input) */
        UCHAR *mac,           /* Encrypt data(output) */
        INT32 iFlag);                   /* 0:Right;other:left */
/***********************************/
/*   cipher function               */
/*      f(r,k)                     */
/***********************************/

void f_cipher(UCHAR *r,UCHAR *k,UCHAR *frk)
{
    UCHAR row,col;
    INT32 i,j;
    UCHAR tmp_bit[64];
    UCHAR tmp[8];

    for (i=0;i<48;i++)      /* E bit-selection */
        er[i] = r[des_e[i]-1];
    bit_xor(er,k,48,tmp_bit);
    for (i=0;i<8;i++) {
        for (j=0;j<6;j++)
          key_b[j] = tmp_bit[i*6+j];
        row = key_b[0] *2 + key_b[5];
        col = key_b[1] *8 + key_b[2] *4 + key_b[3] *2 + key_b[4];
        key_sb[i] = des_s[i][row][col];
        }
    for (i=0;i<4;i++)
        tmp[i] = key_sb[i*2] * 16 + key_sb[i*2+1];
    spilt_bit(tmp,4,tmp_bit);
    for (i=0;i<32;i++)      /* primitive function P */
        frk[i] = tmp_bit[des_p[i]-1];
}

/***********************************/
/*   bit xor                       */
/*   ab = a xor b                  */
/***********************************/
void bit_xor(UCHAR *a,UCHAR *b,INT32 len,UCHAR *ab)
{
    INT32 i;
    for (i=0;i<len;i++)  /* er (xor) k */
        if (a[i] == b[i])
            ab[i] = 0;
        else
            ab[i] = 1;
}
/***********************************/
/*   key calculation               */
/***********************************/

void key_calculation(UCHAR *keybit)
{
    INT32 i,j;
    for (i=0;i<56;i++)   /* permuted choice 1 */
        key_cd[i] = keybit[des_pc1[i]-1];

    for (i=0;i<16;i++) {
        left_shift(key_cd,des_lshift[i]);  /* left shift */
        left_shift(key_cd+28,des_lshift[i]);
        for (j=0;j<48;j++)  /* permuted choice 2 */
            key_k[i][j] = key_cd[des_pc2[j]-1];
        }
}

/*********************************/
/* left shift function           */
/*********************************/

void left_shift(UCHAR *val,UCHAR shift)
{
    INT32 i;
    UCHAR tmp_bit[64];
    for (i=0;i<shift;i++)
        tmp_bit[i] = val[i];
    for (i=0;i<28-shift;i++)
        val[i] = val[i+shift];
    for (i=0;i<shift;i++)
        val[28-shift+i] = tmp_bit[i];
}

/*********************************/
/* get bit value                 */
/*********************************/

void spilt_bit(UCHAR *data,INT32 len,UCHAR *databit)
{
    INT32 i,j;
    UCHAR ch;
    for (i=0;i<len;i++) {
        ch = data[i];
        for (j=0;j<8;j++) {
            if (ch & 0x80)
                databit[i*8+j] = 1;
            else
                databit[i*8+j] = 0;
            ch <<=1;
            }
        }
}

/*********************************/
/* get bit value                 */
/*********************************/

void merge_bit(UCHAR *bit,INT32 len,UCHAR *data)
{
    INT32 i,j;
    for (i=0;i<len;i++) {
        data[i] = 0;
        for (j=0;j<8;j++) {
            data[i] <<=1;
            data[i] += bit[i*8+j];
            }
        }
}

void des(INT32 encry_flag,UCHAR *key,UCHAR *data,UCHAR *edata)
{
    INT32 i, j;
    UCHAR tmp_bit[64];

    spilt_bit(key,8,key_bit);
    spilt_bit(data,8,data_bit);
    key_calculation(key_bit);
    for (i=0;i<32;i++) {  /* initial permutate  */
        data_lbit[i] = data_bit[des_ip[i]-1];
        data_rbit[i] = data_bit[des_ip[i+32]-1];
        }
    switch (encry_flag) {
        case 1:       /* encry data  */
          for (i=0;i<16;i++) {  /* L' = R, R' = L xor f(R,Kn) */
              for (j=0;j<32;j++)
                  tmp_bit[j] = data_rbit[j];
              f_cipher(data_rbit,key_k[i],frk_bit);
              bit_xor(data_lbit,frk_bit,32,data_rbit);
              for (j=0;j<32;j++)
                  data_lbit[j] = tmp_bit[j];
              }
          break;
        default:      /* decry data */
            for (i=15;i>=0;i--) {  /* L' = R, R' = L xor f(R,Kn) */
                for (j=0;j<32;j++)
                    tmp_bit[j] = data_rbit[j];
                f_cipher(data_rbit,key_k[i],frk_bit);
                bit_xor(data_lbit,frk_bit,32,data_rbit);
                for (j=0;j<32;j++)
                    data_lbit[j] = tmp_bit[j];
                }
            break;
      }
    for (i=0;i<32;i++) {
        tmp_bit[i]    = data_rbit[i];
        tmp_bit[i+32] = data_lbit[i];
        }
    for (i=0;i<64;i++)   /* inverse initial perm */
        data_bit[i] = tmp_bit[des_rip[i]-1];
    merge_bit(data_bit,8,edata);
}

/*
3DES calculation
*/
void Tri_DES(INT32 sec_flag, 
        UCHAR *Key_data, /* 16 bytes */
        UCHAR *in_data, 
        UCHAR *out_data)
{
  UCHAR tmp_indata[9];
  UCHAR tmp_outdata[9];
  UCHAR Key_L[9], Key_R[9];

  memcpy(tmp_indata, in_data, 8);
  memcpy(Key_L, Key_data, 8);        /* Left Key */
  memcpy(Key_R, Key_data+8, 8);      /* Right Key */

  if (sec_flag == 0)  
  /* Triple DES for Decryption , M = DES-1{K_L, DES[K_R, DES-1(K_L, C)]} */
  {
    des(0, Key_L, tmp_indata, tmp_outdata);
    memcpy(tmp_indata, tmp_outdata, 8);
    des(1, Key_R, tmp_indata, tmp_outdata);
    memcpy(tmp_indata, tmp_outdata, 8);
    des(0, Key_L, tmp_indata, tmp_outdata);
    memcpy(out_data, tmp_outdata, 8);
  }
  else        
  /* Triple DES for Encryption , C = DES{K_L, DES-1[K_R, DES(K_L, M)]} */
  {
    des(1, Key_L, tmp_indata, tmp_outdata);
    memcpy(tmp_indata, tmp_outdata, 8);
    des(0, Key_R, tmp_indata, tmp_outdata);
    memcpy(tmp_indata, tmp_outdata, 8);
    des(1, Key_L, tmp_indata, tmp_outdata);
    memcpy(out_data, tmp_outdata, 8);
  }
}

/*
calculation key (one divide key)
*/
void divide_one_key(const UCHAR *Key,
                            UCHAR *divdata,
                            UCHAR *out_key)
{
  UCHAR *Kd_L,*Kd_R;
  UCHAR inv_data[KEY_LENGTH + 1];
  UCHAR TempKey[KEY_LENGTH + 1];

  INT32 i;

  memset(inv_data,0,sizeof(inv_data));
  memset(TempKey,0,sizeof(TempKey));

  Kd_L = out_key;
  Kd_R = out_key + 8;

  Tri_DES(1, (UCHAR *)Key, divdata, Kd_L);
  for (i=0;i<8;i++)
    inv_data[i] = ~divdata[i];
  Tri_DES(1, (UCHAR *)Key, inv_data, TempKey);
    memcpy(Kd_R,TempKey,8);
}

/*
calculation key (many divide keys)
*/
void DESDivKeys(const UCHAR *key,
    const INT32 divnum,
    UCHAR *divdata,
    UCHAR *out_key)
{
  UCHAR cTempkey[KEY_LENGTH + 1];
  UCHAR *cTempdivdata;
  UCHAR ctempkey[KEY_LENGTH + 1];
  INT32 i;

  memset(cTempkey,0,sizeof(cTempkey));
  memcpy(cTempkey,key,KEY_LENGTH);

  for ( i=0;i<divnum;i++ )
  {
    memset(ctempkey,0,KEY_LENGTH + 1);
    cTempdivdata = divdata + i*8;
    divide_one_key(cTempkey,cTempdivdata,ctempkey);
    memset(cTempkey,0,KEY_LENGTH + 1);
    memcpy(cTempkey,ctempkey,KEY_LENGTH);
  }
  memcpy(out_key,ctempkey,KEY_LENGTH);
}

INT32 DESEncrypt(const UCHAR *key,  /* key */
    const INT32 divnum,              /* divided times */
    UCHAR *divdata,       /* divided data */
    const INT32 ilen_in,            /* length of data */
    UCHAR *in,            /* Encrypt data(input) */
    UCHAR *out)           /* Encrypt data(output) */
{
  UCHAR cKey[KEY_LENGTH + 1];
  INT32 iData_num;
  UCHAR *buf;
  INT32 i;
  
  memset(cKey,0,sizeof(cKey));
  buf = in;
  DESDivKeys(key,divnum,divdata,cKey);
  
  /* Encrypt data */
  if ( 0 != (ilen_in % 8) )
      return -1;
  iData_num = ilen_in / 8;
  for ( i=0;i<iData_num;i++ )
  {
    Tri_DES(1, (UCHAR *)cKey, buf+(i*8), out+(i*8));
  }
  return 0;
}

INT32 DESDecrypt(const UCHAR *key,  /* key */
    const INT32 divnum,              /* divided times */
    UCHAR *divdata,       /* divided data */
    const INT32 ilen_in,            /* length of data */
    UCHAR *in,            /* Encrypt data(input) */
    UCHAR *out)           /* Encrypt data(output) */
{
  UCHAR cKey[KEY_LENGTH + 1];
  INT32 iData_num;
  UCHAR *buf;
  INT32 i;
  
  memset(cKey,0,sizeof(cKey));
  buf = in;
  DESDivKeys(key,divnum,divdata,cKey);
  
  /*Encrypt data */
  if ( 0 != (ilen_in % 8) )
      return -1;
  iData_num = ilen_in / 8;    
  for ( i=0;i<iData_num;i++ )
  {
    Tri_DES(0, (UCHAR *)cKey, buf+(i*8), out+(i*8));
  }
  return 0;
}

INT32 DESMac(const UCHAR *key,  /* key */
        const INT32 divnum,              /* divided times */
        UCHAR *divdata,       /* divided data */
        const INT32 ilen_in,            /* length of data */
        UCHAR *in,            /* Encrypt data(input) */
        UCHAR *mac,           /* Encrypt data(output) */
        INT32 iFlag)                    /* 0:Right;other:left */
{
  UCHAR cKey[17];
  INT32 iData_num;
  UCHAR *buf;
  UCHAR ini_value[8];
  UCHAR cipher_data[8];
  UCHAR K2up[9];
  UCHAR *b;
  INT32 i,j;
  
  memset(cKey,0,sizeof(cKey));
  memset(ini_value,0,sizeof(ini_value));
  memset(cipher_data,0,sizeof(cipher_data));
  memset(K2up,0,sizeof(K2up));
  b = in;
  buf = in;
  DESDivKeys(key,divnum,divdata,cKey);
  if ( 0==iFlag )
  {
    memcpy(K2up,cKey+8,8);
  }
  else
  {
    memcpy(K2up,cKey,8);
  }
  
  /* MAC */
  if ( 0 != (ilen_in % 8) )
      return -1;
  iData_num = ilen_in / 8;
  for ( i=0;i<iData_num;i++ )
  {
  for (j=0;j<8;j++)
    ini_value[j] ^= *(b+j);
  des(1, K2up,ini_value, cipher_data);
  memcpy(ini_value, cipher_data, 8);
  b += 8;
  }
  memcpy(mac,ini_value,8);
  return 0;
}

#ifdef __cplusplus
}
#endif


