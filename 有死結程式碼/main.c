#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


int a=3;	//可用的人數量 
int b=2;	//
int c=2;	//

int maxa1=3,maxb1=1,maxc1=2;	//thread1最多要用的數量 
int geta1=0,getb1=1,getc1=2;	//thread1目前手中人數的數量 
int needa1,needb1,needc1;		//thread1還需要多少人數
int reqa1,reqb1,reqc1;			//thread1要求多少人數 

int maxa2=7,maxb2=2,maxc2=2;	//thread2，承上 
int geta2=4,getb2=0,getc2=1;
int needa2,needb2,needc2;
int reqa2,reqb2,reqc2;


int maxa3=9,maxb3=3,maxc3=2;	//thread3，承上 
int geta3=3,getb3=2,getc3=2;
int needa3,needb3,needc3;
int reqa3,reqb3,reqc3;

int temp=0;

//thread1，child1 
void *child1() 
{
	srand((unsigned)time(NULL));  //時間亂數 
	needa1 = maxa1-geta1;         //計算need 
	needb1 = maxb1-getb1;
	needc1 = maxc1-getc1;
  	

  do
  {
	  if(needa1 ==0) reqa1 = 0;				//隨機產生要求人數的數量 
	  else reqa1 = (rand() % needa1) +1;
	  if(needb1 ==0) reqb1 = 0;
	  else reqb1 = (rand() % needb1) +1;
	  if(needc1 ==0) reqc1 = 0;
	  else reqc1 = (rand() % needc1) +1;
	  printf("實驗室1要求:a=%d b=%d c=%d\n",reqa1,reqb1,reqc1);
	  printf("實驗室1要求時可用人數剩餘:a=%d b=%d c=%d\n",a,b,c);
	  while(temp==1);
	  temp=1;
	  if((reqa1 <=a) && (reqb1<=b) &&(reqc1<=c))	//如果要求沒超過剩餘人數量，就可以通過去使用 
	  {
	  	printf("實驗室1要求通過\n");
	  	needa1 -= reqa1;	//因為通過了，給人數，這個thread的需求量，就減上要求的人數量 
	  	needb1 -= reqb1;
	  	needc1 -= reqc1;
	  	geta1 += reqa1;		//因為通過了，給人數，這個thread手上的人數量，就加上要求的人數量 
	  	getb1 += reqb1;
	  	getc1 += reqc1;
	  	a -= reqa1;			//人數減掉給的要求量 
	  	b -= reqb1;
	  	c -= reqc1;
	  	temp=0;
	  }
	  else
	  { 
	  	printf("人數不夠!實驗室1的要求無法通過!\n");
	  	temp=0;
	  }
	  if(needa1==0 && needb1==0 && needc1==0)	//如果個人數需要量都是0，表示做完了，把人數還回去 
	  {
	  	a += geta1;
	  	b += getb1;
	  	c += getc1;
	  	printf("實驗室1完成，返還人數，可用人數剩餘:a=%d b=%d c=%d\n",a,b,c);
	  }
	  sleep(1);
  }while(needa1!=0 || needb1!=0 || needc1!=0);	//還有需要人數，還沒做完，繼續 

  pthread_exit(NULL);  //thread結束 
}

//thread2，child2，跟thread1一樣 
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
 	  printf("實驗室2要求:a=%d b=%d c=%d\n",reqa2,reqb2,reqc2);
 	  printf("實驗室2要求時可用人數剩餘:a=%d b=%d c=%d\n",a,b,c);
 	  while(temp==1);
 	  temp=1;
	  if((reqa2 <=a) && (reqb2<=b) &&(reqc2<=c))
	  {
	  	printf("實驗室2要求通過\n");
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
	  	printf("人數不夠!實驗室2的要求無法通過!\n");
	  	temp=0;
	  }
	  if(needa2==0 && needb2==0 && needc2==0)
	  {
	  	a += geta2;
	  	b += getb2;
	  	c += getc2;
	  	printf("實驗室2完成，返還人數，人數剩餘:a=%d b=%d c=%d\n",a,b,c);
	  }
	  sleep(1);
  }while(needa2!=0 || needb2!=0 || needc2!=0);
  
  pthread_exit(NULL); 
}


//主程式，thread3 
int main() 
{

  srand((unsigned)time(NULL)); 
  
    pthread_t P1;	//宣告一個thread id為P1 
    pthread_t P2;
    pthread_create(&P1, NULL, child1,"");  //(ID,NULL,thread函式中自己取的名子,傳入值) 
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
  	  printf("實驗室3要求:a=%d b=%d c=%d\n",reqa3,reqb3,reqc3);
  	  printf("實驗室3要求時人數剩餘:a=%d b=%d c=%d\n",a,b,c);
  	  while(temp==1);
  	  temp=1;
	  if((reqa3 <=a) && (reqb3<=b) &&(reqc3<=c))
	  {
	  	printf("實驗室3要求通過\n");
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
	  	printf("人數不夠!實驗室3的要求無法通過!\n");
	  	temp=0;
	  }
	  
	  if(needa3==0 && needb3==0 && needc3==0)
	  {
	  	a += geta3;
	  	b += getb3;
	  	c += getc3;
	  	printf("實驗室3完成，返還人數，人數剩餘:a=%d b=%d c=%d\n",a,b,c);
	  }
	  sleep(1);
  }while(needa3!=0 || needb3!=0 || needc3!=0);
	

  pthread_join(P1, NULL); //如thread還沒結束，在這等待 
  pthread_join(P2, NULL);
  printf("結束\n");
  printf("人數總量:%d %d %d\n",a,b,c);
  return 0;
}
