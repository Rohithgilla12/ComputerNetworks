#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

bool checkRepe(unsigned long int arr[],int n,int num){
  for(int i = 0; i < n; i++)
  {
    if(arr[i] == num){
      return false;
    }
  }
  return true;
}

int main()
{
  srand(time(NULL));
  int seed=1000;
  int step = 10;
  int n=10;
  printf("Enter the number of random numbers you want\n");
  scanf("%d",&n);
  unsigned long int ranNums[n];
  int temp;
  for(int i = 0; i < n; i++)
  {
    ranNums[0] =0;
  }
  int eachLeft = (seed-step)/n;
  for (int i=0;i<n;i++){
    temp=(rand()%step)+seed;
    if(checkRepe(ranNums,n,temp)){
        seed=seed-eachLeft;
        step +=eachLeft+step;
        ranNums[i] = temp;
    }
    else
    {
      i--;
    }
    
  }

  for(int i=0;i<n-1;i++){
    ranNums[i]=ranNums[i] << rand()%15 ^ ranNums[i+1] >> rand()%8;
    printf("%lu\n",ranNums[i]);
  }
  return 0;
}
