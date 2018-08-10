#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct dic
{
    char* key;
    char* content;
    struct dic* next;
};

int open_file(struct dic** p,const char* filename)
{

    FILE* pfile=fopen(filename,"r");
    if(pfile==NULL)
    {
        return 0;
    }
    char buf[1024]={0};
    size_t len=0;
    int count=0;

    *p=(struct dic*)malloc(sizeof(struct dic));
    memset(*p,0x00,sizeof(struct dic));

    struct dic *pd=*p;
    while(!feof(pfile))
    {
        memset(buf,0x00,sizeof(buf));
        fgets(buf,sizeof(buf),pfile);
        len=strlen(buf);
        if(len>0)
        {
            pd->key=(char*)malloc(len);
            memset(pd->key,0x00,len);
            strcpy(pd->key,&buf[1]);
        }
        memset(buf,0x00,sizeof(buf));
        fgets(buf,sizeof(buf),pfile);
        len=strlen(buf);
        if(len>0)
        {
            pd->content=(char*)malloc(len);
            memset(pd->content,0x00,len);
            strcpy(pd->content,&buf[6]);
        }
        pd->next=(struct dic*)malloc(sizeof(struct dic));
        memset(pd->next,0x00,sizeof(pd->next));
        pd=pd->next;
        count++;
    }
    fclose(pfile);
    return count;
}

int find_word(struct dic* p, int size,const char* key,char* content)
{
    const struct dic* pd=p;
    while(pd)
    {
        if(pd->key && pd->content)
        {
            if(strncmp(pd->key,key,strlen(key))==0)
            {
                strcpy(content,pd->content);
                return 1;
            }
        }
        pd=pd->next;
    }
    return 0;
}

void free_dic(struct dic* p,int size)
{
    struct dic* pd=p;
    while(pd)
    {
        if(pd->key)
        {
            free(pd->key);
        }
        if(pd->content)
            free(pd->content);
        struct dic* tmp=pd->next;
        free(pd);
        pd=tmp;
    }
}

int main()
{
    long start_ms=0;
    long end_ms=0;

    start_ms=clock();
    struct dic* p=NULL;
    int size=open_file(&p,"dict.txt");
    end_ms=clock();
    printf("open dictionary used %ld ms\n",end_ms-start_ms);

    char key[1024];
    char content[1024];

    while(1)
    {
        memset(key,0x00,sizeof(key));
        memset(content,0x00,sizeof(content));

        scanf("%s",key);
        if(strncmp(key,"command=exit",12)==0)
        {
            break;
        }
        start_ms=clock();
        if(find_word(p,size,key,content)==1)
        {
            printf("%s",content);
        }
        else
        {
            printf("not found\n");
        }
        end_ms=clock();
        printf("used %ld ms\n",end_ms-start_ms);

    }
    start_ms=clock();
    free_dic(p,size);
    end_ms=clock();
    printf("exit dictionary used %ld ms\n",end_ms-start_ms);

    return 0;
}
