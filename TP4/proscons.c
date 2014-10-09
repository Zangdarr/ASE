#define N 100
#include "sem.h"

structsem_s mutex, vide, plein;

sem_init(&mutex,1);
sem_init(&vide,1);
sem_init(&plein,0);

void producteur(void)
{
	objet_t objet;

	while(1){
		produire_objet(&objet);
		sem_down(&vide);
		sem_down(&mutex);
		mettre_objet(objet);
		sem_up(&mutex);
		sem_up(&plein);
	}
}

void consommateur(void){
	
	objet_t objet;

	while(1){
		sem_down(&plein);
		sem_down(&mutex);
		retirer_objet(&objet);
		sem_up(&mutex);
		sem_up(&vide);
		utiliser_objet(objet);
	}
}

int main(){

	create_ctx(16384, producteur, NULL);
	create_ctx(16384, consommateur, NULL);
	start_sched();
	return 0;
}