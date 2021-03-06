#include "switch_to.h"



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
    ctx_courant->ctx_f(ctx_courant->ctx_args);
  }
  else {
    return;
  }
 }

struct ctx_s ctx_ping;
struct ctx_s ctx_pong;


 int main(){

   init_ctx(&ctx_ping, 16384, f_ping, NULL);
   init_ctx(&ctx_pong, 16384, f_pong, NULL);
   switch_to_ctx(&ctx_ping);
   exit(EXIT_SUCCESS);
 }

void f_ping(void * args){

  while(1){
    printf("Heeeeeyyyy Brother\n");
    switch_to_ctx(&ctx_pong);
    printf("Heeeeeyyyy Sister\n");
    switch_to_ctx(&ctx_pong);
    printf("OOOOOOOOOOOOOhhh\n");
    switch_to_ctx(&ctx_pong);
  }
}


void f_pong(void * args){

  while(1){
    printf("There's an endless road to rediscover\n");
    switch_to_ctx(&ctx_ping);
    printf("Know the water sweat but blood is thicker\n");
    switch_to_ctx(&ctx_ping);
    printf("OOOOOOOooooooohhh\n");
    switch_to_ctx(&ctx_ping);
  }
}

   
