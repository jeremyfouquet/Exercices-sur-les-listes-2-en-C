/*
   # *******************************************************
   # Nom ......... : main.c
   # Rôle ........ : Exercices sur les listes en C
   # Auteur ...... : Jeremy Fouquet
   # Version ..... : V1 2022
   # Licence ..... : Réalisé dans le cadre du cours de La Licence Informatique de L IED
   # Compilation :  gcc main.c
   # Execution : ./a.out
   # Usage : remplacer|compter|majuscule (en fonction de l'option choisi) <fichier de sortie>
   # *******************************************************
*/

#include <stdio.h> // puts(), printf()
#include <stdlib.h> // exit()
#include <string.h> // strlen()

#define string char *
#define nil NULL
typedef struct node { string car ; struct node * cdr ; } node, * list ;


void usage(const string, const string); // prototype
char * scan_file(const string);
int compte_mots(const string);
void copieChaine(string, string);
void exercice_E_1(const string, int argc, char * argv[]) ; // prototype
void fonction_E_1_A(char * argv[]);
void fonction_E_1_B();
void fonction_E_1_C();
void modification(char *, char *);
int my_strcmp(const string, const string);
list cons(string car, list L);
int estMajuscule(char C);

const int tailleMot = 32;
int nbToto = 0;
char motOrigine[tailleMot];
char motChange[tailleMot];
string filename = "fichier_in.txt";
string copie = "fichier_out.txt";

int main(int argc, const char * argv[]) {
    printf("%s\n", "E. Exercices sur les listes");
    if (argc < 2) usage("Nombre d'arguments", "remplacer|compter|majuscule (en fonction de l'option choisi)") ;
    exercice_E_1("E.1 Exercices en C", argc, argv);
    puts("");
    return 0;
}

void exercice_E_1(const string titre, int argc, char * argv[]) {
    char * choix = argv[1];    
    printf("\n%s\n", titre);
    if(my_strcmp("remplacer", choix) == 0) {
        if (argc < 4) usage("Nombre d'arguments", "remplacer <mot à modifier> <mot modifié>") ;
        printf("\n%s\n", "A. Écrire un programme qui lit une liste de mots dans un fichier et remplace chaque occurrence d’un mot A par un autre mot B, les deux mots étant fournis sur la ligne de commande ainsi que le nom des fichiers d’entrée et de sortie :");
        puts("");
        fonction_E_1_A(argv);
    } else if (my_strcmp("compter", choix) == 0) {
        printf("\n%s\n", "B. Compte combien de fois ”toto” figure dans le fichier d’entrée. Le main() doit imprimer le résultat sur stdout. Note : pour tester si deux chaînes sont identiques, il faut utiliser la fonction strcmp() de la bibliothèque string.h ; en effet == (eql) ne teste que l’identité des pointeurs.");
        fonction_E_1_B();
    } else if (my_strcmp("majuscule", choix) == 0) {
        printf("\n%s\n", " C. Écrire un programme qui lit une liste de mots dans un fichier et ne garde que les mots commençant par une majuscule. Utiliser l’algorithme de modification de liste. Le main() doit imprimer le résultat dans le fichier de sortie.");
        fonction_E_1_C();
    } else {
        usage("Valeur d'argument", "il faut choisir une option en premier argument parmis remplacer ou compter ou majuscule") ;
    }
}

void fonction_E_1_A(char * argv[]) {
    copieChaine(motOrigine, argv[2]);
    copieChaine(motChange, argv[3]);
    printf("Vous souhaitez modifier le mot : %s en %s\n", motOrigine, motChange);
    printf("Nom du fichie original : %s\n", filename);
    printf("Nom du noveau fichier : %s\n", copie);
    int nb_mots = compte_mots(filename) ;
    FILE * R = fopen(filename, "r") ; // ouvre le canal R en mode "r" pour filename
    if (! R) usage(filename, "Le fichier est introuvable") ; // si pas de fichier message erreur exit
    int lu;
    string mots[nb_mots] ;
    for (int max = 0 ; max < nb_mots ; max++) {
        char mot[tailleMot] ;
        if((lu = fscanf(R, "%s", mot)) == EOF) usage(filename, "Un probleme est survenue dans la lecture du fichier");
        char * P = mot;
        if(my_strcmp(motOrigine, mot) == 0) {
            P = motChange;
        }
        mots[max] = strdup(P) ;
    }
    fclose(R) ; // ferme le canal
    FILE * W = fopen(copie, "w") ; // ouvre le canal W en mode "w" pour copie
    for (int max = 0 ; max < nb_mots ; max++) {
        fputs(mots[max], W);
        fputc(' ', W);
    }
    if (! W) usage(copie, "Erreur inconnu") ;
    fclose(W) ; // ferme le canal

}

