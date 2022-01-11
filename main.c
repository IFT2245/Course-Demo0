/*
 * IFT 2245
 * Démonstration 1
 *
 * Ce petit programme explore les aspects les plus généraux de C.
 * Cela devrait vous servir de rappel. Si vous n'avez JAMAIS écrit
 * de programme en C, il est très fortement conseillé de faire des
 * lectures / exercices en C.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define flush() do { fflush(stdout); } while(0)
#define STATEMENT() do { ;} while(0)
#define MULT_BY_TWO(a) do {((a) << 1); } while(0)
#define CONDITION 1

void function() {
    MULT_BY_TWO(5);
}

void print_f_example() {
    /**
     * %d : entier
     * %c : charactère (alphanumérique)
     * %f : point flotant
     * %s : NULL TERMINATED string
     * %lf : double
     *  ^ large
     * %x : hexa
     */
    char *a_string = "Bienvenue au cours IFT 2245";
    printf("Message: %s\n", a_string);
    flush();

    int a_number = 5;

    printf("Un nombre: %d\n", a_number);
    flush();

    int another_number = 10;

    printf("%d + %d = %d\n", a_number, a_number, another_number);
    flush();

    printf("Un float: %f\n", (float) 10.0);
    flush();

    printf("Un double: %lf\n", (double) 10.0);
    flush();
}

void bits_example() {
    unsigned int a = 10;

    for (unsigned int i = 0; i <= 5; ++i) {
        // représentation hexadécimale (x)
        // le # demande d'imprimer le préfix 0x
        printf("%d = %#x\n", i, i);
        flush();
    }

    for (unsigned int i = 0; i <= 5; ++i) {
        // l'opérateur shift-left (<<) permet de déplacer
        // la présentation binaire vers la gauche du nombre
        // de positions spécifiées
        // (il y a aussi shift right) (>>)
        // 0b00010 << 2 = 0b01000
        unsigned int j = i << 1U;
        // le U après le 1     ^
        // indique que la constante est non-signée
        printf("%d = %#x\n", j, j);
        flush();
    }

    // les shift combinés avec l'opération AND binaire
    // permet d'aller chercher les parties d'un nombre
    unsigned char byte = 0b11110000;
    //                 TOP:^---|
    //                  BOTTOM:^---
    unsigned char top = (byte >> 4U) & 0xFU;
    unsigned char bot = byte & 0xFU;

    printf("TOP: %#x\n", top); // devrait être 0xF
    flush();

    printf("BOTTOM: %#x\n", bot); // devrait être 0x0
    flush();
}

void types_in_c() {
    /**
     * typed v.s dynamic
     * weak v.s strong
     *
     * C: weak typed
     */


    // En C, tout ce qui est != 0 => vrai

    bool i = true;
    printf("i = %d\n", i);

    int j = i;
    printf("j = %d\n", j);

    // Signature des types:
    // unsigned {integer type}
    // signed {integer type} == {integer type}
    //
    // Non signé: toujours non-négatif (>= 0)
    // Signé: Pourrait être négatif,
    // complément à 2 de la valeur positive

    // Petit piège courant:
    int *k, l; // k, l
    // Attention! k est un pointeur, mais pas l!
    // L'étoile va avec le nom de la variable et non le type!

    // -----------------  ATTENTION ------------------
    // Les règles exactes de typages en C sont complexes
    // et non-intuitives. Une opération qui semble
    // normale pour un humain entre deux types différents
    // peut avoir un résultat inattendu. Il est préférable
    // de faire des opérations entre des variables de même
    // type (ou d'insérer des casts). Une bonne lecture est:
    // https://stackoverflow.com/a/46073296/5092307
}

void function_with_reference(int *i) {
    *i <<= 1; // <------- Qu'est-ce que cette ligne va faire?
    i = (int *) 5; // <------ change la valeur du POINTEUR qui est passé par VALEUR
}

void pointers() {
    /**
     * Pointeur: référence vers quelque chose.
     *
     * Un pointeur a pour valeur une adresse.
     *
     * Le language C définit deux opérations principales
     * sur les adresses:
     *
     *      - *address : valeur à l'adresse
     *      - &variable : adresse de la variable
     */
    int a = 5;
    int *pInt = &a;
    int b = a;

    // Comportement des pointeurs

    printf("a = %d\n", a);
    flush();

    printf("pInt = %d\n", *pInt);
    flush();

    printf("b = %d\n", b);
    flush();

    // Observons ce qu'il se passe quand on change la valeur
    a = 6;

    printf("a = %d\n", a);
    flush();

    printf("pInt = %d\n", *pInt);
    flush();

    printf("b = %d\n", b);
    flush();

    // Comment on peut se servir des pointeurs

    int i = 10;
    printf("i = %d\n", i);
    flush();

    int *another_int_pointer = &i;
    function_with_reference(another_int_pointer);
    printf("i = %d\n", i);
    flush();

    printf("*(&i) = %d\n", *another_int_pointer);
    flush();

    // Le type (void*) est le pointeur UNIVERSEL.
    // Il permet de retourner des pointeurs
    // générique et sans type affecté.
    // C'est ce que malloc retourne après une allocation
    // mémoire. Il est nécéssaire de le cast vers le type
    // voulu avant de l'utiliser.
}

