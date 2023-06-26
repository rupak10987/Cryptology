#include<iostream>
int main()
{
    char ch;
    while(1)
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

    //encryption
    text_counter=0;
    char final_text[128];
    while(true)
    {
    int encr;
    if(ch=='E')
    {
    encr=(int)main_text[text_counter]+k;
    if(encr>(int)'z')
    encr=((int)'a'-1)+encr-(int)'z';
    encr=encr%((int)'z'+1);
    }
    else if(ch=='D')
    {
    encr=(int)main_text[text_counter]-k;
    if(encr<(int)'a')
    encr=encr+((int)'z'-(int)'a')+1;
    encr=encr%((int)'z'+1);
    }

    final_text[text_counter]=(char)encr;
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

    return 0;
}
