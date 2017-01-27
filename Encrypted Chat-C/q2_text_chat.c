#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {

  if((argv[3]==NULL)||(argc<3)){
    printf("ERROR\n");
    return 0;
  }
  //checking input

  int i,num,len;
  char received[1000],sent[1000],str[1010],temp[1000];
  char *s=(char *)malloc(sizeof(char)*1000);
  char c;

  FILE *f,*g;
  f=fopen(argv[1],"r");
  memset(temp, '\0', sizeof(temp));

  if(f==NULL){
    printf("Nothing received yet.\n");
    f=fopen(argv[1],"w");
    fclose(f);
  }
  //see if f exist
  else{
    f=fopen(argv[1],"r");
    num=0;
	  while(((c=fgetc(f))!=EOF)&&(c!='\0')){
      received[num]=c;
      num++;
    }
    received[num]='\0';

    if(received[0]!='['){
      printf("Nothing received yet.\n");
    }
    //get the message from incoming file and see if it is valid
    else{
      printf("Recieved: ");
      printf("%s",received);
    }
    fclose(f);
    f=fopen(argv[1],"w");
    fclose(f);
    //clear the content of f
  }
    //get the message from incoming file and see if it is valid
    //if valid, show it and clear it; If not valid, clear the file.

while(1){
    //sending
    printf("Send:      ");
    //fgets (sent,1000,stdin);
    num=0;
    while(((c=getchar())!='\n')){
      if(c==EOF){
        printf("\nSession terminated due to end of the input stream.\n");
        return 0;
      }
      sent[num]=c;
      num++;
    }
    sent[num]='\n';
    sent[num+1]='\0';

    //printf("%s\n",sent);
    //take the input from stdin

    len=strlen(argv[3]);
    str[0]='[';
    for(i=1;i<len+1;i++){
      str[i]=argv[3][i-1];
    }
    str[len+1]=']';
    str[len+2]=' ';
    str[len+3]='\0';
   //constrct str=[username]

    strcat(str,sent);
    //append sent after user name;

    g=fopen(argv[2],"w");
    fputs(str,g);
	  strcpy(str, "");
    fclose(g);
    //write the string into outcome file.


    //checking and receiving
    while(1){
      //printf("looping...\n");
      f=fopen(argv[1],"r");
      num=0;
      while(((c=fgetc(f))!=EOF)&&(c!='\0')){
        received[num]=c;
        num++;
      }
      received[num]='\0';
      //get received message
		  //printf("%s\n",temp);
      if((strcmp(received,temp)!=0)&&(received[0]=='[')){//modify to better checking
        printf("Recieved: ");
        printf("%s",received );
        fclose(f);
        strcpy(temp,received);
        break;
      }
      //if new message received, print it and quit the loop.
      fclose(f);
    }
  }
}
