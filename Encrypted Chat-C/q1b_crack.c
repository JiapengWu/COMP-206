#include <stdio.h>
#include <stdlib.h>
#include <string.h>

  int main(int argc, char const *argv[]) {
  int a,i,num,k,key,len,len1,count,count1;
  char enc[1000],reverse[1000],dec[1000];
  char c;


  FILE *f;
  f=fopen(argv[1],"r");

  if(f==NULL){
  printf("ERROR\n");
  return 0;
}
//check input
  num=0;

    while(((c=fgetc(f))!=EOF)&&(c!='\0')){
      enc[num]=c;
      num++;
    }
    enc[num]='\0';
    //get the string from input file

    len=strlen(enc);
    for(i=0;i<len;i++){
      reverse[i]=enc[len-1-i];
    }
    reverse[len]='\0';
    //get the reversion of input string
    len1=strlen(reverse);
    for(key=0;key<256;key++){

      count=0;count1=0;

      for(i=0;i<len1;i++){
        k=(int)reverse[i]-key;
        if((k<=255)&&(k>=0)){
          dec[i]=(char)k;
        }
        else if ((int)reverse[i]-key<0){
          while(k<0){
            k+=256;
          }
          dec[i]=(char)k;
        }
        //get the ith character of dec[]
        a=(int)dec[i];
        if(((a>=1)&&(a<=31))||((a>=33)&&(a<=64))||((a>=91)&&(a<=96))||((a>=123)&&(a<=255))){
          i=-1;
          
          break;
        }
        else if((a==65)||(a==97)){//if a is a a or A, count it
          count++;
          
        }
        else if((a==90)||(a==122)){//if a is a z or Z, count it
          count1++;
          
        }
      }

      if((i==len1)&&(count>=1)&&(count1>=1)){
		//printf("I am here %d\n",key);
        dec[len1]='\0';
        printf("%d\n", key);
        printf("%s\n", dec);
        fclose(f);
        return 0;
      }
      //printf("%s\n", dec);
    }
    //get the corresponding char
    printf("Nothing found\n");
    fclose(f);
    return 0;
}
