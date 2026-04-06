//nawresdhaouadi
//lina marnissi
//mariem hichri
//zahra douggui
//LIG 1 projet ASD 2

#include <stdio.h>
#include <string.h>

#define MAX 100

struct Client {
    int id;
    char nom[50];
};
struct Chambre {
    int numero;
    float prix;
    int disponible;
};

struct Reservation {
    int idClient;
    int numChambre;
    int nbNuits;
};
struct Client clients[MAX];
struct Chambre chambres[MAX];
struct Reservation reservations[MAX];

int nbClients = 0, nbChambres = 0, nbReservations = 0;

int clientExiste(int id) {
    int i;
    for(i=0;i<nbClients;i++)
        if(clients[i].id == id) return 1;
    return 0;
}

int chambreExiste(int num) {
    int i;
    for(i=0;i<nbChambres;i++)
        if(chambres[i].numero == num) return 1;
    return 0;
}

int verifierChambre(int num) {
    int i;
    for(i = 0; i < nbChambres; i++) {
        if(chambres[i].numero == num && chambres[i].disponible == 1)
            return i;
    }
    return -1;
}

// ===== CLIENT =====
void ajouterClient() {
    int id;
    printf("ID: ");
    scanf("%d", &id);
    getchar();

    if(clientExiste(id)) {
        printf("Client existe deja !\n");
        return;
    }

    clients[nbClients].id = id;
    printf("Nom: ");
    fgets(clients[nbClients].nom, 50, stdin);
    clients[nbClients].nom[strcspn(clients[nbClients].nom, "\n")] = 0;

    nbClients++;
    printf("Client ajoute !\n");
}

void afficherClients() {
    int i;
    if(nbClients==0){printf("Aucun client.\n"); return;}
    for(i = 0; i < nbClients; i++)
        printf("ID:%d | Nom:%s\n", clients[i].id, clients[i].nom);
}

void modifierClient() {
    int id, i;
    printf("ID du client a modifier: ");
    scanf("%d", &id);
    getchar();

    for(i = 0; i < nbClients; i++) {
        if(clients[i].id == id) {
            printf("Nouveau nom: ");
            fgets(clients[i].nom, 50, stdin);
            clients[i].nom[strcspn(clients[i].nom, "\n")] = 0;
            printf("Modifie !\n");
            return;
        }
    }
    printf("Client non trouve.\n");
}

void supprimerClient() {
    int id, i, j;
    printf("ID du client a supprimer: ");
    scanf("%d", &id);

    for(i = 0; i < nbClients; i++) {
        if(clients[i].id == id) {
            for(j = i; j < nbClients - 1; j++)
                clients[j] = clients[j + 1];
            nbClients--;
            printf("Supprime !\n");
            return;
        }
    }
    printf("Client non trouve.\n");
}

// ===== CHAMBRE =====
void ajouterChambre() {
    int num;
    printf("Numero: ");
    scanf("%d", &num);

    if(chambreExiste(num)) {
        printf("Chambre existe deja !\n");
        return;
    }

    chambres[nbChambres].numero = num;
    printf("Prix: ");
    scanf("%f", &chambres[nbChambres].prix);

    chambres[nbChambres].disponible = 1;
    nbChambres++;
    printf("Chambre ajoutee !\n");
}

void afficherChambres() {
    int i;
    if(nbChambres==0){printf("Aucune chambre.\n"); return;}
    for(i = 0; i < nbChambres; i++)
        printf("Num:%d | Prix:%.2f | %s\n",
               chambres[i].numero,
               chambres[i].prix,
               chambres[i].disponible ? "Libre" : "Occupee");
}

void modifierChambre() {
    int num, i;
    printf("Numero chambre a modifier: ");
    scanf("%d", &num);

    for(i = 0; i < nbChambres; i++) {
        if(chambres[i].numero == num) {
            printf("Nouveau prix: ");
            scanf("%f", &chambres[i].prix);
            printf("Modifie !\n");
            return;
        }
    }
    printf("Chambre non trouvee.\n");
}

void supprimerChambre() {
    int num, i, j;
    printf("Numero chambre a supprimer: ");
    scanf("%d", &num);

    for(i = 0; i < nbChambres; i++) {
        if(chambres[i].numero == num) {
            for(j = i; j < nbChambres - 1; j++)
                chambres[j] = chambres[j + 1];
            nbChambres--;
            printf("Supprimee !\n");
            return;
        }
    }
    printf("Chambre non trouvee.\n");
}

// ===== RESERVATION =====
void reserver() {
    int id, num, nbNuits, index;
    printf("ID client: ");
    scanf("%d", &id);
    if(!clientExiste(id)){printf("Client non trouve !\n"); return;}

    printf("Numero chambre: ");
    scanf("%d", &num);

    index = verifierChambre(num);
    if(index == -1){printf("Chambre non disponible !\n"); return;}

    printf("Nombre de nuits: ");
    scanf("%d", &nbNuits);
    if(nbNuits <=0){printf("Nombre de nuits invalide !\n"); return;}

    reservations[nbReservations].idClient = id;
    reservations[nbReservations].numChambre = num;
    reservations[nbReservations].nbNuits = nbNuits;
    nbReservations++;

    chambres[index].disponible = 0;
    printf("Reservation effectuee !\n");
}

// ===== FACTURATION =====
void facturation() {
    int id, i, j, found=0;
    float totalGeneral = 0;
    printf("ID client: ");
    scanf("%d", &id);

    if(!clientExiste(id)){printf("Client non trouve !\n"); return;}

    printf("\n--- FACTURE ---\nClient ID: %d\n", id);
    for(i = 0; i < nbReservations; i++) {
        if(reservations[i].idClient == id) {
            int num = reservations[i].numChambre;
            int nuits = reservations[i].nbNuits;

            for(j = 0; j < nbChambres; j++) {
                if(chambres[j].numero == num) {
                    float total = nuits * chambres[j].prix;
                    totalGeneral += total;
                    printf("Chambre %d | Nuits: %d | Total: %.2f DT\n", num, nuits, total);
                    chambres[j].disponible = 1; // libération
                    found = 1;
                }
            }
        }
    }

    if(!found) printf("Aucune reservation pour ce client.\n");
    else printf("TOTAL GENERAL: %.2f DT\n", totalGeneral);
}

// ===== MENU =====
int main() {
    int choix;
    do {
        printf("\n=== MENU HOTEL ===\n");
        printf("1. Ajouter Client\n");
        printf("2. Afficher Clients\n");
        printf("3. Modifier Client\n");
        printf("4. Supprimer Client\n");
        printf("5. Ajouter Chambre\n");
        printf("6. Afficher Chambres\n");
        printf("7. Modifier Chambre\n");
        printf("8. Supprimer Chambre\n");
        printf("9. Reservation\n");
        printf("10. Facturation\n");
        printf("0. Quitter\n");

        printf("Choix: ");
        scanf("%d", &choix);

        switch(choix) {
            case 1: ajouterClient(); break;
            case 2: afficherClients(); break;
            case 3: modifierClient(); break;
            case 4: supprimerClient(); break;
            case 5: ajouterChambre(); break;
            case 6: afficherChambres(); break;
            case 7: modifierChambre(); break;
            case 8: supprimerChambre(); break;
            case 9: reserver(); break;
            case 10: facturation(); break;
            case 0: printf("Au revoir !\n"); break;
            default: printf("Choix invalide !\n");
        }

    } while(choix != 0);

    return 0;
}
