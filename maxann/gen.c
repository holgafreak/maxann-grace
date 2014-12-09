// just a test generator for maxanneal
#include <stdio.h>
#include <stdlib.h>

int main() {
  int i,j,k;
  // write tempo
  printf("120\n");
  // write 12 weights for notes (C, C#, .. B/H)
  for(i=0;i<12;i++)
    printf("%d\n",i+1);
  
 // write 5 parameters for  music qualification
  printf("15\n"); //strength
  printf("0\n"); // crossings
  printf("4\n"); // intervals (minor thirds preferred)
  printf("10\n"); // duration
  printf("0\n"); // weights
  //write 256 values for strenght/intensity (tensao_usuario) over
  //the score (made up from 256 1/16th) 
  for(i=0;i<256;i++)
    printf("%d\n",i%5+1);
  //write 64 values for note durations over the score
  for(i=0;i<64;i++) {
    if(i<64/2)
      printf("%d\n",(int)random()% 7+1);
    else
      printf("%d\n",i%7+1);
  }
  return 0;
}
