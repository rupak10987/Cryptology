namespace IO{

void decToBinary(int n,int *start,int a_size)
{
    //initialize the array
    for(int j=0;j<4;j++)
    start[j]=0;
    // counter for binary array
    int i = 0;
    while (n > 0) {

        // storing remainder in binary array
        start[a_size-1-i] = n % 2;
        n = n / 2;
        i++;
    }
}

void hexToBinary(char hexInput,int *bin_array) {
    switch (hexInput) {
        case '0':
            bin_array[0]=0;
            bin_array[1]=0;
            bin_array[2]=0;
            bin_array[3]=0;
            break;
        case '1':
            bin_array[0]=0;
            bin_array[1]=0;
            bin_array[2]=0;
            bin_array[3]=1;
            break;
        case '2':
            bin_array[0]=0;
            bin_array[1]=0;
            bin_array[2]=1;
            bin_array[3]=0;
            break;
        case '3':
            bin_array[0]=0;
            bin_array[1]=0;
            bin_array[2]=1;
            bin_array[3]=1;
            break;
        case '4':
            bin_array[0]=0;
            bin_array[1]=1;
            bin_array[2]=0;
            bin_array[3]=0;
            break;
        case '5':
            bin_array[0]=0;
            bin_array[1]=1;
            bin_array[2]=0;
            bin_array[3]=1;
            break;
        case '6':
            bin_array[0]=0;
            bin_array[1]=1;
            bin_array[2]=1;
            bin_array[3]=0;
            break;
        case '7':
            bin_array[0]=0;
            bin_array[1]=1;
            bin_array[2]=1;
            bin_array[3]=1;
            break;
        case '8':
            bin_array[0]=1;
            bin_array[1]=0;
            bin_array[2]=0;
            bin_array[3]=0;
            break;
        case '9':
            bin_array[0]=1;
            bin_array[1]=0;
            bin_array[2]=0;
            bin_array[3]=1;
            break;
        case 'A':
        case 'a':
            bin_array[0]=1;
            bin_array[1]=0;
            bin_array[2]=1;
            bin_array[3]=0;
            break;
        case 'B':
        case 'b':
            bin_array[0]=1;
            bin_array[1]=0;
            bin_array[2]=1;
            bin_array[3]=1;
            break;
        case 'C':
        case 'c':
            bin_array[0]=1;
            bin_array[1]=1;
            bin_array[2]=0;
            bin_array[3]=0;
            break;
        case 'D':
        case 'd':
            bin_array[0]=1;
            bin_array[1]=1;
            bin_array[2]=0;
            bin_array[3]=1;
            break;
        case 'E':
        case 'e':
            bin_array[0]=1;
            bin_array[1]=1;
            bin_array[2]=1;
            bin_array[3]=0;
            break;
        case 'F':
        case 'f':
            bin_array[0]=1;
            bin_array[1]=1;
            bin_array[2]=1;
            bin_array[3]=1;
            break;
        default:
            printf("Invalid hexadecimal input.");
            break;
    }
}


void input(int* msg,int msg_size,const char* data_name)
{
char c;
std::cout<<"ENTER "<<data_name<<" : ";
for(int i=0;i<msg_size;i++)//16
{
std::cin>>c;
hexToBinary(c,&msg[i*4]);
}
for(int i=0;i<msg_size*4;i++)//16
{
if(i!=0 && i%4==0)
std::cout<<" ";
std::cout<<msg[i];
}
}

void barrel_shifter(int *msg,int *rslt,int s)
{
for(int i=0+s;i<28;i++)
{
    rslt[i-s]=msg[i];
}
if(s==2)
{
    rslt[26]=msg[0];
    rslt[27]=msg[1];
}
else if(s==1)
rslt[27]=msg[0];
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

};
