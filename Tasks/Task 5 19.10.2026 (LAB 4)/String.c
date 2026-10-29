
#define NULL ((void *)0)






const unsigned char *user_memchr(const unsigned char  *s,unsigned char c,int size)
{

    const unsigned char *result = NULL;
    unsigned char flag=0;

    for(int i=0;i<size&&(0==flag);i++)
    {
        if(s[i]==c)
        {
            result =&s[i];
            flag=1;
        }
        else
        {;}
    }
    return result;
}


unsigned char user_memcmp(const unsigned char *s1,const unsigned char *s2,int size)
{
    unsigned char result=0;

    for(int i=0;(i<size)&&(0==result);i++)
    {
        if(s1[i]>s2[i])
        {
            result=1;
        }
        else if(s1[i]<s2[i])
        {
            result=-1;
        }
        else{;}


    }
    return result;
}

void user_memcpy(unsigned char *dest,const unsigned char *src,int size)
{
    for(int i=0;i<size;i++)
    {
        dest[i]=src[i];
    }
}

void user_memmove(unsigned char *dest,const unsigned char *src,int size)
{
    if(dest<src)
    {
        for(int i=0;i<size;i++)
        {
            dest[i]=src[i];
        }
    }
    else
    {
        for(int i=size-1;i>=0;i--)
        {
            dest[i]=src[i];
        }
    }
}

void user_memset(unsigned char *dest,unsigned char c,int size)
{
    for(int i=0;i<size;i++)
    {
        dest[i]=c;
    }
}

void user_strcat(unsigned char *dest,const unsigned char *src)
{
    int i=0;
    while(dest[i])
    {
        i++;
    }
    int j=0;
    while(src[j])
    {
        dest[i]=src[j];
        i++;
        j++;
    }
    dest[i]='\0';
}

void user_strchr(const unsigned char *s,unsigned char c,const unsigned char **result)
{
    *result=NULL;
    unsigned char flag=0;
    for(int i=0;(s[i])&&(0==flag);i++)
    {
        if(s[i]==c)
        {
            *result=&s[i];
            flag=1;
        }
        else{;}
    }
}
int user_strcmp(const unsigned char *s1,const unsigned char *s2)
{
    int result=0;
    for(int i=0;(s1[i])&&(s2[i])&&(0==result);i++)
    {
        if(s1[i]>s2[i])
        {
            result=1;
        }
        else if(s1[i]<s2[i])
        {
            result=-1;
        }
        else{;}
    }
    return result;
}

void user_strcpy(unsigned char *dest,const unsigned char *src)
{
    int i=0;
    while(src[i])
    {
        dest[i]=src[i];
        i++;
    }
    dest[i]='\0';
}

int user_strcspn(const unsigned char *s,const unsigned char *accept)
{
    int result=0;
    unsigned char flag=0;
    for(int i=0;(s[i])&&(0==flag);i++)
    {
        for(int j=0;(accept[j])&&(0==flag);j++)
        {
            if(s[i]==accept[j])
            {
                flag=1;
            }
            else{;}
        }
        if(0==flag)
        {
            result++;
        }
    }
    return result;
}

int user_strlen(const unsigned char *s)
{
    int i=0;
    while(s[i])
    {
        i++;
    }
    return i;
}


void user_strncat(unsigned char *dest,const unsigned char *src,int n)
{
    int i=0;
    while(dest[i])
    {
        i++;
    }
    int j=0;
    while((src[j])&&(j<n))
    {
        dest[i]=src[j];
        i++;
        j++;
    }
    dest[i]='\0';
}

int user_strncmp(const unsigned char *s1,const unsigned char *s2,int n)
{
    int result=0;
    for(int i=0;(s1[i])&&(s2[i])&&(i<n)&&(0==result);i++)
    {
        if(s1[i]>s2[i])
        {
            result=1;
        }
        else if(s1[i]<s2[i])
        {
            result=-1;
        }
        else{;}
    }
    return result;
}

void user_strncpy(unsigned char *dest,const unsigned char *src,int n)
{
    int i=0;
    while((src[i])&&(i<n))
    {
        dest[i]=src[i];
        i++;
    }
    dest[i]='\0';
}

void user_strrchr(const unsigned char *s,unsigned char c,const unsigned char **result)
{
    *result=NULL;
    unsigned char flag=0;
    for(int i=user_strlen(s)-1;(i>=0)&&(0==flag);i--)
    {
        if(s[i]==c)
        {
            *result=&s[i];
            flag=1;
        }
        else{;}
    }
}
const unsigned char *user_strstr(const unsigned char *s,const unsigned char *substr)
{
    const unsigned char *result=NULL;
    unsigned char flag=0;
    int s_len=user_strlen(s);
    int substr_len=user_strlen(substr);
    for(int i=0;(i<s_len)&&(0==flag);i++)
    {
        if(s[i]==substr[0])
        {
            if(user_strncmp(&s[i],substr,substr_len)==0)
            {
                result=&s[i];
                flag=1;
            }
        }
        else{;}
    }
    return result;
}

const unsigned char *user_strtok(const unsigned char *s,const unsigned char *delim)
{
    const unsigned char *result=NULL;
    unsigned char flag=0;
    int s_len=user_strlen(s);
    int delim_len=user_strlen(delim);
    for(int i=0;(i<s_len)&&(0==flag);i++)
    {
        for(int j=0;(j<delim_len)&&(0==flag);j++)
        {
            if(s[i]==delim[j])
            {
                result=&s[i];
                flag=1;
            }
        }
    }
    return result;
}
