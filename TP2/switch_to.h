#define CORRECT_MAGIC 0xAABBAABB 

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef void (func_t)(void *); 

enum etat_e{ CTX_TERMINE, CTX_ACTIVABLE, CTX_INIT};

struct ctx_s {

  void * ctx_ebp;
  void * ctx_esp;
  int ctx_magic;
  func_t * ctx_f;
  void * ctx_args;
  void * ctx_stack;
  enum etat_e ctx_etat;

}ctx_s;

/** */
int init_ctx(struct ctx_s * p_ctx, int stack_size, func_t * f, void* args);

/** */
void switch_to_ctx(struct ctx_s * p_ctx);

void f_ping(void * args);
void f_pong(void * args);
