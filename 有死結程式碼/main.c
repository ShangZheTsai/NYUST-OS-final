#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


int a=3;	//�i�Ϊ��H�ƶq 
int b=2;	//
int c=2;	//

int maxa1=3,maxb1=1,maxc1=2;	//thread1�̦h�n�Ϊ��ƶq 
int geta1=0,getb1=1,getc1=2;	//thread1�ثe�⤤�H�ƪ��ƶq 
int needa1,needb1,needc1;		//thread1�ٻݭn�h�֤H��
int reqa1,reqb1,reqc1;			//thread1�n�D�h�֤H�� 

int maxa2=7,maxb2=2,maxc2=2;	//thread2�A�ӤW 
int geta2=4,getb2=0,getc2=1;
int needa2,needb2,needc2;
int reqa2,reqb2,reqc2;


int maxa3=9,maxb3=3,maxc3=2;	//thread3�A�ӤW 
int geta3=3,getb3=2,getc3=2;
int needa3,needb3,needc3;
int reqa3,reqb3,reqc3;

int temp=0;

//thread1�Achild1 
void *child1() 
{
	srand((unsigned)time(NULL));  //�ɶ��ü� 
	needa1 = maxa1-geta1;         //�p��need 
	needb1 = maxb1-getb1;
	needc1 = maxc1-getc1;
  	

  do
  {
	  if(needa1 ==0) reqa1 = 0;				//�H�����ͭn�D�H�ƪ��ƶq 
	  else reqa1 = (rand() % needa1) +1;
	  if(needb1 ==0) reqb1 = 0;
	  else reqb1 = (rand() % needb1) +1;
	  if(needc1 ==0) reqc1 = 0;
	  else reqc1 = (rand() % needc1) +1;
	  printf("�����1�n�D:a=%d b=%d c=%d\n",reqa1,reqb1,reqc1);
	  printf("�����1�n�D�ɥi�ΤH�ƳѾl:a=%d b=%d c=%d\n",a,b,c);
	  while(temp==1);
	  temp=1;
	  if((reqa1 <=a) && (reqb1<=b) &&(reqc1<=c))	//�p�G�n�D�S�W�L�Ѿl�H�ƶq�A�N�i�H�q�L�h�ϥ� 
	  {
	  	printf("�����1�n�D�q�L\n");
	  	needa1 -= reqa1;	//�]���q�L�F�A���H�ơA�o��thread���ݨD�q�A�N��W�n�D���H�ƶq 
	  	needb1 -= reqb1;
	  	needc1 -= reqc1;
	  	geta1 += reqa1;		//�]���q�L�F�A���H�ơA�o��thread��W���H�ƶq�A�N�[�W�n�D���H�ƶq 
	  	getb1 += reqb1;
	  	getc1 += reqc1;
	  	a -= reqa1;			//�H�ƴ�����n�D�q 
	  	b -= reqb1;
	  	c -= reqc1;
	  	temp=0;
	  }
	  else
	  { 
	  	printf("�H�Ƥ���!�����1���n�D�L�k�q�L!\n");
	  	temp=0;
	  }
	  if(needa1==0 && needb1==0 && needc1==0)	//�p�G�ӤH�ƻݭn�q���O0�A��ܰ����F�A��H���٦^�h 
	  {
	  	a += geta1;
	  	b += getb1;
	  	c += getc1;
	  	printf("�����1�����A���٤H�ơA�i�ΤH�ƳѾl:a=%d b=%d c=%d\n",a,b,c);
	  }
	  sleep(1);
  }while(needa1!=0 || needb1!=0 || needc1!=0);	//�٦��ݭn�H�ơA�٨S�����A�~�� 

  pthread_exit(NULL);  //thread���� 
}

