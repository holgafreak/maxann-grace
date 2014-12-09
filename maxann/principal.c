/*********************** File: principal.c ***************************/
#include "maxannea.h"
//extern fptr *FNS;
int P1, P2, P3, P4, P5;
Partitura X;
float myexp(float x);
int myrand();
float Esfria(float Temperature)
{
  return(Temperature*0.9);
}
int Aceita(float Temperature, float Variation)
{
  float aux,P,Q;
  if (Temperature != 0.0)
    aux = Variation/Temperature;
  else
    aux = 0;
  P = 1.0/myexp(-aux);
  Q = (float)myrand();
  Q = Q/32767.0;
  return (Q < P);
}
Partitura Xmax, Xnovo;
void find_best_song()
{
  long Qualidade_max, Qualidade_Atual,
    Qualidade_Nova, Variacao;
  float Temperature;
  int Cont, Iteracoes, Aumentou, i;
  /*  P1 = P4 = 2;  Initial weights for the 5 criteria 
  P5 = 3;
  P3 = 1;
  P2 = 1;
  */
  inicializa(&X); /* Generate initial song */
  Qualidade_Atual = qualidade(&X);
  copia(&Xmax,&X);
  Qualidade_max = Qualidade_Atual;
  Aumentou = True;
  Iteracoes = 0;
  Temperature = 100.0;
  while (Aumentou) /* While the quality is increasing... */
    {
      Cont = MaxIt;
      Aumentou = False;
      for(Cont = MaxIt; Cont > 0; Cont--)
	{
	  Iteracoes++; vizinho(&Xnovo, &X); /* Pick a new song in the neighborhood */
	  Qualidade_Nova = qualidade(&Xnovo);
	  Variacao = Qualidade_Nova - Qualidade_Atual;
	  if (Variacao > 0)
	    {
	      copia(&X,&Xnovo);
	      Qualidade_Atual = Qualidade_Nova;
	      if (Qualidade_Nova > Qualidade_max)
		{
		  copia(&Xmax, &Xnovo);
		  Qualidade_max = Qualidade_Nova;
		}
	      Aumentou = True;
	    }
	  else
	    {
	      if (Aceita(Temperature,Variacao))
		{
		  copia(&X, &Xnovo);
		  Qualidade_Atual = Qualidade_Nova;
		}
	    }
	}/* for */
      Temperature = Esfria(Temperature);
    }
}
long semente = 1234567;
/* Since the ANSI library used to create external objects does not
   have the rand and the exp functions, we had to write our own. */
int myrand()
{
  semente =((semente*1103515245+12345)>>1)&2147483647;
  return (int) semente&32767;
}
float myexp(float x)
{
  /* Uses the Taylor Series in order to give a good aproximation of
     exp(x) if x is something between 0 and 5. We are using the
     following expression: (1+x+x*x/2+x*x*x/6+x*x*x*x/24+x*x*x*x*x/120
     +X^6/720 +X^7/5040 +X^8/40320 +X^9/362880
     +X^10/3628800);
  */
  return (1.0+x*(1.0+x*(0.5+x*(0.16666667+x*(0.0416667+x*(1.0/120+x*
							  (1.0/720+x*(1.0/5040+x*(1.0/40320+x*(1.0/362880+x*(x/3628800)))))))))));
}
