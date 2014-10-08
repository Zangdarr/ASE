#define CORRECT_MAGIC 0xAABBAABB 

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef int (func_t)(int); 

struct ctx_s {

  void * ctx_ebp;
  void * ctx_esp;
  int magic;

}ctx_s;

/** Sauve le context actuel et en cree un nouveau pour executer une fonction*/
int try(struct ctx_s * p_ctx, func_t * f, int arg);

/** Retourne au context passe en parametre et fournit une information*/
int throw(struct ctx_s * p_ctx, int r);
