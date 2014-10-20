#define N 100
#include "sem.h"


struct sem_s mutex; 
struct sem_s vide;
struct sem_s plein;



int stock_produits;

void produire_objet(){
	stock_produits++;
}

void mettre_objet(){
	printf("stock : %d\n",stock_produits);
}

void retirer_objet(){
	stock_produits--;
}

void utiliser_objet(){
	printf("stock : %d\n",stock_produits);
}

void producteur(void* objet)
{

	while(1){
		produire_objet();
		sem_down(&vide);
		sem_down(&mutex);
		mettre_objet();
		sem_up(&mutex);
		sem_up(&plein);
	}
}

void consommateur(void* objet){
	
	

	while(1){
		sem_down(&plein);
		sem_down(&mutex);
		retirer_objet();
		sem_up(&mutex);
		sem_up(&vide);
		utiliser_objet();
	}
}


void start_sched(){

  
  setup_irq(TIMER_IRQ, yield);
  start_hw();
  yield();

  }

int main(){

	stock_produits = 1;
	sem_init(&mutex,1);
	/* Nombre de places libres
		N places libres.
	*/
	sem_init(&vide,N);

	/* 0 places occupées */ 
	sem_init(&plein,0);
	
	create_ctx(16384, producteur, NULL);
	create_ctx(16384, consommateur, NULL);
	start_sched();
	return 0;

}