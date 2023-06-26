#include<iostream>
int main()
{
    char maping[26][2];
    maping[0][0]='a';maping[0][1]='b';
    maping[1][0]='b';maping[1][1]='f';
    maping[2][0]='c';maping[2][1]='e';
    maping[3][0]='d';maping[3][1]='g';
    maping[4][0]='e';maping[4][1]='c';
    maping[5][0]='f';maping[5][1]='x';
    maping[6][0]='g';maping[6][1]='d';
    maping[7][0]='h';maping[7][1]='a';
    maping[8][0]='i';maping[8][1]='z';
    maping[9][0]='j';maping[9][1]='h';
    maping[10][0]='k';maping[10][1]='o';
    maping[11][0]='l';maping[11][1]='n';
    maping[12][0]='m';maping[12][1]='y';
    maping[13][0]='n';maping[13][1]='l';
    maping[14][0]='o';maping[14][1]='m';
    maping[15][0]='p';maping[15][1]='k';
    maping[16][0]='q';maping[16][1]='v';
    maping[17][0]='r';maping[17][1]='w';
    maping[18][0]='s';maping[18][1]='s';
    maping[19][0]='t';maping[19][1]='u';
    maping[20][0]='u';maping[20][1]='t';
    maping[21][0]='v';maping[21][1]='r';
    maping[22][0]='w';maping[22][1]='j';
    maping[23][0]='x';maping[23][1]='p';
    maping[24][0]='y';maping[24][1]='q';
    maping[25][0]='z';maping[25][1]='i';
char ch;
while(true)
{
 std::cout<<"Encrypt or decrypt[E/D]? :" ;
    std::cin>>ch;
    int k;
    char initial_text[128];
    int text_counter=0;
    std::cout<<"enter Value of K :";
    std::cin>>k;
    if(ch=='E')
    std::cout<<"enter plain text : ";
    else if(ch=='D')
    std::cout<<"enter cipher text : ";
    getchar();
    while(true)
    {
    char in_c=getchar();
    if(in_c=='\n')
    break;
    initial_text[text_counter]=in_c;
    text_counter++;
    }
    initial_text[text_counter]='\0';
    const char* main_text=initial_text;

    //alter
    text_counter=0;
    char final_text[128];
    while(true)
    {
    int indx;
    if(ch=='E')
    {
    indx=(int)main_text[text_counter]-(int)'a';
    final_text[text_counter]=maping[indx][1];
    }
    else if(ch=='D')
    {
    for(int i=0;i<26;i++)
    {
        if(main_text[text_counter]==maping[i][1])
        {
           indx=i;
           break;
        }
    }
    final_text[text_counter]=maping[indx][0];
    }


    if(main_text[text_counter]=='\0')
    {
    final_text[text_counter]='\0';
    break;
    }
    text_counter++;
    }
    const char* out_text=final_text;
    if(ch=='E')
    std::cout<<"\ncipher text : "<<out_text<<std::endl;
    else if(ch=='D')
    std::cout<<"\nplain text : "<<out_text<<std::endl;

}
}
