#include "try.h"



int try(struct ctx_s * p_ctx, func_t * f, int arg) {
    
  p_ctx->magic = CORRECT_MAGIC;

  /* La valeur de %%esp dans %0 */
  /* La valeur de %%ebp dans %1 */
  asm("movl %%esp, %0" "\n\t"
      "movl %%ebp, %1"
      : "=r"(p_ctx->ctx_esp),
	"=r"(p_ctx->ctx_ebp)
      );

  return (*f)(arg);
  
}


int throw(struct ctx_s * p_ctx, int r) {
  /** rval permet d'assurer l'integrite de la valeur de r
      apres le changement de context*/
  static int rval; 
  rval = r;

  assert(p_ctx->magic==CORRECT_MAGIC);

  /* La valeur de %0 dans %%esp */
  /* La valeur de %1 dans %%ebp */
  asm("movl %0, %%esp" "\n\t"
      "movl %1, %%ebp"
      :: "r"(p_ctx->ctx_esp),
	 "r"(p_ctx->ctx_ebp)
      );

  return rval;

}
