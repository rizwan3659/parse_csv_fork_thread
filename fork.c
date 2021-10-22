#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

#define PATH_OF_CSV_FILE "student_record.csv"

int tokenize( char *buffer , char *del , char *subdel  )
{
 char *str1, *str2, *token, *subtoken;
    char *saveptr1, *saveptr2;
    int j;

        token = strtok_r(str1,del , &saveptr1);
 for (j = 1, str1 = buffer; ; j++, str1 = NULL)
 {
        token = strtok_r(str1,del , &saveptr1);
        if (token == NULL)
            break;
        printf("%d: %s\n", j, token);

       for (str2 = token; ; str2 = NULL)
      {
            subtoken = strtok_r(str2, subdel, &saveptr2);
            if (subtoken == NULL)
                break;
            printf(" --> %s\n", subtoken);
        }
  }



}


int function(char *path_of_file, char *section )
{
  int fd;
  char *buffer;
  int size;
  int ret;
  char *p;
  char *q;

  fd =  open(path_of_file,O_RDONLY);
  if(fd == -1)
  {
    fprintf(stderr, "Error on line %d : %s\n", __LINE__, strerror(errno));
    ret = -1;
    goto EXIT;
  }

  size = lseek(fd, 0, SEEK_END); 
  if( size == -1)
  {
    fprintf(stderr, "Error on line %d : %s\n", __LINE__, strerror(errno));
    ret = -1;
    goto EXIT;
  }

  buffer=(char *)malloc(size*sizeof(char));
  if( buffer  == NULL)
  {

    fprintf(stderr, "Error on line %d : %s\n", __LINE__, strerror(errno));
    ret = -1;
    goto EXIT;
  }
 
  if(lseek(fd, 0, SEEK_SET)  == -1 ) 
  {
    fprintf(stderr, "Error on line %d : %s\n", __LINE__, strerror(errno));
    ret = -1;
    goto EXIT;
  }


  ret = read(fd,buffer,size);
  if(ret == -1)
  {
   fprintf(stderr, "Error on line %d : %s\n", __LINE__, strerror(errno));
    
    goto EXIT; 

  }

 ret = tokenize(buffer,"\n",","); 

 EXIT:
  return ret ;
}


int main()
{
  pid_t pid ;
  pid = fork(); 
  if(pid == 0)
  {
    function("student_record.csv","A");    
  }
  else
  {
    function("student_record.csv","B");    
   


  }

}
