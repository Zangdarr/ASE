#define CORRECT_MAGIC 0xAABBAABB 
#define TIMER_IRQ 2

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef void (func_t)(void *); 
typedef void (irq_handler_func_t)(void); 


enum etat_e{ CTX_TERMINE, CTX_ACTIVABLE, CTX_INIT};

struct ctx_s {

  void * ctx_ebp;
  void * ctx_esp;
  int ctx_magic;
  func_t * ctx_f;
  void * ctx_args;
  void * ctx_stack;
  enum etat_e ctx_etat;
  struct ctx_s * next;

}ctx_s;

/** */
int init_ctx(struct ctx_s * p_ctx, int stack_size, func_t * f, void* args);

/** */
void switch_to_ctx(struct ctx_s * p_ctx);

int create_ctx(int stack_size, func_t f, void * args);

void f_ping(void * args);
void f_pong(void * args);



void setup_irq(unsigned int irq, irq_handler_func_t handler);
void start_hw();
void start_sched();

void irq_disable();
void irq_enable();
