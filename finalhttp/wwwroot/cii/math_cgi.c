#include<stdio.h>
#include<string.h>
#include<stdlib.h>


void math_op(char *buf)
{
    int x, y;
    sscanf(buf,"x=%d&y=%d",&x,&y);
    printf("<html>\n");

    printf("<h1>%d + %d = %d</h1>",x,y,x+y);
    printf("<h1>%d - %d = %d</h1>",x,y,x-y);
    printf("<h1>%d * %d = %d</h1>",x,y,x*y);
    if(y==0)
    {
        printf("<h1>%d / %d = error</h1>",x,y);
        printf("<h1>%d % %d = error</h1>",x,y);

    }
    else
    {
        printf("<h1>%d / %d = %d</h1>",x,y,x/y);
        printf("<h1>%d % %d = %d</h1>",x,y,x%y);

    }
    printf("</html>\n");

}

int main()
{
    //huode http canshu 
    char buf[1024];
    if(getenv("METHOD"))
    {
        if(strcasecmp(getenv("METHOD"),"GET")==0)
        {
            strcpy(buf,getenv("QUERY_STRING"));
        }
        else
        {
            int len=atoi(getenv("CONTENT_LENGTH"));
            int i=0;
            for(;i<len;i++)
            {
                read(0,buf+i,1);
            }
            buf[i]='\0';
        }
        printf("arg:%s\n",buf);
        math_op(buf);
    }
}








