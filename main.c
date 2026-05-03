//nawresdhaouadi
//lina marnissi
//mariem hichri
//zahra douggui
//LIG 1 projet ASD 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===== STRUCTURES =====
typedef struct Client {
    int id;
    char nom[50];
    struct Client* suiv;
} Client;

typedef struct Chambre {
    int num;
    float prix;
    int dispo;
    struct Chambre* suiv;
} Chambre;

typedef struct Reservation {
    int idC;
    int numCh;
    int nuits;
    struct Reservation* suiv;
} Reservation;

// ===== LISTES =====
Client* LC = NULL;
Chambre* LCH = NULL;
Reservation* LR = NULL;

// ===== CENTER TEXT =====
void centerText(char* text) {
    int width = 80;
    int len = strlen(text);
    int spaces = (width - len) / 2;
    int i;   // declaration kharej for

    for (i = 0; i < spaces; i++) {
        printf(" ");
    }
    printf("%s\n", text);
}

// ===== RECHERCHE =====
Client* chercherClient(int id) {
    Client* t = LC;
    while (t) {
        if (t->id == id) return t;
        t = t->suiv;
    }
    return NULL;
}

Chambre* chercherChambre(int num) {
    Chambre* t = LCH;
    while (t) {
        if (t->num == num) return t;
        t = t->suiv;
    }
    return NULL;
}

// ===== SAUVEGARDE =====
void sauvegarderClients() {
    FILE* f = fopen("clients.txt", "w");
    Client* t = LC;
    while (t) {
        fprintf(f, "%d;%s\n", t->id, t->nom);
        t = t->suiv;
    }
    fclose(f);
}

void sauvegarderChambres() {
    FILE* f = fopen("chambres.txt", "w");
    Chambre* t = LCH;
    while (t) {
        fprintf(f, "%d;%.2f;%d\n", t->num, t->prix, t->dispo);
        t = t->suiv;
    }
    fclose(f);
}

void sauvegarderReservations() {
    FILE* f = fopen("reservations.txt", "w");
    Reservation* t = LR;
    while (t) {
        fprintf(f, "%d;%d;%d\n", t->idC, t->numCh, t->nuits);
        t = t->suiv;
    }
    fclose(f);
}

// ===== CHARGEMENT =====
void chargerClients() {
    FILE* f = fopen("clients.txt", "r");
    if (!f) return;
    Client* n;
    while (1) {
        n = malloc(sizeof(Client));
        if (fscanf(f, "%d;%49[^\n]\n", &n->id, n->nom) != 2) {
            free(n);
            break;
        }
        n->suiv = LC;
        LC = n;
    }
    fclose(f);
}

void chargerChambres() {
    FILE* f = fopen("chambres.txt", "r");
    if (!f) return;
    Chambre* n;
    while (1) {
        n = malloc(sizeof(Chambre));
        if (fscanf(f, "%d;%f;%d\n", &n->num, &n->prix, &n->dispo) != 3) {
            free(n);
            break;
        }
        n->suiv = LCH;
        LCH = n;
    }
    fclose(f);
}

void chargerReservations() {
    FILE* f = fopen("reservations.txt", "r");
    if (!f) return;
    Reservation* n;
    while (1) {
        n = malloc(sizeof(Reservation));
        if (fscanf(f, "%d;%d;%d\n", &n->idC, &n->numCh, &n->nuits) != 3) {
            free(n);
            break;
        }
        n->suiv = LR;
        LR = n;
    }
    fclose(f);
}

// ===== CLIENT =====
void ajouterClient() {
    Client* n = malloc(sizeof(Client));
    printf("ID: "); scanf("%d", &n->id); getchar();

    if (chercherClient(n->id)) {
        printf("Existe deja\n"); free(n); return;
    }

    printf("Nom: ");
    fgets(n->nom, 50, stdin);
    n->nom[strcspn(n->nom, "\n")] = 0;

    n->suiv = LC;
    LC = n;
    sauvegarderClients();
}

void afficherClients() {
    Client* t = LC;
    while (t) {
        printf("%d - %s\n", t->id, t->nom);
        t = t->suiv;
    }
}

void supprimerClient() {
    int id;
    printf("ID: "); scanf("%d", &id);

    Client *t = LC, *p = NULL;
    while (t && t->id != id) { p = t; t = t->suiv; }

    if (!t) { printf("Introuvable\n"); return; }

    if (p) p->suiv = t->suiv;
    else LC = t->suiv;

    free(t);
    sauvegarderClients();
}

void modifierClient() {
    int id;
    printf("ID: "); scanf("%d", &id); getchar();

    Client* t = chercherClient(id);
    if (!t) { printf("Introuvable\n"); return; }

    printf("Nouveau nom: ");
    fgets(t->nom, 50, stdin);
    t->nom[strcspn(t->nom, "\n")] = 0;

    sauvegarderClients();
}

// ===== CHAMBRE =====
void ajouterChambre() {
    Chambre* n = malloc(sizeof(Chambre));
    printf("Numero: "); scanf("%d", &n->num);

    if (chercherChambre(n->num)) {
        printf("Existe deja\n"); free(n); return;
    }

    printf("Prix: "); scanf("%f", &n->prix);
    n->dispo = 1;

    n->suiv = LCH;
    LCH = n;
    sauvegarderChambres();
}

