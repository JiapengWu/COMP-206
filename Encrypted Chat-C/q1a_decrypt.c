#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {

  if(argc<2){
    printf("ERROR\n");
    return 0;
  }

  int num,k,len,len1;
  char enc[1000],reverse[1000],dec[1000];
  char c;
  char *p;
  int key=strtol(argv[1],&p,10);


  FILE *f;
  f=fopen(argv[2],"r");

  if(f==NULL){
  printf("ERROR\n");
  return 0;
}

  num=0;

    while((c=fgetc(f))!=EOF){
      enc[num]=c;
      num++;
    }
    enc[num]='\0';
    //get the string from input file

    len=strlen(enc);
    for(int i=0;i<len;i++){
      reverse[i]=enc[len-1-i];
    }
    reverse[len]='\0';
    //get the reversion of input string

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
    printf("%s\n",dec);

    fclose(f);
  return 0;
}