void fonction_E_1_B() {  
    int nb_mots = compte_mots(filename) ;
    FILE * R = fopen(filename, "r") ; // ouvre le canal R en mode "r" pour filename
    if (! R) usage(filename, "Le fichier est introuvable") ; // si pas de fichier message erreur exit
    int lu;
    string mots[nb_mots] ;
    for (int max = 0 ; max < nb_mots ; max++) {
        char mot[tailleMot] ;
        if((lu = fscanf(R, "%s", mot)) == EOF) usage(filename, "Un probleme est survenue dans la lecture du fichier");
        char * P = mot;
        if(my_strcmp("toto", mot) == 0) {
            nbToto++;
        }
        mots[max] = strdup(P) ;
    }
    fprintf(stdout, "\nNombre de %s %d\n", "toto", nbToto) ;
    fclose(R) ; // ferme le canal
}

void fonction_E_1_C() {
    int nb_mots = compte_mots(filename) ;
    FILE * R = fopen(filename, "r") ; // ouvre le canal R en mode "r" pour filename
    if (! R) usage(filename, "Le fichier est introuvable") ; // si pas de fichier message erreur exit
    FILE * W = fopen(copie, "w") ; // ouvre le canal W en mode "w" pour copie
    if (! W) {fclose(R); usage(copie, "Erreur inconnu"); } ;
    int lu;
    list L = nil;
    for (int max = 0 ; max < nb_mots ; max++) {
        char mot[tailleMot] ;
        if((lu = fscanf(R, "%s", mot)) == EOF) usage(filename, "Un probleme est survenue dans la lecture du fichier");
        char * P = mot;
        if(estMajuscule(P[0])==0) {
            L = cons(strdup(P), L);
        }
    }
    while(L) {
        fputs(L->car, W);
        fputc(' ', W);
        L=L->cdr;

    }
    fclose(R) ; // ferme le canal
    fclose(W) ; // ferme le canal
}

int estMajuscule(char C){
    //https://www.ibm.com/docs/fr/sdse/6.3.1?topic=configuration-ascii-characters-from-33-126
    int majuscule = -1;
    if(C >= 65 && C <= 90){
        majuscule = 0;
    }
    return majuscule;
}

int my_strcmp(const string S1, const string S2){
    int compare = 0;
    int i;
    for(i = 0; S1[i] == S2[i] && S1[i] != '\0'; i++);
    if(S1[i] > S2[i]){
        compare = 1;
    }
    else if(S1[i] < S2[i]) {
        compare = -1;
    }
    else {
        compare = 0;
    }
    return compare;
}

void copieChaine(string origin, string copie) {
    char * P = copie;
    for (int i = 0; * P != '\0'; i++, P++) {
        origin[i] = * P;
    }
}


int compte_mots(const string filename) {
    FILE * R = fopen(filename, "r") ; // Ouvre le canal
    if (! R) usage(filename, "Le fichier est introuvable") ; // si pas de fichier message erreur exit
    char stop[tailleMot] ;
    int scan, nb_mots = 0 ;
    while((scan = fscanf(R, "%s", stop)) != EOF) {
        if (scan) nb_mots++ ;
        else usage(filename, "Une erreur dans le fichier ne peut être lu") ;
    }
    fclose(R) ; // ferme le canal
    return nb_mots ;
}

list cons(string car, list L) {
    list new = malloc(sizeof(node)) ;
    if (! new) usage("cons : manque de RAM", "Revoir la liste") ; // enfin, un peu de sérieux !
    new -> car = car ;
    new -> cdr = L ;
    return new ;
}

void putlist(list L) {
    if (! L) return ; // nil : fin de liste
    printf("%c \n", L -> car) ;
    putlist(L -> cdr) ;
}

void usage(const string E, const string D) {
    printf("Erreur en provenance de : %s\n", E);
    printf("Detail : %s\n", D);
    exit(1) ;
}
