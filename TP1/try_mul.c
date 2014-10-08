#include "try.h"



/** structure dans laquelle sera stockee les coordonnees du context de depart*/
struct ctx_s * env;


/** fonction recursive demandant des nombres en entree utilisateur et effectuant la multiplication de ceux-ci */
static int mul(int depth) {
  int i;

  switch (scanf("%d", &i)) {
    case EOF :
      return 1;
    case 0 : 
      return mul(depth+1);
    case 1 :
      if (i){ 
	return i * mul(depth+1);
      }
      else {
	throw(env,0);
      }

    }
  return -1;

}

/** MAIN*/
int main(){

  int product;

  env = malloc(sizeof(ctx_s));
  
  product = try(env,&mul,0);
  printf("product = %d\n",product);
  
  free(env);

  return 0;

}
