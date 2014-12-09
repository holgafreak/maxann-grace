/*********************** File: quali.c ***************************/
#include <stdlib.h>
#include <stdio.h>
#include "maxannea.h"
int TENSAO_USUARIO[MaxSemiColcheias];
int tensao( Nota *n1, Nota *n2, Nota *n3, Nota *n4)
{
  static int tensao_intervalar[12] = {0, 10, 7, 6, 5, 2, 9, 1, 4, 3, 8, 11};
  int t=0;
  if(n1->pitch != REST )
    {
      if(n2->pitch != REST) t+=tensao_intervalar[abs((*n1).pitch - (*n2).pitch) % 12];
      if(n3->pitch != REST) t+=tensao_intervalar[abs((*n1).pitch - (*n3).pitch) % 12];
      if(n4->pitch != REST) t+=tensao_intervalar[abs((*n1).pitch - (*n4).pitch) % 12];
    } 
    
  if(n2->pitch != REST )
    { if(n3->pitch != REST) t+=tensao_intervalar[abs((*n2).pitch - (*n3).pitch) % 12];
      if(n4->pitch != REST) t+=tensao_intervalar[abs((*n2).pitch - (*n4).pitch) % 12];
    }
  if(n3->pitch != REST && n4->pitch != REST)
    t+=tensao_intervalar[abs((*n3).pitch - (*n4).pitch) % 12];
  if(n1->pitch == REST || n2->pitch == REST || n3->pitch == REST || n4->pitch == REST)
    t+=2;
  return (t);
}
int cruzamento( Nota *n1, Nota *n2, Nota *n3, Nota *n4)
{
  int j=0;
  if(n1->pitch != REST )
    {
      if((*n1).pitch > (*n2).pitch && n2->pitch != REST) j+=n1->pitch - n2->pitch;
      if((*n1).pitch > (*n3).pitch && n3->pitch != REST) j+=n1->pitch - n3->pitch;
      if((*n1).pitch > (*n4).pitch && n4->pitch != REST) j+=n1->pitch - n4->pitch;
    } else
    j+=1;
  if(n2->pitch != REST )
    {
      if((*n2).pitch > (*n3).pitch && n3->pitch != REST) j+=n2->pitch - n3->pitch;
      if((*n2).pitch > (*n4).pitch && n4->pitch != REST) j+=n2->pitch - n4->pitch;
    }
  if(n3->pitch != REST && n4->pitch != REST && n3->pitch > n4->pitch)
    j+=n3->pitch - n4->pitch ;
  return (j);
}
int salto(int n1, int n2)
{
  if(n1 == REST || n2 == REST) return(0);
  return(abs(n1-n2));
}
int qualidade(Partitura *X)
{
  long tensao_da_musica = 0, duracao = 0,
    duracao_voz = 0, cruzamentos = 0,
    saltos = 0, soma_dos_pesos = 0;
  int nota_atual = 0, nota_seguinte = 0,
    semi, dur, voz, numero_de_notas = 0;
  /* Harmonic Analysis (vertical) */
  for (semi=0; semi < MaxSemiColcheias; semi++)
    {
      tensao_da_musica += abs(tensao(&(*X)[0][semi],&(*X)[1][semi],
				     &(*X)[2][semi],&(*X)[3][semi]));
      //fprintf(stderr,"tens %ld\n",tensao_da_musica);
      tensao_da_musica =abs(tensao_da_musica-TENSAO_USUARIO[semi]);
      /* This only works if the song has 4 voices. We must generalize
	 this in the future */
      cruzamentos += cruzamento(&(*X)[0][semi],&(*X)[1][semi],
				&(*X)[2][semi],&(*X)[3][semi]);
    }
  /* Horizontal Analysis */
  for (voz=0; voz < MaxVozes; voz++)
    {
      semi = 0;
      duracao_voz = 0;
      while(semi<MaxSemiColcheias)
	{
	  nota_atual = (*X)[voz][semi].pitch;
	  numero_de_notas++;
	  dur = 1;
	  semi++;
	  while ((*X)[voz][semi].start == 0 && semi<MaxSemiColcheias)
	    { dur++;
	      semi++;
	    }
	  duracao_voz += abs(dur-DURACAO_ADEQUADA[voz][semi-1]);
	  soma_dos_pesos += dur*pesos_das_notas[(nota_atual % 12)+1];
	  if(semi<MaxSemiColcheias)
	    {
	      nota_seguinte = (*X)[voz][semi].pitch;
	      saltos += salto(nota_atual, nota_seguinte);
	    }
	}
      duracao += duracao_voz*(voz+1);
    }
  soma_dos_pesos *=10;
  soma_dos_pesos /= 1024; /* between 0 and 100 */
  tensao_da_musica *=100;
  tensao_da_musica /=(MaxSemiColcheias*MaxTensao); /* between 0 and 100 */
  cruzamentos *=100;
  cruzamentos /=(MaxSemiColcheias); /* between 0 and 100 */
  saltos *=10;
  saltos /= (numero_de_notas); /* between 0 and 100 */
  duracao *=100;
  duracao /= (2*MaxVozes*MaxSemiColcheias); /* between 0 and 100 */
  return ((int)
	  (P1*(100-tensao_da_musica)+
	   P2*(100-cruzamentos)+
	   P3*(30-labs(saltos-30))*33/10+ /* Incentivamos saltos proximos
					     da terca menor */
	   P4*(100-duracao)+
	   P5*soma_dos_pesos));
}
