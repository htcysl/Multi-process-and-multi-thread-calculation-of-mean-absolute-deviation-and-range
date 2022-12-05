#include <stdio.h>
#include <stdlib.h> 
#include <math.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#include <pthread.h>

#define BUFFER_SIZE 	25
#define NUMBER_SIZE 	500000
#define READ_END	0
#define WRITE_END	1

#define MAX_THREAD 10

#define SMALL	0
#define BIG	1
#define MEAN	2
#define MAD	3


struct args {
	float* numbers;
	int count;
};



float write_global[BUFFER_SIZE];
float read_global[BUFFER_SIZE]; 

float parentArray[4]; 
float childArray[4]; 

int THREAD_NUM = 0;

float MeanArray[MAX_THREAD][4] = {0};
int part = 0;

int flag = 0;


void Mean(float numbers[], int count,int s, int n, int numPart, int thread_part)
{

	float sum = 0;
	for (int i = s; i < n; i++)
		sum = sum + numbers[i];
	
	MeanArray[thread_part][MEAN] = (sum / numPart);
}


void MADFunction(float numbers[], int count, float mean, int s, int c, int thread_part)
{
	float Sum = 0;
	for (int i = s; i < c; i++) 
		Sum = Sum + fabsf(numbers[i] - mean);

	MeanArray[0][MAD] += (Sum / count);
}

void RangeFunction(float numbers[], int count,int s, int n,int thread_part)
{
	float small=numbers[s],big=numbers[s];
	
	static float Range[2];
	
	for (int i = s; i<n; i++) {
	    
		if(numbers[i] > big) 	big = numbers[i];  
	  	if(numbers[i] < small)  small = numbers[i];  		
	}
	
	Range[SMALL] = small;
	Range[BIG] = big;
	
	MeanArray[thread_part][SMALL] = small;
	MeanArray[thread_part][BIG] = big;
}

void* threadMain(void *input)
{

	int thread_part = part++;
	int numPart =  (((struct args*)input)->count)/THREAD_NUM;
	
	int startIndex = thread_part * numPart;
	int endIndex = (thread_part+1) * numPart;
	
	//float numbers_[] = ((struct args*)input)->count);
	
	Mean(((struct args*)input)->numbers,((struct args*)input)->count,startIndex,endIndex,numPart,thread_part);
	
	RangeFunction(((struct args*)input)->numbers,((struct args*)input)->count,startIndex,endIndex,thread_part);
	
	flag++;
	
	while(flag < THREAD_NUM);
	
	float avarageMean;
	
	for(int i=0;i<THREAD_NUM;i++){
		avarageMean += MeanArray[i][MEAN];
	}
	
	//printf("Flag-MEAN: %f \n",(avarageMean/THREAD_NUM) );
	
	MADFunction(((struct args*)input)->numbers,((struct args*)input)->count,(avarageMean/THREAD_NUM),startIndex,endIndex,thread_part);
	
	//printf("MAD: %f \n",MeanArray[thread_part][MAD] );
	
	
}


int main(int argc, char *argv[])
{
  clock_t start, end;
  start = clock();
  double pTime;

	
  float numbers[NUMBER_SIZE];
  int count=0;
  FILE *file;
  
  THREAD_NUM = atoi(argv[2]);
  
  struct args *obj = (struct args *)malloc(sizeof(struct args));
  
  pthread_t threads[MAX_THREAD];

  
  if (file = fopen(argv[1], "r"))
  {
    while (fscanf(file, " %f", &numbers[count]) != EOF)
    {
      count++;
    }
    
    fclose(file);
  }
  
  obj->numbers = numbers;
  obj->count = count;

  
  
  for(int i=0; i<THREAD_NUM; i++)
  {
  	pthread_create(&threads[i],NULL,threadMain,(void *)obj);
  
  }
  
  for(int i=0; i<THREAD_NUM; i++)
  {
  	pthread_join(threads[i],NULL);
  
  }
  
  /*
  
  for(int i=0; i<THREAD_NUM; i++)
  {
  	printf("Thread: %d Mean: %f  MAD: %f  Range_Small: %f  Range_Big: %f \n",i,MeanArray[i][MEAN],MeanArray[i][MAD],MeanArray[i][SMALL],MeanArray[i][BIG]);
  
  }*/
  
  
  	float newRangeArray[THREAD_NUM*2];
	
	for(int i = 0; i<THREAD_NUM; i++)
	{	

		newRangeArray[i] = MeanArray[i][SMALL];
		newRangeArray[i+THREAD_NUM] = MeanArray[i][BIG];
	}
	
	/*
	for(int i = 0; i<(THREAD_NUM*2); i++)
	{	
		printf("i: %d Num: %f  \n",i,newRangeArray[i]);
	}*/
	
	RangeFunction(newRangeArray, count,0,THREAD_NUM*2,(THREAD_NUM+1));
	
	printf("Program is reading %s \n",argv[1]);
	
	printf("%d threads are created \n",atoi(argv[2]) );
  
        printf("Range: %.2f\n", (MeanArray[THREAD_NUM+1][BIG]-MeanArray[THREAD_NUM+1][SMALL]) );
  
  	printf("MAD: %.2f\n", MeanArray[0][MAD] );

 
 	end = clock();
     	pTime = ((double) fabsf(end - start) / CLOCKS_PER_SEC)*100;
	printf("Execution time for Range and MAD algorithm is  %.3f seconds.\n", pTime);
  

  pthread_exit(0);

  return 0;
}


