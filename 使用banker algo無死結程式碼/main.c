#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

int a=3;  
int b=2;
int c=2;
int temp=0;		//用來互斥thread使用band algorithm時，不會race condition，會擋住其他thread 
int finish1=0,finish2=0,finish3=0;		//如=1，表示thread做完了 

int maxa1=3,maxb1=1,maxc1=2;
int geta1=0,getb1=1,getc1=2;
int needa1=3,needb1=0,needc1=0;
int reqa1,reqb1,reqc1;

int maxa2=7,maxb2=2,maxc2=2;
int geta2=4,getb2=0,getc2=1;
int needa2=3,needb2=2,needc2=1;
int reqa2,reqb2,reqc2;

int maxa3=9,maxb3=3,maxc3=2;
int geta3=3,getb3=2,getc3=2;
int needa3=6,needb3=1,needc3=0;
int reqa3,reqb3,reqc3;

/*bank algorithm
按照3個thread，六種可能一一執行測試 
1>2>3
1>3>2...
*/ 
int bankeralgorithm(int flag1,int flag2,int flag3,int get1,int get2,int get3,int get4,int get5,int get6,int get7,int get8,int get9,int need1,int need2,int need3,int need4,int need5,int need6,int need7,int need8,int need9)
{
	temp=1;
	int testa=a,testb=b,testc=c;
	int conti=0;	//例如有一種順序確定了可給人數，conti為1，就不會繼續判斷其他選擇 
	
		if(flag1==1)	//flag1為thread1進入要求人數 
		{
			if(reqa1>testa || reqb1>testb || reqc1>testc)
			{
				printf("人數不夠!"); 
				return 0;
			}
			else 
			{
				if(need4==0 &&need5==0 &&need6==0) 
				{	
					get4=0;
					get5=0;
					get6=0;
				}	
				if(need7==0 &&need8==0 &&need9==0) 
				{
					get7=0;
					get8=0;
					get9=0;
				}
				if(need1==0 &&need2==0 &&need3==0)
				{
					get1=0;
					get2=0;
					get3=0;
				}
				else
				{
					get1 += reqa1;
					get2 += reqb1;
					get3 += reqc1;
				}
				
				need1 -= reqa1;
				need2 -= reqb1;
				need3 -= reqc1;
				
				testa -= reqa1;
				testb -= reqb1;
				testc -= reqc1;
			}
		}
		else if(flag2==1)
		{
			if(reqa2>testa || reqb2>testb || reqc2>testc) 
			{
				printf("人數不夠!"); 
				return 0;
			}
			else 
			{	
				if(need1==0 &&need2==0 &&need3==0) 
				{
					get1=0;
					get2=0;
					get3=0;
				}
				if(need7==0 &&need8==0 &&need9==0) 
				{
					get7=0;
					get8=0;
					get9=0;
				}
				if(need4==0 &&need5==0 &&need6==0) 
				{
					get4=0;
					get5=0;
					get6=0;
				}
				else
				{
					get4 += reqa2;
					get5 += reqb2;
					get6 += reqc2;
				} 
				
				need4 -= reqa2;
				need5 -= reqb2;
				need6 -= reqc2;
				
				testa -= reqa2;
				testb -= reqb2;
				testc -= reqc2;
			}
		}
		else if(flag3==1)
		{
			if(reqa3>testa || reqb3>testb || reqc3>testc)
			{
				printf("人數不夠!"); 
				return 0;
			}
			else 
			{	
				if(need1==0 &&need2==0 &&need3==0) 
				{
					get1=0;
					get2=0;
					get3=0;
				}	
				if(need4==0 &&need5==0 &&need6==0) 
				{
					get4=0;
					get5=0;
					get6=0;
				}		
			
				if(need7==0 &&need8==0 &&need9==0) 
				{
					get7=0;
					get8=0;
					get9=0;
				}	
				else
				{
					get7 += reqa3;
					get8 += reqb3;
					get9 += reqc3;
				}
				need7 -= reqa3;
				need8 -= reqb3;
				need9 -= reqc3;
				
				testa -= reqa3;
				testb -= reqb3;
				testc -= reqc3;
			}
		}
		
		
		
//開始判斷 
		//判斷從thread1開始所有可能，1>2>3,1>3>2 
		
		//1
		if(need1<=testa && need1<=testb && need1<=testc)
		{	
				testa += get1;
				testb += get2;
				testc += get3; 
			//2>3
			if(need4<=testa && need5<=testb && need6<=testc)
			{		
					testa += get4;
					testb += get5;
					testc += get6;
					
				if(need7<=testa && need8<=testb && need9<=testc)
				{		
						testa += get7;
						testb += get8;
						testc += get9;
						conti = 1;
				}
				else
				{	
					testa -= get4;
					testb -= get5;
					testc -= get6;
				} 
			}
			
			//3>2
			if(need7<=testa && need8<=testb && need9<=testc && conti==0)
			{
					testa += geta3;
					testb += getb3;
					testc += getc3;

				if(need4<=testa && need5<=testb && need6<=testc)
				{
						testa += get4;
						testb += get5;
						testc += get6;
						conti = 1;
				}
				else
				{
					testa -= geta3;
					testb -= getb3;
					testc -= getc3;
				}
			}
			if(conti==0)
			{
				testa -= get1;
				testb -= get2;
				testc -= get3; 
			}
			
		}
		
		//如果thread1沒有順序，第2個thread開始判斷，2>1>3,2>3>1 
		//2
		if(need4<=testa && need5<=testb && need6<=testc && conti==0)
		{	

				testa += get4;
				testb += get5;
				testc += get6; 
			//1>3
			if(need1<=testa && need2<=testb && need3<=testc)
			{
				
					testa += get1;
					testb += get2;
					testc += get3;

					if(need7<=testa && need8<=testb && need9<=testc)
					{
							testa += get7;
							testb += get8;
							testc += get9;
							conti = 1;
					}
					else
					{
						testa -= get1;
						testb -= get2;
						testc -= get3;
					} 
			}	
			
			//3>1
			if(need7<=testa && need8<=testb && need9<=testc && conti==0)
			{
					testa += get7;
					testb += get8;
					testc += get9;
				if(need1<=testa && need2<=testb && need3<=testc)
				{
						testa += get1;
						testb += get2;
						testc += get3;
						conti = 1;
				}
				else
				{
					testa -= get7;
					testb -= get8;
					testc -= get9;
				}
			}
			if(conti==0)
			{
				testa -= get4;
				testb -= get5;
				testc -= get6; 
			}		
		}
		
		
		

		//如果thread1與thread2沒有順序，第3個thread開始判斷，3>1>2,3>2>1
		//3
		if(need7<=testa && need8<=testb && need9<=testc && conti==0)
		{
				testa += get7;
				testb += get8;
				testc += get9; 
			
			//1>2
			if(need1<=testa && need2<=testb && need3<=testc)
			{
					testa += get1;
					testb += get2;
					testc += get3;

					if(need4<=testa && need5<=testb && need6<=testc)
					{
							testa += get4;
							testb += get5;
							testc += get6;
							conti = 1;
					}
					else
					{
						testa -= get1;
						testb -= get2;
						testc -= get3;
					}
			}	
			
			//2>1
			if(need4<=testa && need5<=testb && need6<=testc && conti==0)
			{	
					testa += get4;
					testb += get5;
					testc += get6;

				if(need1<=testa && need2<=testb && need3<=testc)
				{
						testa += get1;
						testb += get2;
						testc += get3;
						conti = 1;
				}
				else
				{
					testa -= get4;
					testb -= get5;
					testc -= get6;
				}
			}
			if(conti==0)
			{
				testa -= get7;
				testb -= get8;
				testc -= get9; 
			}		
		}
				
		if(testa==10 && testb==5 && testc==7) //如果最後回去的人數數等於總人數數，表示有順序假設成立
		{
			return 1;
		}
		else
		{ 	
			printf("會產生死結!");
			return 0;
		} 
}	
	






