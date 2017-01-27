#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(int argc, char *argv[]){
    int i,j,k,x,z,count,count1,num,month,day,numline;
    int posi;
    int daysize;
    char c;
    char *p1,*p2;
    char date[300][200];
    char date1[1000];

    int argv2=strtol(argv[2],&p1,10);
    int argv3=strtol(argv[3],&p2,10);


	if((argv3>7)||(argv3<1)||(argv2<=0)){
		printf("ERROR\n");
		return 0;
	}

    daysize=21+7*argv2;
    FILE *f;
    f=fopen(argv[1],"r");

	if(f==NULL){
		printf("ERROR\n");
		return 0;
	}

    num=0;

    while((c=fgetc(f))!=EOF){
        if(c=='\n'){
        date1[num]=' ';
        }
        else{
        date1[num]=c;
        }
        num++;
 
    }
    i=0;j=0;k=0;
    while((c=date1[k])!=EOF){
        k++;
        if(c!=' '){
            date[i][j]=c;
            j++;
        }
        else{
            date[i][j]='\0';
            i++;j=0;
        }
    }
 
 
//get the date 2 dimensional char array, seperated by ' ' and '\n'
     
    	posi=argv3;
	if(posi==0){
		posi=7;
	}

    for(month=0;month<12;month++){
 
        for(j=0;j<daysize;j++){
        printf("*");
        }
        //print a * line
        printf("\n");
         
        printf("%s\n",date[month+7]);
        //print a month
         
        for(j=0;j<daysize;j++){
        printf("*");
        }
        printf("\n");
        //print a * line
 
             
            for(day=0;day<7;day++){
            printf("* ");
            if(strlen(date[day])>=argv2){
                for(i=0;i<argv2;i++){
                    printf("%c",date[day][i]);
                }
            }
            else{
                printf("%s",date[day]);
                for(i=0;i<argv2-strlen(date[day]);i++){
                    printf(" ");
                }
            }
            printf(" ");
            }
             
 
 
        printf("\n");
        //print a the days
        count=0;
        count1=0;
 	numline=5;
        for(j=0;j<numline;j++){
		if((posi==7)||(posi==0)){
			numline=6;
		}
		//printf("%d\n",posi);
	
            for(k=0;k<7;k++){
                printf("* ");
 
                //fill the number of characters of day
		
		count1++;
		//printf("%d\n",count1);
		

                if(count1>=posi){
                    count++;
			
                }
		
                if((count>0)&&(count<31)){
                    printf("%d",count);
			
                    if(count<10){
                        for(z=0;z<argv2;z++){
                        printf(" ");
                        }
                    }   
                    else{
                        for(z=0;z<(argv2-1);z++){
                        printf(" ");
                        }
                    }
                }
                else{
                    for(z=0;z<(argv2+1);z++){
                    printf(" ");}
                }
 


                if(k==6){
                    printf("\n");
                }
                
        }
 	
    }
	posi=(posi+2)%7;
	if(posi==0){
		posi=7;
	}

    }
	fclose(f);
    return 0;
}
