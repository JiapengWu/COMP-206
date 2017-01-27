#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* encrypt(char* str,int key) {
  int k,len1,len;
  char reverse[1000];
  char *enc=(char *)malloc(sizeof(char)*1000);

  len1=strlen(str);
  for(int i=0;i<len1;i++){
    k=(int)str[i]+key;
    if((k<=255)&&(k>=0)){
      reverse[i]=(char)k;
    }
    else if (k<0){
      while(k<0){
        k+=256;
      }
      reverse[i]=(char)k;
    }

    else if (k>255){
      while(k>255){
        k-=256;
      }
      reverse[i]=(char)k;
    }
  }
  reverse[len1]='\0';
  //get the corresponding char}

  len=strlen(reverse);
  for(int i=0;i<len;i++){
    enc[i]=reverse[len-1-i];
  }
  enc[len]='\0';
  //get the reversion of encrypted string

  return (char *)enc;
}


char* decrypt(char* received,int key, int len) {
  int k,len1;
  char reverse[1000];
  char *dec=(char *)malloc(sizeof(char)*1000);

    for(int i=0;i<len;i++){
      reverse[i]=received[len-1-i];
    }
    reverse[len]='\0';
    //get the reversion of encrypted string

    len1=strlen(reverse);

    for(int i=0;i<len1;i++){
      k=(int)reverse[i]-key;

      if((k<=255)&&(k>=0)){
        dec[i]=(char)k;
      }
      else if (k<0){
        while(k<0){
          k+=256;
        }
        dec[i]=(char)k;
      }
      else if (k>255){
        while(k>255){
          k-=256;
        }
        dec[i]=(char)k;
      }
    }

    dec[len1]='\0';
    //get the corresponding char

    return (char *)dec;
  }



int main(int argc, char *argv[]) {

  if((argv[3]==NULL)||(argv[4]==NULL)||(argc<4)){
    printf("ERROR\n");
    return 0;
  }

  int i,num,len,len1;
  char received[1000],sent[1000],str[1010],temp[1000];
  char c;
  char *p;
  char *encryStr=(char *)malloc(sizeof(char)*1000);
  char *decRec=(char *)malloc(sizeof(char)*1000);

  int key=strtol(argv[4],&p,10);


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
    while((c=fgetc(f))!=EOF){
      received[num]=c;
      num++;
    }
    received[num]='\0';

    decRec=decrypt(received, key, num);

    if(decRec[0]!='['){
      printf("Nothing received yet.\n");
    }
    //get the message from incoming file and see if it is valid
    else{
      printf("Recieved: ");
      printf("%s",decRec);
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
    encryStr=encrypt(str,key);//encrypt the sent string
    fputs(encryStr,g);
	  strcpy(str, "");
    fclose(g);
    //write the string into outcome file.


    //checking and receiving
    while(1){
      //printf("looping...\n");
      f=fopen(argv[1],"r");
      num=0;
      while((c=fgetc(f))!=EOF){
        received[num]=c;
        num++;
      }
      received[num]='\0';
      //get received message
		  //printf("%s\n",temp);
      
      decRec=decrypt(received, key, num);

      if((strcmp(decRec,temp)!=0)&&(decRec[0]=='[')){//modify to better checking
        printf("Recieved: ");
        printf("%s",decRec );
        fclose(f);
        strcpy(temp,decRec);
        break;
      }
      //if new message received, print it and quit the loop.
      fclose(f);
    }
  }
}
