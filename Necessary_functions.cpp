#include<iostream>
#include<conio.h>
#include<math.h>
void bin_addition(int* A,int size_A,int* B,int size_B,int* result,int R_size);
void decToBinary(int n,int *start,int s_size);
void Barrel_shifter(int* data,int data_size,int shift_amnt);
void input_charecters(int *bin_array);
void input_IV(int *bin_array);
void boolean_op(int *A,int *B,int *Result,const char* ch);
void show_in_hex_from_bin(int *msg,int msize);
int main()
{
int *M,*A,*B,*C,*D,*E;
M=new int[512];
A=new int[32];
B=new int[32];
C=new int[32];
D=new int[32];
E=new int[32];
int **W;
W=new int*[80];
for(int i=0;i<81;i++)
W[i]=new int[33];

std::cout<<"INPUT IV A:";
input_IV(A);

std::cout<<"\nINPUT IV B:";
input_IV(B);
std::cout<<"\nINPUT IV C:";
input_IV(C);
std::cout<<"\nINPUT IV D:";
input_IV(D);
std::cout<<"\nINPUT IV E:";
input_IV(E);

input_charecters(M);
std::cout<<"\n";

for(int i=0;i<16;i++)
{
std::cout<<"\nW["<<i<<"]= ";
for(int j=i*32;j<i*32+32;++j)
{
    W[i][j]=M[j];
    std::cout<<M[j]<<",";
}
}


for(int i=16;i<80;i++)
{
boolean_op(W[i-16],W[i-14],W[i],"xor");
boolean_op(W[i-8],W[i],W[i],"xor");
boolean_op(W[i-3],W[i],W[i],"xor");
}

//saving abcde in initial
int initial[160];
for(int i=0;i<160;i++)
{
 switch(i/32)
 {
    case 0:
    initial[i]=A[i%32];
    break;
    case 1:
    initial[i]=B[i%32];
    break;
    case 2:
    initial[i]=C[i%32];
    break;
    case 3:
    initial[i]=D[i%32];
    break;
    case 4:
    initial[i]=E[i%32];
    break;
 }
}
//main rounds
int* FUNC;
int* NOT_term;
int *FUNC_Term1,*FUNC_Term2;
NOT_term=new int[32];
FUNC=new int[32];
FUNC_Term1=new int[32];
FUNC_Term2=new int[32];

for(int i=0;i<80;i++)
{

switch(i/20)
{
case 0:
    //bc or b'd
    boolean_op(B,C,FUNC_Term1,"and");
    boolean_op(B,nullptr,NOT_term,"not");
    boolean_op(NOT_term,D,FUNC_Term2,"and");
    boolean_op(FUNC_Term1,FUNC_Term2,FUNC,"or");
    break;
case 1:
    //b xor c xor d
    boolean_op(B,C,FUNC_Term1,"xor");
    boolean_op(FUNC_Term1,D,FUNC,"xor");
    break;
case 2:
    //bc or bd or cd
    boolean_op(B,C,FUNC_Term1,"and");
    boolean_op(B,D,FUNC_Term2,"and");
    boolean_op(C,D,NOT_term,"and");
    boolean_op(FUNC_Term1,FUNC_Term2,FUNC,"or");
    boolean_op(FUNC,NOT_term,FUNC,"or");
    break;
case 3:
    //b xor c xor d
    boolean_op(B,C,FUNC_Term1,"xor");
    boolean_op(FUNC_Term1,D,FUNC,"xor");
    break;
}


int *TEMP;
TEMP=new int[32];

for(int n=0;n<32;n++)
TEMP[n]=A[n];

Barrel_shifter(TEMP,32,5);

bin_addition(TEMP,32,FUNC,32,TEMP,32);
bin_addition(TEMP,32,E,32,TEMP,32);
bin_addition(TEMP,32,W[i],32,TEMP,32);
//bin_addition(TEMP,32,K[i],32,TEMP,32);

for(int n=0;n<32;n++)
E[n]=D[n];

for(int n=0;n<32;n++)
D[n]=C[n];

Barrel_shifter(B,32,30);
for(int n=0;n<32;n++)
C[n]=B[n];

for(int n=0;n<32;n++)
B[n]=A[n];

for(int n=0;n<32;n++)
A[n]=TEMP[n];
}


for(int i=0;i<160;i++)
{
    switch(i/32)
    {
    case 0:
    bin_addition(&initial[0],32,A,32,&initial[0],32);
    break;
    case 1:
    bin_addition(&initial[32],32,B,32,&initial[32],32);
    break;
    case 2:
    bin_addition(&initial[64],32,C,32,&initial[64],32);
    break;
    case 3:
    bin_addition(&initial[96],32,D,32,&initial[96],32);
    break;
    case 4:
    bin_addition(&initial[128],32,E,32,&initial[128],32);
    break;
    }

}


std::cout<<"DIGEST \n";
show_in_hex_from_bin(initial,160);

return 0;
}






