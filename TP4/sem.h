#define SEM_CORRECT_MAGIC 0xCCBBCCBB
#define CORRECT_MAGIC 0xAABBAABB

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hw.h"

typedef void (func_t)(void *); 
enum etat_e{ CTX_TERMINE, CTX_ACTIVABLE, CTX_INIT, CTX_BLOQUE};

struct ctx_s {

  void * ctx_ebp;
  void * ctx_esp;
  int ctx_magic;
  func_t * ctx_f;
  void * ctx_args;
  void * ctx_stack;
  enum etat_e ctx_etat;
  struct ctx_s * next;
  struct ctx_s * sem_next;

}ctx_s;



struct sem_s{

	int sem_cptr;
	struct ctx_s * liste_bloques;
	int sem_magic;
};




void sem_up(struct sem_s * sem);
void sem_down(struct sem_s * sem);
void sem_init(struct sem_s * sem, unsigned int val);

void yield();


int init_ctx(struct ctx_s * p_ctx, int stack_size, func_t * f, void* args);

/** */
void switch_to_ctx(struct ctx_s * p_ctx);

int create_ctx(int stack_size, func_t f, void * args);