//thread2�Achild2�A��thread1�@�� 
void *child2() 
{
  srand((unsigned)time(NULL)); 
  needa2 = maxa2-geta2;
  needb2 = maxb2-getb2;
  needc2 = maxc2-getc2;	
	
  
  do
  {
  	  if(needa2 ==0) reqa2 = 0;
	  else reqa2 = rand() % needa2 +1;
	  if(needb2 ==0) reqb2 = 0;
  	  else reqb2 = rand() % needb2 +1;
  	  if(needc2 ==0) reqc2 = 0;
 	  else reqc2 = rand() % needc2 +1;
 	  printf("�����2�n�D:a=%d b=%d c=%d\n",reqa2,reqb2,reqc2);
 	  printf("�����2�n�D�ɥi�ΤH�ƳѾl:a=%d b=%d c=%d\n",a,b,c);
 	  while(temp==1);
 	  temp=1;
	  if((reqa2 <=a) && (reqb2<=b) &&(reqc2<=c))
	  {
	  	printf("�����2�n�D�q�L\n");
	  	needa2 -= reqa2; 
	  	needb2 -= reqb2;
	  	needc2 -= reqc2;
	  	geta2 += reqa2;
	  	getb2 += reqb2;
	  	getc2 += reqc2;
	  	a -= reqa2;
	  	b -= reqb2;
	  	c -= reqc2;
	  	temp=0;
	  }
	  else
	  { 
	  	printf("�H�Ƥ���!�����2���n�D�L�k�q�L!\n");
	  	temp=0;
	  }
	  if(needa2==0 && needb2==0 && needc2==0)
	  {
	  	a += geta2;
	  	b += getb2;
	  	c += getc2;
	  	printf("�����2�����A���٤H�ơA�H�ƳѾl:a=%d b=%d c=%d\n",a,b,c);
	  }
	  sleep(1);
  }while(needa2!=0 || needb2!=0 || needc2!=0);
  
  pthread_exit(NULL); 
}


//�D�{���Athread3 
int main() 
{

  srand((unsigned)time(NULL)); 
  
    pthread_t P1;	//�ŧi�@��thread id��P1 
    pthread_t P2;
    pthread_create(&P1, NULL, child1,"");  //(ID,NULL,thread�禡���ۤv�����W�l,�ǤJ��) 
    pthread_create(&P2, NULL, child2,""); 

	needa3 = maxa3-geta3;  
	needb3 = maxb3-getb3;
	needc3 = maxc3-getc3;


  do
  {	
  	  if(needa3 ==0) reqa3 = 0;
  	  else reqa3 = rand() % needa3 +1;
  	  if(needb3 ==0) reqb3 = 0;
 	  else reqb3 = rand() % needb3 +1;
 	  if(needc3 ==0) reqc3 = 0;
  	  else reqc3 = rand() % needc3 +1;
  	  printf("�����3�n�D:a=%d b=%d c=%d\n",reqa3,reqb3,reqc3);
  	  printf("�����3�n�D�ɤH�ƳѾl:a=%d b=%d c=%d\n",a,b,c);
  	  while(temp==1);
  	  temp=1;
	  if((reqa3 <=a) && (reqb3<=b) &&(reqc3<=c))
	  {
	  	printf("�����3�n�D�q�L\n");
	  	needa3 -= reqa3; 
	  	needb3 -= reqb3;
	  	needc3 -= reqc3;
	  	geta3 += reqa3;
	  	getb3 += reqb3;
	  	getc3 += reqc3;
	  	a -= reqa3;
	  	b -= reqb3;
	  	c -= reqc3;
	  	temp=0;
	  }
	  else
	  { 
	  	printf("�H�Ƥ���!�����3���n�D�L�k�q�L!\n");
	  	temp=0;
	  }
	  
	  if(needa3==0 && needb3==0 && needc3==0)
	  {
	  	a += geta3;
	  	b += getb3;
	  	c += getc3;
	  	printf("�����3�����A���٤H�ơA�H�ƳѾl:a=%d b=%d c=%d\n",a,b,c);
	  }
	  sleep(1);
  }while(needa3!=0 || needb3!=0 || needc3!=0);
	

  pthread_join(P1, NULL); //�pthread�٨S�����A�b�o���� 
  pthread_join(P2, NULL);
  printf("����\n");
  printf("�H���`�q:%d %d %d\n",a,b,c);
  return 0;
}
