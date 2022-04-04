//
//  main.c
//  ExoREV5Listes
//
//  Created by jeremy fouquet on 04/04/2022.
//

#include <stdio.h> // puts(), printf()
#include <stdlib.h> // exit()
#include <string.h> // strlen()

#define string char *
#define formatBool(b) ((b) ? "true" : "false")


void usage(const string, const string); // prototype
void scan_file(const string);
int compte_mots(const string);
void copieChaine(string, string);
void exercice_E_1(const string) ; // prototype
void fonction_E_1(void);

const int tailleMot = 32;
char motOrigine[tailleMot];
char motChange[tailleMot];
string filename;
string copie;

int main(int argc, const char * argv[]) {
    printf("%s\n", "E. Exercices sur les listes");
    if (argc < 5) usage("Champs renseignées en ligne de commande", "<mot à remplacer> <mot de remplacement> <fichier d'entrée> <fichier de sortie>") ;
    copieChaine(motOrigine, argv[1]);
    copieChaine(motChange, argv[2]);
    filename = argv[3];
    copie = argv[4];
    exercice_E_1("E.1 Exercices en C");
    puts("");
    return 0;
}

void exercice_E_1(const string titre) {
    printf("\n%s\n", titre);
    printf("\n%s\n", "A. Écrire un programme qui lit une liste de mots dans un fichier et remplace chaque occurrence d’un mot A par un autre mot B, les deux mots étant fournis sur la ligne de commande ainsi que le nom des fichiers d’entrée et de sortie :");
    printf("\n%s\n", "> ExoREV5Listes <mot à remplacer> <mot de remplacement> <fichier d'entrée> <fichier de sortie>");
    fonction_E_1();
    puts("");
}

void fonction_E_1() {
    printf("mot d'origne : %s\n", motOrigine);
    printf("mot modifié : %s\n", motChange);
    printf("nom fichier : %s\n", filename);
    printf("mot fichier copie : %s\n", copie);
    scan_file(filename);
}

void copieChaine(string origin, string copie) {
    char * P = copie;
    for (int i = 0; * P != '\0'; i++, P++) {
        origin[i] = * P;
    }
}


void scan_file(const string filename) {
    int nb_mots = compte_mots(filename) ;

    FILE * R = fopen(filename, "r") ; // ouvre le canal R en mode "r" pour filename
    if (! R) usage(filename, "Le fichier est introuvable") ; // si pas de fichier message erreur exit
    char * P; // mon pointeur dynamique
    char mots[nb_mots][tailleMot] ;
    int lu ;
    for (int max = 0 ; max < nb_mots ; max++) {
        lu = fscanf(R, "%s", mots[max]) ;
    }
    P = mots;
    printf("%s \n", "Ici j'affiche la chaine de caractere stockée dans le vecteur à double dimension : ") ;
    puts("");
    for(int max = 0; mots[max] && max < nb_mots; max++) {
        printf("%s ", mots[max]) ;
    }
    puts("");
    puts("");
    printf("%s \n", "Ici j'affiche les entier à partir du vecteur à double dimension : ") ;
    puts("");
    for(int max = 0; mots[max] && max < nb_mots; max++) {
        string mot = mots[max];
        int tailleMot = strlen(mot);
        for (int iCaractere = 0; iCaractere < tailleMot; iCaractere++) {
            int entier;
            entier = (int) mot[iCaractere];
            printf("%d ", entier);
        }
    }
    puts("");
    puts("");
    printf("%s \n", "Ici j'affiche la chaine de caractere via le pointeur : ") ;
    puts("");
    for (int i = 0; i < nb_mots; i++) {
        printf("%s ", P+(i*tailleMot));
    }
    puts("");
    puts("");
    printf("%s \n", "Ici j'affiche les entier à partir du pointeur : ") ;
    puts("");
    for (int i = 0; i < nb_mots; i++) {
        string mot = P+(i*tailleMot);
        int tailleMot = strlen(mot);
        for (int iCaractere = 0; iCaractere < tailleMot; iCaractere++) {
            int entier;
            entier = (int) mot[iCaractere];
            printf("%d ", entier);
        }
    }
    puts("");
    fclose(R) ; // ferme le canal
}


int compte_mots(const string filename) {
    FILE * R = fopen(filename, "r") ; // Ouvre le canal
    if (! R) usage(filename, "Le fichier est introuvable") ; // si pas de fichier message erreur exit
    
    printf(filename);
    char stop[tailleMot] ;
    int scan, nb_mots = 0 ;
    while((scan = fscanf(R, "%s", stop)) != EOF) {
        if (scan) nb_mots++ ;
        else usage(filename, "Le fichier ne peut pas être lu") ;
    }
    fclose(R) ; // ferme le canal
    return nb_mots ;
}

void usage(const string E, const string D) {
    printf("Erreur en provenance de : %s\n", E);
    printf("Detail : %s\n", D);
    exit(1) ;
}

