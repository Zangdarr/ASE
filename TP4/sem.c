#include "sem.h"

struct ctx_s * ctx_courant = NULL;

void sem_up(struct sem_s * sem){
	
	assert(sem->sem_magic = SEM_CORRECT_MAGIC);
	irq_disable();
	sem->sem_cptr ++;
	if(sem->sem_cptr <= 0) {
		//Reveil
		assert(sem->liste_bloques);
		sem->liste_bloques->ctx_etat = CTX_ACTIVABLE;
		sem->liste_bloques = sem->liste_bloques->sem_next;
		ctx_courant->sem_next = NULL;
	}
	irq_enable();
}

void sem_down(struct sem_s * sem){

	irq_disable();
	assert(sem->sem_magic = SEM_CORRECT_MAGIC);
	sem->sem_cptr --;
	if(sem->sem_cptr >0) 
		return;
	ctx_courant->ctx_etat = CTX_BLOQUE;
	ctx_courant->sem_next = sem->liste_bloques;
	sem->liste_bloques = ctx_courant;
	irq_enable();
	yield();
}


void sem_init(struct sem_s * sem, unsigned int val){
	sem->sem_cptr = val;
	sem->liste_bloques = NULL;
	sem->sem_magic = SEM_CORRECT_MAGIC;
}


void yield(){
  irq_disable();
  if(ctx_courant){
    struct ctx_s * tmp;
    
    while(ctx_courant->next->ctx_etat == CTX_TERMINE && ctx_courant->next != ctx_courant) {
      tmp = ctx_courant->next;
      ctx_courant->next = ctx_courant->next->next;
      free(tmp->ctx_stack);
      free(tmp);
    }
    if(ctx_courant->next->ctx_etat != CTX_TERMINE){
      switch_to_ctx(ctx_courant->next);
    }
    else {
      
      
      irq_enable();
      exit(0);

    }
  }
  else{
    switch_to_ctx(ctx_courant);
  }
  
  irq_enable();
  
}
int create_ctx(int stack_size, func_t f, void * args){

  struct ctx_s * nouveau = malloc(stack_size);
  init_ctx(nouveau, stack_size, f, args);
    irq_disable();
  if (ctx_courant) {
    nouveau->next = ctx_courant->next;
    ctx_courant->next = nouveau;
  }
  else {
    ctx_courant = nouveau;
    ctx_courant->next = nouveau;
  }
  irq_enable();
  return 0;
}

void switch_to_ctx(struct ctx_s * p_ctx){
  
  if (ctx_courant) {
    asm("movl %%ebp, %0" "\n\t"
	"movl %%esp, %1"
	: "=r"(ctx_courant->ctx_ebp),
	  "=r"(ctx_courant->ctx_esp));
  }
  ctx_courant = p_ctx;
  asm("movl %0, %%ebp" "\n\t"
      "movl %1, %%esp"
      :: "r" (ctx_courant->ctx_ebp),
       "r" (ctx_courant->ctx_esp));


  if(ctx_courant->ctx_etat == CTX_INIT){
    ctx_courant->ctx_etat = CTX_ACTIVABLE;
irq_enable();
    ctx_courant->ctx_f(ctx_courant->ctx_args);
    ctx_courant->ctx_etat = CTX_TERMINE;
  }
  else {
    return;
  }
 }
int init_ctx(struct ctx_s * p_ctx, int stack_size, func_t f, void* args){
 
  if(!(p_ctx->ctx_stack = malloc(stack_size))){
    exit(EXIT_FAILURE);

  }
  p_ctx->ctx_esp = p_ctx->ctx_ebp = p_ctx->ctx_stack + stack_size - sizeof(void*);
  p_ctx->ctx_f = f;
  p_ctx->ctx_args = args;
  p_ctx->ctx_etat = CTX_INIT;
  p_ctx->ctx_magic = CORRECT_MAGIC;
  return 0;
  
}


