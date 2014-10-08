#include "switch_to.h"
#include <signal.h>



/** */
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

/** */

struct ctx_s * ctx_courant = NULL;

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


struct ctx_s * ctxs;


 int main(){

   create_ctx(16384, f_ping, NULL);
   create_ctx(16384, f_pong, NULL);
   start_sched();

   exit(EXIT_SUCCESS);
 }

void f_ping(void * args){

  while(1){
    printf("ping");
  }
}


void f_pong(void * args){

  while(1){
    printf("pong");
  }
}



int create_ctx(int stack_size, func_t f, void * args){

  struct ctx_s * nouveau = malloc(stack_size);
  init_ctx(nouveau, stack_size, f, args);
    irq_disable();
  if (ctxs) {
    nouveau->next = ctxs->next;
    ctxs->next = nouveau;
  }
  else {
    ctxs = nouveau;
    ctxs->next = nouveau;
  }
  irq_enable();
  return 0;
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
    switch_to_ctx(ctxs);
  }
  
  irq_enable();
  
}


void start_sched(){

  
  setup_irq(TIMER_IRQ, yield);
  start_hw();
  yield();



}