void afficherChambres() {
    Chambre* t = LCH;
    while (t) {
        printf("%d | %.2f | %s\n", t->num, t->prix, t->dispo ? "Libre" : "Occupee");
        t = t->suiv;
    }
}

void supprimerChambre() {
    int num;
    printf("Numero: "); scanf("%d", &num);

    Chambre *t = LCH, *p = NULL;
    while (t && t->num != num) { p = t; t = t->suiv; }

    if (!t) { printf("Introuvable\n"); return; }

    if (p) p->suiv = t->suiv;
    else LCH = t->suiv;

    free(t);
    sauvegarderChambres();
}

void modifierChambre() {
    int num;
    printf("Numero: "); scanf("%d", &num);

    Chambre* ch = chercherChambre(num);
    if (!ch) { printf("Introuvable\n"); return; }

    printf("Prix: "); scanf("%f", &ch->prix);
    printf("Dispo (1/0): "); scanf("%d", &ch->dispo);

    sauvegarderChambres();
}

// ===== RESERVATION =====
void reserver() {
    int id, num, nuits;

    printf("ID client: "); scanf("%d", &id);
    if (!chercherClient(id)) { printf("Client inexistant\n"); return; }

    printf("Chambre: "); scanf("%d", &num);
    Chambre* ch = chercherChambre(num);

    if (!ch || !ch->dispo) {
        printf("Non disponible\n");
        return;
    }

    printf("Nuits: "); scanf("%d", &nuits);

    Reservation* r = malloc(sizeof(Reservation));
    r->idC = id;
    r->numCh = num;
    r->nuits = nuits;

    r->suiv = LR;
    LR = r;

    ch->dispo = 0;

    sauvegarderReservations();
    sauvegarderChambres();
}

void afficherReservations() {
    Reservation* r = LR;
    while (r) {
        printf("Client %d -> Chambre %d (%d nuits)\n", r->idC, r->numCh, r->nuits);
        r = r->suiv;
    }
}

void supprimerReservation() {
    int id, num;
    printf("ID client: "); scanf("%d", &id);
    printf("Chambre: "); scanf("%d", &num);

    Reservation *r = LR, *p = NULL;

    while (r && !(r->idC == id && r->numCh == num)) {
        p = r;
        r = r->suiv;
    }

    if (!r) { printf("Introuvable\n"); return; }

    Chambre* ch = chercherChambre(num);
    if (ch) ch->dispo = 1;

    if (p) p->suiv = r->suiv;
    else LR = r->suiv;

    free(r);
    sauvegarderReservations();
    sauvegarderChambres();
}

// ===== FACTURE =====
void facture() {
    int id;
    float total = 0;

    printf("ID client: "); scanf("%d", &id);

    Reservation* r = LR;
    while (r) {
        if (r->idC == id) {
            Chambre* ch = chercherChambre(r->numCh);
            if (ch) {
                float t = ch->prix * r->nuits;
                total += t;
                printf("Chambre %d : %.2f\n", ch->num, t);
            }
        }
        r = r->suiv;
    }

    printf("TOTAL = %.2f\n", total);
}

// ===== MENUS =====
void menuPrincipal() {
    printf("\n");
    centerText("===== MENU PRINCIPAL =====");
    centerText("1. Client");
    centerText("2. Chambre");
    centerText("3. Reservation");
    centerText("4. Facture");
    centerText("0. Quitter");
}

// sous-menus normal
void menuClient() {
    printf("\n--- CLIENT ---\n");
    printf("1. Ajouter\n2. Afficher\n3. Supprimer\n4. Modifier\n0. Retour\n");
}

void menuChambre() {
    printf("\n--- CHAMBRE ---\n");
    printf("1. Ajouter\n2. Afficher\n3. Supprimer\n4. Modifier\n0. Retour\n");
}

void menuReservation() {
    printf("\n--- RESERVATION ---\n");
    printf("1. Reserver\n2. Afficher\n3. Supprimer\n0. Retour\n");
}

// ===== MAIN =====
int main() {
    int choix, sous;

    chargerClients();
    chargerChambres();
    chargerReservations();

    do {
        menuPrincipal();
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {
        case 1:
            do {
                menuClient();
                scanf("%d", &sous);
                if (sous == 1) ajouterClient();
                else if (sous == 2) afficherClients();
                else if (sous == 3) supprimerClient();
                else if (sous == 4) modifierClient();
            } while (sous != 0);
            break;

        case 2:
            do {
                menuChambre();
                scanf("%d", &sous);
                if (sous == 1) ajouterChambre();
                else if (sous == 2) afficherChambres();
                else if (sous == 3) supprimerChambre();
                else if (sous == 4) modifierChambre();
            } while (sous != 0);
            break;

        case 3:
            do {
                menuReservation();
                scanf("%d", &sous);
                if (sous == 1) reserver();
                else if (sous == 2) afficherReservations();
                else if (sous == 3) supprimerReservation();
            } while (sous != 0);
            break;

        case 4:
            facture();
            break;
        }

    } while (choix != 0);

    return 0;
}