void boolean_op(int *A,int *B,int *Result,const char* ch)
{
    if(ch=="or")
    {
    for(int i=0;i<32;i++)
        Result[i]=A[i] | B[i];
    }
    else if(ch=="and")
    {
        for(int i=0;i<32;i++)
        Result[i]=A[i] & B[i];
    }
    else if(ch=="not")
    {
    for(int i=0;i<32;i++)
        Result[i]=~A[i];
    }
    else if(ch=="xor")
    {
    for(int i=0;i<32;i++)
    Result[i]=A[i]^B[i];
    }
}

void decToBinary(int n,int *start,int s_size)
{
    //initialize the array
    for(int j=0;j<s_size;j++)
    start[j]=0;
    // counter for binary array
    int i = 0;
    while (n > 0) {

        // storing remainder in binary array
        start[s_size-1-i] = n % 2;
        n = n / 2;
        i++;
    }
}

void bin_addition(int* A,int size_A,int* B,int size_B,int* result,int R_size)
{
int decA=0;
int decB=0;
for(int i=0;i<size_A;i++)
{
decA+=A[size_A-1-i]*pow(2,i);
}
for(int i=0;i<size_B;i++)
{
decB+=B[size_B-1-i]*pow(2,i);
}
int sum=decA+decB;
decToBinary(sum,result,R_size);
}

void input_charecters(int *bin_array)
{
std::cout<<"\nINPUT PASSWORD [max 56 ascii charecters] :";
char *chars;
chars=new char[56];
int i=0;
while(1)
{
    char c=std::cin.get();
    if (c == '\n')
    break;
    chars[i]=c;
    i++;
}
int m_size=i*8;
std::cout<<"password size="<<m_size<<"\n";

for(int j=0;j<m_size/8;j++)
{
decToBinary((int)chars[j],&bin_array[j*8],8);
}

for(int j=m_size+1;j<512-64;j++)
{
bin_array[j]=0;
}

decToBinary(m_size,&bin_array[512-64],64);

bin_array[m_size]=1;

}





void input_IV(int *bin_array)
{
char *chars;
chars=new char[4];
int i=0;
while(1)
{
    char c=std::cin.get();
    if (c == '\n')
    break;
    chars[i]=c;
    i++;
}

for(int j=0;j<4;j++)
{
decToBinary((int)chars[j],&bin_array[j*8],8);
}
}






void Barrel_shifter(int* data,int data_size,int shift_amnt)
{

int *result;
result=new int[data_size];
int i=shift_amnt;
int j=0;
for(i;i<data_size;i++)
{
    result[j]=data[i];
    j++;
}
i=0;
for(j;j<data_size;j++)
{
    result[j]=data[i];
    i++;
}

for(int k=0;k<data_size;k++)
{
data[k]=result[k];
}
}


void show_in_hex_from_bin(int *msg,int msize)
{
std::cout<<"\n";
for(int k=0;k<msize/4;k++)
{
 int hex[1000];
 int i = 1, j = 0, rem, dec = 0, binaryNumber;
 binaryNumber=msg[k*4]*1000+msg[k*4+1]*100+msg[k*4+2]*10+msg[k*4+3];
 if(binaryNumber==0)
    std::cout<<"0";
  while (binaryNumber > 0)
  {
    rem = binaryNumber % 2;
    dec = dec + rem * i;
    i = i * 2;
    binaryNumber = binaryNumber / 10;
  }
    i = 0;
  while (dec != 0)
  {
    hex[i] = dec % 16;
    dec = dec / 16;
    i++;
  }

  for (j = i - 1; j >= 0; j--)
  {
    if (hex[j] > 9)
      std::cout<<(char)(hex[j] + 55);
    else
      std::cout<<hex[j];
  }
}
}
