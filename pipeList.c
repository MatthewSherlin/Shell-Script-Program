//Matthew Michael Sherlin
//Systems Programming
//Homework 5

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define BUFSIZE 128

char *concatenateOne(char *a){
  int size = strlen(a)+ 1;
  char *str = malloc(size);
  strcpy (str, a);
  return str;
}

char *concatenateTwo(char *a, char *b){
  int size = strlen(a) + strlen(b) + 1;
  char *str = malloc(size);
  strcpy (str, a);
  strcat (str, " ");
  if(b[1] == 's') strcat(str, "-S");
  else strcat (str, b);
  return str;
}

char *concatenateThree(char *a, char *b, char *c){
  int size = strlen(a) + strlen(b) + strlen(c) + 1;
  char *str = malloc(size);
  strcpy (str, a);
  strcat (str, " ");
  strcat (str, b);
  strcat (str, " ");
  if(c[1] == 's') strcat(str, "-S");
  else strcat (str, c); 
  return str;
}

int main(int argc, char *argv[]) {
    
    //
    //initializing all needed variables and command
    //
    
    char *cmdBegin="ls -lh";
    char *cmdDir;
    char *cmdSort;
    char *cmdAll;
    
    if(argc==1) cmdAll=concatenateOne(cmdBegin);
    
    if(argc==2 && argv[1][1] != '-'){
        int strsize=0;
        strsize += strlen(argv[1]);
        cmdDir = malloc(strsize);
        cmdDir[0] = '\0';
        strcat(cmdDir, argv[1]);
        
        cmdAll=concatenateTwo(cmdBegin, cmdDir);  
    }
    
    if(argc==2 && argv[1][1] == '-'){
        int strSort=0;
        strSort += strlen(argv[2]);
        cmdSort = malloc(strSort);
        cmdSort[0] = '\0';
        strcat(cmdSort, argv[2]);
        
        int strsize=0;
        strsize += strlen(argv[1]);
        cmdDir = malloc(strsize);
        cmdDir[0] = '\0';
        strcpy(cmdDir, ".");
      
       cmdAll=concatenateThree(cmdBegin, cmdDir, cmdSort);
    }
    
    if(argc==3){
      int strDir=0;
      strDir += strlen(argv[1]);
      cmdDir = malloc(strDir);
      cmdDir[0] = '\0';
      strcat(cmdDir, argv[1]);
      
      int strSort=0;
      strSort += strlen(argv[2]);
      cmdSort = malloc(strSort);
      cmdSort[0] = '\0';
      strcat(cmdSort, argv[2]);
      
      cmdAll=concatenateThree(cmdBegin, cmdDir, cmdSort);
    }
    
    //
    // running commands
    //
    
    char buf[BUFSIZE];
    FILE *fp;
    printf("\n");
    if ((fp = popen(cmdAll, "r")) == NULL) {
        printf("Error opening pipe\n");
        return -1;
    }

    while (fgets(buf, BUFSIZE, fp) != NULL) {
      int count;
      char *string=buf;
      char *p = string;
      char *tok = NULL;      //pointer to each token in string

    //using strtok to separate string into tokens at spaces
    for (tok = strtok (p, " "); tok; tok = strtok (NULL, " \n")){
        ++count;
        char *output_token = strdup (tok);
        if(count==5){
          if(strlen(output_token) > 3){
          printf("%s ", output_token);
          printf(" ");
          }
          else printf("%s   ", output_token);
        }
        if(count>5) printf("%s ", output_token);
        if(count==7){
          if(strlen(output_token)==1) printf(" ");
        }
        if(count==8){
          if(strlen(output_token)==4) printf(" ");
          printf(" ");
        }
        free (output_token);
        
    }
    count=0;
    printf("\n");
}

    if(pclose(fp))  {
        //printf("Error with command\n");
        return -1;
    }
    printf("\n");
    return 0;
}