/******************* File: maxannealing.c ***************************/
#include "maxannea.h"
#include <stdio.h>
#include <stdlib.h>
extern Partitura X;
//fptr *FNS;
void MostraList();
//void *class;
int tempo;
void out(Partitura *score,FILE* f);
int main(int argc,char* argv[])
{ /*
  RememberA0();
  SetUpA4();
  FNS = f;
  setup ( &class, esqueleto_new, 0L,
	  (short) sizeof(struct esqueleto),
	  0L, A_DEFLONG, 0);
  addmess(MostraList,"list", A_GIMME, 0);11 finder_addclass ( "Lists","maxannealing");
  post("Maxannealing Installed");
  RestoreA4();
  */
  MostraList(argc,argv);
  return 0;
}
/*
void *esqueleto_new()
{
  Esqueleto *x;
  SetUpA4();
  x = (Esqueleto *)newobject(class);
  x->e_out = listout(x);
  RestoreA4();
  return (x);
}
*/
void MostraList(int argc, char* argv[])
{
  FILE *F,*fileout;
  char line[100];
  F=fopen(argv[1],"r");
  if(F == NULL)
    exit(-1);
  fileout=fopen(argv[2],"w");
  if(fileout == NULL)
    exit(-1);
  register int i,k;
  long n;
  int dur;
  fscanf(F, "%d",&tempo);
  for (i=0; i < 12; i++) {
    fscanf(F, "%d", &pesos_das_notas[i]);
  }
  
  fscanf(F,"%d",&P1);
  fscanf(F,"%d",&P2);
  fscanf(F,"%d",&P3);
  fscanf(F,"%d",&P4);
  fscanf(F,"%d",&P5);
  
  for (i=0; i < MaxSemiColcheias; i++) {
    //fprintf(stderr,"tensao %d\n",i);
    fscanf(F,"%d",&TENSAO_USUARIO[i]);
  }
  
  for (k=0,i=0; i < MaxSemiColcheias/4; i++) {
    fscanf(F,"%d",&dur);
    //fprintf(stderr,"dur11 %d\n",dur);
    DURACAO_ADEQUADA[MaxVozes-1][k++] = DURACAO_ADEQUADA[MaxVozes-1][k++] =
      DURACAO_ADEQUADA[MaxVozes-1][k++] = DURACAO_ADEQUADA[MaxVozes-1][k++] =
      (int) 8 - dur;
  }
   

  fclose(F);
  inicializa(&X);
  find_best_song();
  out(&X,fileout);
  fclose(fileout);
}
void out(Partitura *score,FILE* f)
{
  // my own invention reading the code,maybe totally wrong
  // write scheme code for Grace
  // global var *maxanneal-midiout* contains list of  total time, notes, durs,
  // and veloc
  float total_time[4] = {0.,0.,0.,0.};
  float duration = 0.; // 
  float dur =((60./tempo)/4.)/4.; //bpm to 1/16th
  int register k = 0, i, j;
  fprintf(f,"(define *maxanneal-midiout* '(");
  for(i=0;i<MaxVozes;i++) {
    fprintf(f,"(");
    for(j=0;j<MaxSemiColcheias;j++) {
      //fprintf(stderr,"%d %d start %d, pitch %d\n",i,j,(*score)[i][j].start, (*score)[i][j].pitch);
      duration = 0.;
      if((*score)[i][j].start==1) {
	if((*score)[i][j].pitch != REST) {
	  fprintf(f,"(");
	  fprintf(f,"%f ",total_time[i]);
	  duration = dur;
	  for(k=j+1;k<MaxSemiColcheias && (*score)[i][k].start == 0;k++)
	    duration += dur;
	  fprintf(f,"%d ",(*score)[i][j].pitch);
	  fprintf(f,"%f ",duration);
	  fprintf(f,"%d)\n",(*score)[i][j].velocity);
	  total_time[i] += duration;
	} else {
	  for(k=j;k<MaxSemiColcheias && (*score)[i][k].start == 0;k++)
	    duration += dur;
	  total_time[i] += duration;
	}
      }
    }
    fprintf(f,")\n");
  }
  fprintf(f,"))\n");
}
  

