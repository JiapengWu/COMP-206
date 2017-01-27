#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	char *token, *token1, *token2;
	char dateTr[150];
	char eng[150]="Sunday Monday Tuesday Wednesday Thursday Friday Saturday January February March April May June July August September October November December";
	char eng2[20][10];
	char *result1, *result2, *datePtr, *day, *month;
	int num=0,j=0,i=0,count=0,count1=0,count2=0,posi1=0,posi2=0;
	char c;
	char date[50];
	char tmp[40];
	char tmp1[150];

	while(((c=getchar())!=EOF)){
		if(c=='\n'){
			date[i]='\0';
			break;
		}		
		else{
			date[i]=c;
			i++;
		}
	}
	//printf("%s\n",date);
	for (int j = 0; j < strlen(date); j++)
      	{
          tmp[j]=date[j+8];
      	}

	token1=strtok(date," ");
	if(token1==NULL){
		printf("ERROR\n");
		return 0;
	}

	token2=strtok(NULL," ");

	if(token2==NULL){
		printf("ERROR\n");
		return 0;
	}


	result1 = strstr(eng, token1);
	result2 = strstr(eng, token2);
	posi1 = result1 - eng;
	posi2 = result2 - eng;
	//printf("%d\n%d\n",posi1,posi2);
	//printf("%s\n%s\n",result1,result2);

	if((posi1>strlen(eng))||(posi1>strlen(eng))){
		printf("ERROR\n");
		return 0;
	}

	for(i=0;i<posi1;i++){
		if(eng[i]==' '){
			count1++;
		}
	}

	for(i=0;i<posi2;i++){
		if(eng[i]==' '){
			count2++;
		}
	}

	//printf("%d\n%d\n",count1,count2);

	FILE *f;
	f=fopen(argv[1],"r");

	if(f==NULL){
		printf("ERROR\n");
		return 0;
	}

	num=0;
	while((c=fgetc(f))!=EOF){
		if(c=='\n'){
		dateTr[num]=' ';
		}
		else{
		dateTr[num]=c;
		}
		num++;
	}
	
	//printf("%s\n",dateTr);
	
	
	for (int j = 0; j < 150; j++)
      	{
        	tmp1[j]=dateTr[j];
      	}
	//printf("%s\n",tmp1);
	
	day=strtok(dateTr," ");
	count=0;
	while(count!=count1){
		day=strtok(NULL, " ");
		count++;
	}
	//printf("%s\n",day);

	month=strtok(tmp1," ");
	count=0;
	while(count!=count2){
		month=strtok(NULL, " ");
		count++;
	}
	//printf("%s\n",month);
	
	printf("%s %s %s\n",day,month,tmp);
	fclose(f);
        return 0;
}

