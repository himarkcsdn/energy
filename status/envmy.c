#include<stdio.h>
#include<stdlib.h>
//int main(int argc, char* argv[], char *env[])
//{
  //  int i=0;
    //for(;env[i];i++)
   // {
   //     printf("%s\n",env[i]);
   // }
//    return 0;
//}


int main()
{
    printf("%s\n",getenv("PATH"));
    return 0;
}