void constant_definition_in_c() {

#define NUMBER_OF_BITS_IN_BYTE 8
#undef NUMBER_OF_BITS_IN_BYTE
#define NUMBER_OF_BITS_IN_BYTE 0x1000

//#define I_AM_ON_A_LINUX_COMPUTER

#ifdef I_AM_ON_A_LINUX_COMPUTER
    printf("Yay!\n");
#else
    printf("Have you heard about GNU/Linux?\n");
#endif
}


void control_structures_in_c() {

    if (CONDITION) {
        printf("If\n");
    }

    while (CONDITION) {
        printf("While\n");
        break;
    }

    do {
        printf("Do... while\n");
        break;
    } while (CONDITION);

    switch (CONDITION) {
        case 1:
            STATEMENT();
            break;
        case 2: {
            STATEMENT();
            STATEMENT();
            STATEMENT();
            STATEMENT();
            STATEMENT();
            STATEMENT();
            STATEMENT();
        }
            break;
        default:
            break;
    }

    goto jump_point;
    /* Au sujet des GOTOS:
     *  - Pas interdits en C
     *  - Un goto "plus bas" est parfois
     *        nécéssaire pour une gestion
     *        d'erreurs efficace
     *  - Un goto en "en haut" est dangereux!
     *  - Les gotos sont dangereux et
     *       devraient être utilisés avec prudence
     */
    printf("Do not print!\n");
    jump_point: // Attention! Un label n'est pas un statement!
    return; // Le return est donc nécéssaire ici.
}

struct a_struct {
    int a;
    int b;
    int c;
    int d;
};

union a_union {
    short s;
    double d;
};

struct in_struct {
    struct {
        struct {
            struct {
                int a;
            };
        } _;
    } _;
};

void structures_and_allocation() {
    // L'opérateur SIZEOF permet d'avoir la taille
    // d'un type
    struct a_struct a;
    // ^ Allocation STATIQUE: sur le STACK

    // STACK: allocation automatiques par le système, taille fixée selon
    //        le programme. Un appel de fonction ajoute des variables sur
    //        le stack, un retour les élimine.
    //
    // HEAP:  allocation manuelle par le programmeur, taille dynamique.
    //        Aucun nettoyage automatique
    //
    struct a_struct *b = (struct a_struct *) malloc(sizeof(struct a_struct)); // <---- Allocation DYNAMIQUE: sur le HEAP

    a.a = 5; // <--- Affectation directe: "comme en java"
    b->a = 5; // <--- Affectation d'un champ au travers un pointeur

    free(b); // Il est impératif de nettoyer la mémoire utilisée
    // le système ne le fait PAS pour nous.
    // Quant à 'a': alloué sur le stack,
    // quand la fonction retourne, a est éliminée.

    int *array = (int *) malloc(sizeof(int) * 10);
    array[0] = 1;
    array[1] = 2;
    *(array + 2) = 3; // Équivalent à array[2], permet de faire des "slices"
    //    array[1000000] = 4;
    // Attention! Ce code pourrait être valide! Mais c'est un accès illégal.

    // Une union
    union a_union u;
    printf("Taille d'un short: %d\n", (unsigned char) sizeof(short));
    flush();

    printf("Taille d'un double: %d\n", (unsigned char) sizeof(double));
    flush();

    printf("Taille de l'union: %d\n", (unsigned char) sizeof(union a_union));
    flush();

    u.s = 1;
    printf("Valeur de u.s = %d\n", (unsigned char) u.s);
    flush();

    printf("Valeur de u.d = %f\n", (double) u.d);
    flush();

    u.d = 5.6;
    printf("Valeur de u.s = %d\n", (unsigned char) u.s);
    flush();

    printf("Valeur de u.d = %f\n", (double) u.d);
    flush();

    // Leçon: le système vous fait confiance et ne sait pas ce que vous faites.
}

void other(int sz) {
    int arr[sz];
}

int main(int argc, char **argv) {

    if (argc <= 1) {
        printf("ERR\n");
        exit(EXIT_FAILURE);
    }

    int example = atoi(argv[1]); // NOLINT(cert-err34-c)

    for (int i = example; i <= 6; ++i)
        switch (i) {
            case 0 : {
                print_f_example();
                break;
            }
            case 1: {
                bits_example();
                break;
            }
            case 2: {
                pointers();
                break;
            }
            case 3: {
                types_in_c();
                break;
            }
            case 4: {
                control_structures_in_c();
                break;
            }
            case 5: {
                constant_definition_in_c();
                break;
            }
            case 6: {
                structures_and_allocation();
                break;
            }
            default:
                break;
        }

    return 0;
}    
