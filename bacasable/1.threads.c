#include <pthread.h>
#include <stdio.h>

void *maFonction(void *arg) {
    printf("Bonjour depuis le thread!\n");
    pthread_exit(NULL); // Terminer le thread
}

int main() {
    pthread_t monThread; // Déclaration de l'identifiant du thread
    int retour;

    // Créer un nouveau thread
    retour = pthread_create(&monThread, NULL, maFonction, NULL);
    if (retour) {
        printf("Erreur lors de la création du thread.\n");
        return -1;
    }

    // Attendre que le thread se termine
    pthread_join(monThread, NULL);

    printf("Thread principal terminé.\n");
    return 0;
}

// gcc -pthread 'bacasable/1.threads.c' -o 'bacasable/1.threads' ; 'bacasable/1.threads' ; rm 'bacasable/1.threads'


// pthread_create est utilisée en langage C pour créer un nouveau thread. Elle prend quatre paramètres :

// thread: C'est un pointeur vers une variable de type pthread_t, qui est utilisée pour stocker l'identifiant du thread nouvellement créé.
// attr: C'est un pointeur vers un objet de type pthread_attr_t, qui spécifie les attributs du thread. Si vous souhaitez utiliser les valeurs par défaut, vous pouvez passer NULL.
// start_routine: C'est un pointeur vers la fonction que le nouveau thread exécutera dès qu'il sera créé. Cette fonction doit être de type void * (*)(void *), 
//		ce qui signifie qu'elle prend un pointeur générique comme argument et renvoie un pointeur générique. Cette fonction représente le point de départ de l'exécution du thread.
// arg: C'est un pointeur vers les arguments que vous souhaitez passer à la fonction start_routine.
// 		Ces arguments peuvent être de n'importe quel type et sont transmis à la fonction via un pointeur générique (void *).