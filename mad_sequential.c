#include <stdio.h>
#include<stdlib.h>
#include <math.h>  
#include <time.h> 

float Mean(float numbers[], int count)
{
	float sum = 0;
	for (int i = 0; i < count; i++)
		sum = sum + numbers[i];
	return (sum / count);
}

float MADFunction(float numbers[], int count, float mean)
{
	float Sum = 0;
	for (int i = 0; i < count; i++) 
		Sum = Sum + fabsf(numbers[i] - mean);

	return (Sum / count);
}


float RangeFunction(float numbers[], int count)
{
	float small=numbers[0],big=numbers[0];
    for (int i = 0; i<count; i++) {
    
		if(numbers[i] > big) 	big = numbers[i];  
  		if(numbers[i] < small)  small = numbers[i];  		
	}

	return (big-small);
}

int main(int argc, char *argv[])
{
  clock_t start, end;
  start = clock();
  double pTime;
  
  
  float numbers[500000],small,big,range,meanNum;
  int count=0;
  FILE *file;

  if (file = fopen(argv[1], "r"))
  {
    while (fscanf(file, " %f", &numbers[count]) != EOF)
    {
      count++;
    }
    
    fclose(file);
    
	meanNum = Mean(numbers, count);
	printf("Range:  %.2f\n", RangeFunction(numbers, count) );
	printf("Mad:  %.2f\n", MADFunction(numbers, count,meanNum) );	

	end = clock();
     	pTime = ((double) fabsf(end - start) / CLOCKS_PER_SEC)*100;
	printf("Execution time for Range and MAD algorithm is  %.3f seconds.\n", pTime);
     
  }

  return 0;
}