//therad1,child1
void *child1() 
{
	srand((unsigned)time(NULL)); 
	needa1 = maxa1-geta1;
	needb1 = maxb1-getb1;
	needc1 = maxc1-getc1;
  	

  do
  {
	  if(needa1 ==0) reqa1 = 0;
	  else reqa1 = (rand() % needa1) +1;
	  if(needb1 ==0) reqb1 = 0;
	  else reqb1 = (rand() % needb1) +1;
	  if(needc1 ==0) reqc1 = 0;
	  else reqc1 = (rand() % needc1) +1;
	  printf("child1要求:reqa1=%d reqb1=%d reqc1=%d\n",reqa1,reqb1,reqc1);
	  printf("child1要求時人數剩餘:a=%d b=%d c=%d\n",a,b,c);
	  while(temp==1);
	  temp=1;
	  if(bankeralgorithm(1,0,0,geta1,getb1,getc1,geta2,getb2,getc2,geta3,getb3,getc3,needa1,needb1,needc1,needa2,needb2,needc2,needa3,needb3,needc3)==1)		
	  {
	  	printf("child1要求通過\n\n");
	  	needa1 -= reqa1; 
	  	needb1 -= reqb1;
	  	needc1 -= reqc1;
	  	geta1 += reqa1;
	  	getb1 += reqb1;
	  	getc1 += reqc1;
	  	a -= reqa1;
	  	b -= reqb1;
	  	c -= reqc1;
	  	temp=0;
	  }
	  else
	  { 
	  	printf("child1的要求無法通過!\n\n");
		temp = 0;	
	  } 
	  
	  if(needa1==0 && needb1==0 && needc1==0)
	  {
	  	a += geta1;
	  	b += getb1;
	  	c += getc1;
	  	printf("child1完成，返還人數，人數剩餘:a=%d b=%d c=%d\n\n",a,b,c);
	  	finish1 =1;
	  }
	  sleep(1);
  }while(needa1!=0 || needb1!=0 || needc1!=0);

  pthread_exit(NULL); 
}

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
 	  printf("child2要求:reqa2=%d reqb2=%d reqc2=%d\n",reqa2,reqb2,reqc2);
 	  printf("child2要求時人數剩餘:a=%d b=%d c=%d\n",a,b,c);
 	  while(temp==1);
	  temp=1;
	  if(bankeralgorithm(0,1,0,geta1,getb1,getc1,geta2,getb2,getc2,geta3,getb3,getc3,needa1,needb1,needc1,needa2,needb2,needc2,needa3,needb3,needc3)==1)
	  {
	  	printf("child2要求通過\n\n");
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
		printf("child2的要求無法通過!\n\n"); 	
	  	temp = 0;
	  }
	  if(needa2==0 && needb2==0 && needc2==0)
	  {
	  	a += geta2;
	  	b += getb2;
	  	c += getc2;
	  	printf("child2完成，返還人數，人數剩餘:a=%d b=%d c=%d\n\n",a,b,c);
	  	finish2=1;
	  }
	  sleep(1);
  }while(needa2!=0 || needb2!=0 || needc2!=0);
  
  pthread_exit(NULL); 
}



