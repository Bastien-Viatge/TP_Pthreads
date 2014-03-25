#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>
#define MAX_FACTORS 10000
#define MAX_MEM 1000


//Structure de donnée C avec iterateur qui parcoure next pour stocker les nombres premiers
struct primeFactorMemory_t{
	uint64_t number;
	uint64_t factors[MAX_FACTORS];
	primeFactorMemory_t * next;
};



static pthread_mutex_t mutexPrintfactors = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutexFile = PTHREAD_MUTEX_INITIALIZER;
static 	FILE* fichier;
static primeFactorMemory_t primeFactorMemory[MAX_MEM];

int is_prime( uint64_t p )
{
	uint64_t q = 2;
	for (q = 2; q < (uint64_t)sqrt(p); q++ )  //comparaison jusqu'à la racine seulement
	{
		if ( p%q == 0 )
		{
			return 0;
		}
	}
	return 1;
}




//-----------------------------------------------print_prime_factor qu3
//void print_prime_factor( uint64_t n )
//{
//
//	printf("%lu :",n);
//	uint64_t i ;
//
//	uint64_t racine =(uint64_t)sqrt(n);
//
//	for( i= 2 ; i<=racine ; i++)
//	{
//		if( n%i == 0 )
//		{
//
//			//c=strcat(c," ");
//			//c=strcat(c,itoa(i,c,10));
//			printf(" %lu",i);
//			n /= i;
//			i--;
//
//		}
//
//
//	}
//	if ( n !=1)
//		printf(" %lu \n",n);
//}//--------Fin print_prime_factor qu3



/*
int main() //Question 3
{
	FILE* fichier = fopen("numbers.txt","r+");
	if( fichier != NULL )
	{
		// In order to enter in while =1
		uint64_t i = 1;
		int nbtokens;
		//int64_t j = 1;
		nbtokens=fscanf(fichier,"%lu",&i);
		while(nbtokens != 0 && nbtokens != EOF)
		{
			printf("nbtokens %d : ",nbtokens);
			print_prime_factor(i);
			nbtokens=fscanf(fichier,"%lu",&i);

		}
	}
	
}//Fin de pthread Main

*/





int getMaxFactors()
{
	return (int)sqrt(pow(2,64)-1);
}


int get_prime_factors( uint64_t n, uint64_t* dest )
{

	uint64_t divider;
	int factorNumber = 0;
	uint64_t racine =(uint64_t)sqrt(n);

	for( divider= 2 ; divider<=racine ; divider++)
	{
		if( n%divider == 0 )
		{
			dest[factorNumber++] = divider;
			n /= divider;
			divider--;

		}


	}
	if ( n !=1)
	{
		dest[factorNumber++] = n;
	}


	return factorNumber;
}


void print_prime_factors(uint64_t n) {
  uint64_t factors[MAX_FACTORS];
  int factorNumber = get_prime_factors(n, factors);

  // We use a mutex to guarantee that output will appear in order
  pthread_mutex_lock(&mutexPrintfactors);
  printf("%lu: ", n);
  for (int i = 0; i < factorNumber; ++i) {
    printf("%lu ", factors[i]);
  }
  printf("\n");
  pthread_mutex_unlock(&mutexPrintfactors);
}

void *pthreadMainBoucle(void *i)
{
	uint64_t number = (uint64_t)i;
	print_prime_factors(number);
	pthread_exit( NULL);
}


void *pthreadMain()

//Starting function for threads
//call print_prime_factor(i) for each number of the file
{
	//pthread_t tid = pthread_self( );

	uint64_t nbreLu = 1;
	int nbtokens = 1;
	while (nbtokens != 0 && nbtokens != EOF)
	{
		pthread_mutex_lock( &mutexFile);
		nbtokens=fscanf(fichier,"%lu",&nbreLu);
		pthread_mutex_unlock( &mutexFile);
		print_prime_factors(nbreLu);

	}
	pthread_exit( NULL);
}



int main() { 
	//Open "numbers.txt" 
	fichier = fopen("numbers.txt","r+");
	int crdu;
	if( fichier != NULL ) 
	{ 
		pthread_t pthread1,pthread2; 

		//--------------------------------------Initialisation du mutex 
		pthread_mutex_init(&mutexFile,NULL);
		pthread_mutex_init(&mutexPrintfactors,NULL);

		//---------------------------------------------Creating pthread 
 


		crdu = pthread_create( &pthread1, NULL, pthreadMain, NULL);
		if ( crdu != 0 ) 
		{
			printf("Error : code=%d",crdu); 
			exit ( -1); 
		}
		crdu = pthread_create( &pthread2, NULL, pthreadMain, NULL);
		if ( crdu != 0 ) 
		{ 
			printf("Error : code=%d",crdu);
			exit ( -1);
		} 
		//------------------------------------------------Join pthread
		crdu = pthread_join(pthread1, NULL);
		if ( crdu != 0 ) {
			printf("Error : code=%d",crdu);
			exit ( -1);
		} 
		crdu = pthread_join(pthread2, NULL);
		if ( crdu != 0 ) 
		{ 
			printf("Erreur : code=%d",crdu);
			exit ( -1);
		}
	} 

	//---------------------------------------Destruction du mutex
	crdu = pthread_mutex_destroy( &mutexFile);
	if ( crdu != 0 )
	{
		printf("Erreur : code=%d",crdu); exit( -1);
	}
	crdu = pthread_mutex_destroy( &mutexPrintfactors);
	if ( crdu != 0 ) 
	{
		printf("Erreur : code=%d",crdu); exit( -1);
	}

	pthread_exit( NULL);
}


