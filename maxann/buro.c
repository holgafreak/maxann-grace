/*********************** File: buro.c ***************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maxannea.h"
int DURACAO_ADEQUADA[MaxVozes][MaxSemiColcheias];
int pesos_das_notas[13];
int melhor_nota=0;
void inicializa (Partitura *X)
{
  int i,voz,semi;
  for (i=0;i<12;i++)
    if (pesos_das_notas[i] > pesos_das_notas[melhor_nota]) melhor_nota = i;
  for (voz=0; voz<MaxVozes; voz++)
    for (semi=0; semi<MaxSemiColcheias; semi++) {
      if (semi % 16==0) {
	(*X)[voz][semi].pitch = melhor_nota+(voz+3)*12;
	(*X)[voz][semi].velocity = 100;
	(*X)[voz][semi].start = 1;
      }
      else {
	(*X)[voz][semi].pitch = melhor_nota+(voz+3)*12;
	(*X)[voz][semi].velocity = 100;
	(*X)[voz][semi].start = 0;
      }
    }
  for (semi=0; semi<MaxSemiColcheias; semi++) {
    DURACAO_ADEQUADA[2][semi] = DURACAO_ADEQUADA[3][semi]<<1;
    DURACAO_ADEQUADA[1][semi] = DURACAO_ADEQUADA[2][semi]<<1;
    DURACAO_ADEQUADA[0][semi] = DURACAO_ADEQUADA[1][semi]<<1;
  }
}

void copia(Partitura *X, Partitura *Y)
{
  memcpy(X, Y, sizeof(Partitura));
}
void vizinho (Partitura *Y, Partitura *X)
/* Returns in Y, a neighbor of X */
{
  int pitch, duracao, voz, semi, oitava, k, l, i, temp = 1;
  voz = (int) myrand()&3;
  semi = (int) myrand()&255;
  pitch = (int) myrand() % 12;
  if(pitch == 0)
    pitch = REST;
  temp = (DURACAO_ADEQUADA[voz][semi]<<1)+1;
  duracao = (int) myrand() % temp;
  //fprintf(stderr,"dur %d temp %d pitch %d voz %d\n",duracao,temp,pitch,voz);
  //if(duracao == 0)
  //		duracao++;

  copia(Y, X);
  if (pitch != REST) {
    if (semi == 0) i = (*Y)[voz][semi].pitch;
    else i = (*Y)[voz][semi-1].pitch; /* i is the previous note */
    if (i == REST) i = melhor_nota+(voz+3)*12;
    oitava = ( int) i/12 -1; /* We choose a pitch near the pitch of i */
    pitch += oitava*12; /* preserving the selected pitch class. */
    while (abs(i-pitch) > 6)
      if ( i > pitch) pitch += 12;
      else pitch-= 12;
    while(pitch < 36) pitch +=12;
    while(pitch > 96) pitch -=12;
    //fprintf(stderr,"voz %d pitch %d\n",voz,pitch);
  }
  (*Y)[voz][semi].pitch = pitch;
  (*Y)[voz][semi].velocity = 100;
  (*Y)[voz][semi].start = 1;

  for(k=1; k<duracao && semi+k<MaxSemiColcheias; k++) {
    (*Y)[voz][semi+k].pitch = pitch;
    (*Y)[voz][semi+k].velocity = 100;
    (*Y)[voz][semi+k].start=0;
  }

  
  if (semi+duracao<MaxSemiColcheias && !(*Y)[voz][semi+duracao].start)
    (*Y)[voz][semi+duracao].start = 1;
 
}