int main() 
{

  srand((unsigned)time(NULL)); 
  
    pthread_t P1;  
    pthread_t P2;
    pthread_create(&P1, NULL, child1,""); 
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
  	  printf("main要求:reqa3=%d reqb3=%d reqc3=%d\n",reqa3,reqb3,reqc3);
  	  printf("main要求時人數剩餘:a=%d b=%d c=%d\n",a,b,c);
  	  while(temp==1);
	  temp=1;
	  if(bankeralgorithm(0,0,1,geta1,getb1,getc1,geta2,getb2,getc2,geta3,getb3,getc3,needa1,needb1,needc1,needa2,needb2,needc2,needa3,needb3,needc3)==1)
	  {
	  	printf("main要求通過\n\n");
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
		printf("main的要求無法通過!\n\n"); 	
	  	temp = 0;
	  }
	  
	  if(needa3==0 && needb3==0 && needc3==0)
	  {
	  	a += geta3;
	  	b += getb3;
	  	c += getc3;
	  	printf("main完成，返還人數，人數剩餘:a=%d b=%d c=%d\n\n",a,b,c);
	  	finish3=1;
	  }
	  sleep(1);
  }while(needa3!=0 || needb3!=0 || needc3!=0);
	

  pthread_join(P1, NULL); 
  pthread_join(P2, NULL);
  printf("結束\n");
  printf("人數總量:%d %d %d\n",a,b,c);
  return 0;
}
