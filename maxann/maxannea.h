/*********************** File: maxannea.h ***************************/
/* We are sorry but this is a bilingual code. */
//#include "ext.h"
//#include "typedefs.h"
//#include "SetUpA4.h"
#define True 1
#define False 0
#define MaxIt 1000
#define MaxVozes 4
#define MaxSemiColcheias 256
#define REST -1
#ifdef RAND_MAX
#undef RAND_MAX
#define RAND_MAX 32767
#endif
#define MaxCruzamentos 6
#define MaxTensao 66
typedef struct _nota Nota;
struct _nota { int pitch, velocity, start,dur; };
typedef Nota Partitura[MaxVozes][MaxSemiColcheias];
/* pitch and velocity are the MIDI values, start is a boolean variable that
   tells whether the note start at this moment or not. */
extern int P1, P2, P3, P4, P5;
extern int TENSAO_USUARIO[MaxSemiColcheias];
extern int qualidade(Partitura *X);
extern int DURACAO_ADEQUADA[MaxVozes][MaxSemiColcheias];
extern int pesos_das_notas[];
extern int tensao( Nota *n1, Nota *n2, Nota *n3, Nota *n4);
extern int cruzamento( Nota *n1, Nota *n2, Nota *n3, Nota *n4);
extern int aponta_escala[13];
//extern fptr *FNS;
void inicializa(Partitura *);
void copia(Partitura *, Partitura *);
void vizinho(Partitura *, Partitura *);
/*
typedef struct esqueleto {
  struct object e_ob;
  Atom e_av[MaxSemiColcheias];
  int e_ac;
  void *e_out;
} Esqueleto;
*/
