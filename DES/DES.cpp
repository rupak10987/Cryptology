#include<iostream>
#include"some_base_funcions.h"

char choice;

///DES tables
//shift info
int shift_amount[17]={0,1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
//pc1
int pc1[56]={57,49,41,33,25,17,9,
             1,58,50,42,34,26,18,
             10,2,59,51,43,35,27,
             19,11,3,60,52,44,36,
             63,55,47,39,31,23,15,
             7,62,54,46,38,30,22,
             14,6,61,53,45,37,29,
             21,13,5,28,20,21,4};
//pc2
int pc2[48]={14,17,11,24,1,5,
             3,28,15,6,21,10,
             23,19,12,4,26,8,
             16,7,27,20,13,2,
             41,52,31,37,47,55,
             30,40,51,45,33,48,
             44,49,39,56,34,53,
             46,42,50,36,29,32};

//ebit
int e_bit[48]={32,1,2,3,4,5,
               4,5,6,7,8,9,
               8,9,10,11,12,13,
               12,13,14,15,16,17,
               16,17,18,19,20,21,
               20,21,22,23,24,25,
               24,25,26,27,28,29,
               28,29,30,31,32,1
               };

//s_box
int sbox1[4][16]={{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
                 {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
                 {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
                 {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}};
int sbox2[4][16]={{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
                 {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
                 {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
                 {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}};

int sbox3[4][16]={{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
                 {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
                 {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
                 {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}};

int sbox4[4][16]={{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
                 {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
                 {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
                 {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}};
int sbox5[4][16]={{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
                 {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
                 {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
                 {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}};
int sbox6[4][16]={{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
                 {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
                 {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
                 {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}};
int sbox7[4][16]={{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
                 {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
                 {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
                 {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}};
int sbox8[4][16]={{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
                 {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
                 {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
                 {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}};

int p_box[32]={16,7,20,21,
              29,12,28,17,
              1,15,23,26,
              5,18,31,10,
              2,8,24,14,
              32,27,3,9,
              19,13,30,6,
              22,11,4,25};
//initial permutation
int ip[64]={58,50,42,34,26,18,10,2,
            60,52,44,36,28,20,12,4,
            62,54,46,38,30,22,14,6,
            64,56,48,40,32,24,16,8,
            57,49,41,33,25,17,9,1,
            59,51,43,35,27,19,11,3,
            61,53,45,37,29,21,13,5,
            63,55,47,39,31,23,15,7};
//final permutation
int fp[64]={40,8,48,16,56,24,64,32,
            39,7,47,15,55,23,63,31,
            38,6,46,14,54,22,62,30,
            37,5,45,13,53,21,61,29,
            36,4,44,12,52,20,60,28,
            35,3,43,11,51,19,59,27,
            34,2,42,10,50,18,58,26,
            33,1,42,9,49,17,57,25};


void sub_key_gen(int *k64,int **all_key);
void permutation(int* msg,int msg_size,int* rslt, int rslt_size,const char* table_name);
void fiestel_cipher(int* L,int* R,int** key,int round,int* fb);
void scnd_XOR(int* L,int* R,int* Result,int** key,int round_no);
void first_XOR(int* ER,int** key,int round_no,int* Result);
void s_box(int *R,int *newR);

int main()
{
    std::cout<<"Enter Choice Encryption(E) / Decryption(D) :";
    std::cin>>choice;
    int *msg;
    msg=new int[64];
    int *key64;
    key64=new int[64];

    if(choice=='E')
    IO::input(msg,16,"PLAIN TEXT [16 hex digits]");
    else if(choice=='D')
    IO::input(msg,16,"CIPHER TEXT [16 hex digits]");

    std::cout<<std::endl<<std::endl;
    IO::input(key64,16,"KEY [16 hex digits]");

    //initial permutation to msg
    int *msg_permutted;
    msg_permutted=new int[64];
    permutation(msg,64,msg_permutted,64,"ip");
    std::cout<<"\n\nIP(Plain Text) 64-->64\n";
    for(int i=0;i<64;i++)
    {
    if(i!=0 && i%4==0)
    std::cout<<" ";
    std::cout<<msg_permutted[i];
    }

    //sub key generation
    int **Key;
    Key=new int*[17];
    for(int i=0;i<17;i++)
    {
      Key[i]=new int[48];
    }
    sub_key_gen(key64,Key);

    //splitting the message into L0 and R0
    int *L0;
    int *R0;
    L0=new int[32];
    R0=new int[32];
    for(int i=0;i<32;i++)
    {
    L0[i]=msg_permutted[i];
    R0[i]=msg_permutted[32+i];
    }

    //fiestel cypher 16 rounds returns 64bit block
    int *f_b;
    f_b=new int[64];
    fiestel_cipher(L0,R0,Key,0,f_b);

    //final_permutation on fb
    int *msg_finally_permutted;
    msg_finally_permutted=new int[64];
    permutation(f_b,64,msg_finally_permutted,64,"fp");

    std::cout<<"\n\nOUTPUT after final permutation using fp:\n";
    for(int i=0;i<64;i++)
    {
    if(i!=0 && i%4==0)
    std::cout<<" ";
    std::cout<<msg_finally_permutted[i];
    }

    std::cout<<"\n\n==================\n";
    std::cout<<"Cipher TEXT :";
    IO::show_in_hex_from_bin(msg_finally_permutted,64);
    std::cout<<"\n==================\n";
    std::cout<<std::endl<<std::endl;
    return 0;
}


void permutation(int* msg,int msg_size,int* rslt, int rslt_size,const char* table_name)
{
int *temp;
temp=new int[rslt_size];
for(int i=0;i<rslt_size;i++)
{
if(table_name=="pc1")
temp[i]=msg[pc1[i]-1];
else if(table_name=="pc2")
temp[i]=msg[pc2[i]-1];
else if(table_name=="e_bit")
temp[i]=msg[e_bit[i]-1];
else if(table_name=="p_box")
temp[i]=msg[p_box[i]-1];
else if(table_name=="ip")
temp[i]=msg[ip[i]-1];
else if(table_name=="fp")
temp[i]=msg[fp[i]-1];
}
for(int i=0;i<rslt_size;i++)
{
rslt[i]=temp[i];
}
}


void s_box(int *R,int *newR)
{
for(int i=0;i<8;i++)
{
int row=R[i*6]*2 +R[i*6+5];
int collumn=R[i*6+1]*8 +R[i*6+2]*4+R[i*6+3]*2 +R[i*6+4];
int data=0;
switch(i)
{

case 0:
    data=sbox1[row][collumn];
    break;
case 1:
    data=sbox2[row][collumn];
    break;
case 2:
    data=sbox3[row][collumn];
    break;
case 3:
    data=sbox4[row][collumn];
    break;
case 4:
    data=sbox5[row][collumn];
    break;
case 5:
    data=sbox6[row][collumn];
    break;
case 6:
    data=sbox7[row][collumn];
    break;
case 7:
    data=sbox8[row][collumn];
    break;
}

IO::decToBinary(data,&newR[i*4]);
}
}

void sub_key_gen(int *k64,int **all_key)
{
int *k56;
k56=new int[56];
permutation(k64,64,k56,56,"pc1");
//printing pc1
std::cout<<"\n\nPC1(KEY) 64-->56\n";
for(int i=0;i<56;i++)
{
    if(i!=0 && i%4==0)
    std::cout<<" ";
    std::cout<<k56[i];
}
std::cout<<"\n\n";

//end of printing pc1
int **k56s;
k56s=new int*[17];
for(int i=0;i<17;i++)
k56s[i]=new int[56];
//c&d
IO::barrel_shifter(&k56[0],&k56s[0][0],shift_amount[0]);//c0
IO::barrel_shifter(&k56[28],&k56s[0][28],shift_amount[0]);//d0
for(int i=0;i<16;i++)
{
    IO::barrel_shifter(&k56s[i][0],&k56s[i+1][0],shift_amount[i+1]);//cn
    IO::barrel_shifter(&k56s[i][28],&k56s[i+1][28],shift_amount[i+1]);//dn
}

//printing all keys
std::cout<<"ALL SUB KEYS Before PC2 (28 + 28 =56)";
for(int i=0;i<17;i++)
{
std::cout<<"\nc"<<i<<"\n";
for(int j=0;j<56;j++)
{
if(j!=0 && j%4==0)
std::cout<<" ";

if(j==28)
std::cout<<"\nd"<<i<<"\n";

std::cout<<k56s[i][j];
}
std::cout<<"\n";
}
//end printing all keys

for(int i=0;i<17;i++)
{
    permutation(k56s[i],56,all_key[i],48,"pc2");
}
}
void first_XOR(int* ER,int** key,int round_no,int* Result)
{
for(int i=0;i<48;i++)
{
    if(choice=='E')
    Result[i]=ER[i]^key[round_no][i];
    else if(choice=='D')
    Result[i]=ER[i]^key[17-round_no][i];
}
}
void scnd_XOR(int* L,int* R,int* Result,int** key,int round_no)
{
//R ke e_bit_substitute kora lagbe
int *ER;
ER=new int[48];
permutation(R,32,ER,48,"e_bit");

std::cout<<"\nE_BIT_SELECTION(R"<<round_no-1<<") 32-->46\n";
for(int i=0;i<48;i++)
{
if(i!=0 && i%4==0)
std::cout<<" ";
std::cout<<ER[i];
}


//round_func=xor between Er and round key
first_XOR(ER,key,round_no,ER);
std::cout<<"\n\nROUND_KEY"<<round_no<<" XOR extended_R"<<round_no-1<<"\n";
for(int i=0;i<48;i++)
{
if(i!=0 && i%4==0)
std::cout<<" ";
std::cout<<ER[i];
}


//sbox and p_box substituion for Round_F;
s_box(ER,R);
std::cout<<"\n\nSBOX(extended_R"<<round_no-1<<" XOR ROUND_KEY"<<round_no<<") 46-->32\n";
for(int i=0;i<32;i++)
{
if(i!=0 && i%4==0)
std::cout<<" ";
std::cout<<R[i];
}

int* S_P_Func;
S_P_Func=new int[32];
permutation(R,32,S_P_Func,32,"p_box");

std::cout<<"\n\nF=PBOX(SBOX(extended_R"<<round_no-1<<" XOR ROUND_KEY"<<round_no<<"))\n";
for(int i=0;i<32;i++)
{
if(i!=0 && i%4==0)
std::cout<<" ";
std::cout<<S_P_Func[i];
}



//xor btn L and S_P_Func
std::cout<<"\n\nF xor L"<<round_no-1<<"\n";
for(int i=0;i<32;i++)
{
if(i!=0 && i%4==0)
std::cout<<" ";
R[i]=S_P_Func[i]^L[i];
std::cout<<R[i];
}
}


void fiestel_cipher(int* L,int* R,int** key,int round,int* fb)
{
    if(round==16)
    {
        std::cout<<"\n\nFinally AFTER ROUND16 swap L16 with R16\n";
        for(int j=0;j<32;j++)
        fb[j]=R[j];
        for(int i=0;i<32;i++)
        fb[i+32]=L[i];
        return;
    }
    round++;

    //visualise round key
    std::cout<<"\n\n=======\nROUND"<<round<<"\n=======\n";
    std::cout<<"ROUND"<<round<<" KEY IN BIN | PC2(C"<<round<<"D"<<round<<") 56-->48\n";
    for(int i=0;i<48;i++)
    {
        if(i!=0 && i%4==0)
        std::cout<<" ";
        std::cout<<key[round][i];
    }
    std::cout<<"\n\nROUND"<<round<<" KEY IN HEX";
    IO::show_in_hex_from_bin(key[round],48);


    //inputs l and r in this round
    std::cout<<"\n\nROUND"<<round<<" INPUTS";
    std::cout<<"\nL"<<round-1<<"\n";
    for(int i=0;i<32;i++)
    {
        if(i!=0 && i%4==0)
        std::cout<<" ";
        std::cout<<L[i];
    }
    std::cout<<"\nR"<<round-1<<"\n";
    for(int i=0;i<32;i++)
    {
        if(i!=0 && i%4==0)
        std::cout<<" ";
        std::cout<<R[i];
    }
    std::cout<<"\n";


    //saving l and r to temp variable
    int templ[32],tempr[32];
    for(int i=0;i<32;i++)
    {
    templ[i]=L[i];
    tempr[i]=R[i];
    }

    scnd_XOR(L,R,R,key,round);//R1=L0 xor f(E(R0),k1)
    for(int i=0;i<32;i++)
    L[i]=tempr[i];

    std::cout<<"\n\nL"<<round<<"<--R"<<round-1<<" || R"<<round<<"--F\n";

    std::cout<<"\nOUTPUT OF ROUND"<<round<<" \n";
    std::cout<<"\nL"<<round<<" :";
    IO::show_in_hex_from_bin(L,32);
    std::cout<<"\nR"<<round<<" :";
    IO::show_in_hex_from_bin(R,32);
    fiestel_cipher(L,R,key,round,fb);
}
