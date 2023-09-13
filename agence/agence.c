#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LONGUEUR_NOM_UTILISATEUR 50
#define MAX_LONGUEUR_MOT_DE_PASSE 50

int authentifier()
{
    char nom_utilisateur[MAX_LONGUEUR_NOM_UTILISATEUR];
    char mot_de_passe[MAX_LONGUEUR_MOT_DE_PASSE];
    int tentatives_restantes = 3;

    while (tentatives_restantes > 0)
    {
        printf("+----------------------------------+\n");
        printf("|             Authentification     |\n");
        printf("+----------------------------------+\n");
        printf("|                                  |\n");
        printf("| Entrez votre nom d'utilisateur : |\n");
        printf("|                                  |\n");
        printf("+----------------------------------+\n");
        printf("> ");
        scanf("%s", nom_utilisateur);
        printf("\n");

        printf("+----------------------------------+\n");
        printf("|             Authentification     |\n");
        printf("+----------------------------------+\n");
        printf("|                                  |\n");
        printf("| Entrez votre mot de passe :      |\n");
        printf("|                                  |\n");
        printf("+----------------------------------+\n");
        printf("> ");
        scanf("%s", mot_de_passe);
        printf("\n");

        if (strcmp(nom_utilisateur, "jmlery") == 0 && strcmp(mot_de_passe, "beigneur") == 0)
        {
            return 1;
        }
        else
        {
            tentatives_restantes--;
            printf("+----------------------------------+\n");
            printf("|         Authentification         |\n");
            printf("+----------------------------------+\n");
            printf("|                                  |\n");
            printf("| Nom d'utilisateur ou mot de     |\n");
            printf("| passe incorrect                  |\n");
            printf("| Tentatives restantes : %d         |\n", tentatives_restantes);
            printf("|                                  |\n");
            printf("+----------------------------------+\n");
            printf("\n");
        }
    }

    printf("+----------------------------------+\n");
    printf("|         Authentification         |\n");
    printf("+----------------------------------+\n");
    printf("|                                  |\n");
    printf("| Vous avez atteint le nombre      |\n");
    printf("| maximum de tentatives.           |\n");
    printf("|                                  |\n");
    printf("+----------------------------------+\n");
    printf("\n");

    return 0;
}

typedef struct Date
{
    int jour;
    int mois;
    int annee;
} Date;

void afficherDate(Date date);
int estBissextile(int annee);
int joursDansMois(int mois, int annee);
int estDateValide(Date date);
Date saisirDate();
int nombreJours(int jour, int mois, int annee);
Date dateDAujourdhui();
int differenceJours(struct Date date1, struct Date date2);

typedef struct Voiture
{
    int id;
    int disponibilite;
    int typeDeTransmission;
    char categorie;
    int climatisation;
    float kilometrage;
    int nbPortes;
    int nbPassagersMax;
    int nbCarteCreditExigee;
    int airBagConducteur;
    int airBagPassager;
    int abs;
    int fermetureCentralise;
    int directionAssiste;
    int radio;
    float tarifJournalierEnEuro;
    char marque[100];
    char modelele[100];
    char immatriculation[9];


} Voiture;
typedef struct Parc
{

    int nbVoituresMax;
    Voiture voitures[999];
    int nbVoitures;


} Parc;

int chercherVehicule(Parc p, int idVoiture);
int ajouterNouveauVehicule(Parc * p);
int changeeDisponibiliteVehicule(Parc * p,int idVoiture);
void afficherListeVehicule(Parc p);
int modifierVehicule(Parc * p,int idVoiture);

void conv_min_maj(char * chaine);
Voiture saisirVoiture(Parc p,int id);

void afficherVoiture(Voiture v);
Voiture modifierVoiture(Parc p,Voiture v);
int chercherVehiculeParImmatricule(Parc p, char * immatriculation);

typedef struct Reservation
{
    int id;
    int idClient;
    int idVehicule;
    Date effectueLe;
    int nbJours;
    int nbPassagers;
    int typeAssurance;
    float tarifAssurance;
    float coutTotale;
    int annullee;

} Reservation;

Reservation saisirReservation(int id,int idVehicule,int idClient,int capacitePassagerMax,int tarifJournalierVoiture);
void afficherReservaton(Reservation r);
Reservation modifierReservation(Reservation r,int capacitePassagerMax,int tarifJournalierVoiture);



typedef struct Client
{

    int id;
    char nom[55];
    char prenom[55];
    Date dateDeNaissance;
    Date dateObtentionDuPermis;
    char numTel[11];
    char email[100];
} Client;


Client saisirClient(int id);
void afficherClient(Client c);
Client modifierClient(Client c);



typedef struct Agence
{
    char nom[55];
    Client clients[999];
    Parc parc;
    Reservation reservations[999];
    int nbClients;
    int nbResevations;


} Agence;

int menu_principal();
void procedure_principale();
int menu_gestion_clients();
void procedure_gestion_clients(Agence * a);
int menu_gestion_parc();
void procedure_gestion_parc(Agence * a);
int menu_gestion_reservations();
void procedure_gestion_reservation(Agence * a);
int chercherClient(Agence * a, int idClient);
int chercherReservation(Agence * a, int idReservation);
int ajouterNouveauClient(Agence * a,int ageMin,int ageMax);
void afficherListeClient(Agence a);
int modifierUnClient(Agence *  a,int idClient,int ageMin,int ageMax);
void ajouterNouvelleReservation(Agence * a,int idVehicule,int idClient,int capacitePassagerMax,int tarifJournalierVoiture);
void afficherListeReservation(Agence a);
int modifierUneReservation(Agence * a,int idReservation);
void enregistrerAgenceDansSauvegarde(Agence agence);
Agence recupererAgenceApartirDuFichier(char * nomAgence,int nbVoituresMax);
void quitter(Agence * a);




void afficherDate(Date date)
{
    printf("%02d/%02d/%04d", date.jour, date.mois, date.annee);
}

int estBissextile(int annee)
{
    return ((annee % 4 == 0) && (annee % 100 != 0)) || (annee % 400 == 0);
}

int nombreJours(int jour, int mois, int annee)
{
    int joursMois[12] = {31, estBissextile(annee) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int nbJours = jour;
    for (int i = 0; i < mois - 1; i++)
    {
        nbJours += joursMois[i];
    }
    return nbJours;
}

int joursDansMois(int mois, int annee)
{
    int nbJours = 31;
    switch(mois)
    {
    case 2:
        nbJours = estBissextile(annee) ? 29 : 28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        nbJours = 30;
        break;
    }
    return nbJours;
}

int estDateValide(Date date)
{
    int estValide = 1;
    if (date.mois < 1 || date.mois > 12)
    {
        estValide = 0;
    }
    else if (date.jour < 1 || date.jour > joursDansMois(date.mois, date.annee))
    {
        estValide = 0;
    }
    return estValide;
}

// Cherche une sous-chaîne dans une chaîne en ignorant la casse
int chaineExisteDansChaine(const char* chaine, const char* recherche)
{
    const char* p = chaine;
    const char* q = recherche;

    while (*p)
    {
        if (toupper(*p) == toupper(*q))
        {
            // Si nous avons trouvé une correspondance, vérifiez le reste de la chaîne de recherche
            const char* r = p + 1;
            const char* s = q + 1;
            while (*s && toupper(*r) == toupper(*s))
            {
                r++;
                s++;
            }
            if (!*s)
            {
                // Si la chaîne de recherche est vide, nous avons trouvé une correspondance
                return 1;
            }
        }
        p++;
    }
    return 0;
}

Date saisirDate()
{
    Date date;
    do
    {
        printf("\nEntrez la date (jj/mm/aaaa) : ");
        scanf("%d/%d/%d", &date.jour, &date.mois, &date.annee);
    }
    while (!estDateValide(date));
    return date;
}

Date dateDAujourdhui()
{


    time_t now;
    struct tm *local_time;
    char date_string[11]; // 10 characters for the date + 1 null character

    time(&now); // Get the current time
    local_time = localtime(&now); // Convert to local time

    strftime(date_string, sizeof(date_string), "%d/%m/%Y", local_time);

    Date dateAujourdhui;

    int n;

    do
    {

        n = sscanf(date_string, "%d/%d/%d", &dateAujourdhui.jour, &dateAujourdhui.mois, &dateAujourdhui.annee);


    }
    while (n != 3);

    return dateAujourdhui;

}

int differenceJours(Date date1,Date date2)
{
    int nbJours1 = nombreJours(date1.jour, date1.mois, date1.annee);
    int nbJours2 = nombreJours(date2.jour, date2.mois, date2.annee);
    return nbJours2 - nbJours1;
}

int differenceEnAnnees(Date date1, Date date2)
{
    int diffAnnees = date2.annee - date1.annee;
    if (date2.mois < date1.mois || (date2.mois == date1.mois && date2.jour < date1.jour))
    {
        diffAnnees--;
    }
    return diffAnnees;
}

void conv_min_maj(char * chaine)
{
    int taille, i ;
    taille =strlen(chaine);
    for (i = 0 ; i < taille ; i++)
    {
        chaine[i] = toupper(chaine[i]);
    }
}

Voiture saisirVoiture(Parc p,int id)
{
    Voiture v;
    v.id = id;
    v.typeDeTransmission = -1 ;
    do
    {
        printf("\nType de transmission ( 1 : Manuelle / 2 : Automatique )? ");
        scanf("%d",&v.typeDeTransmission);
    }
    while ( v.typeDeTransmission != 1 && v.typeDeTransmission != 2);

    do
    {
        printf("\nCategegorie ( Lettre de A a Z )? ");
        v.categorie = getchar();
        v.categorie = getchar();
        v.categorie = toupper(v.categorie);
    }
    while( v.categorie < 'A' || v.categorie > 'Z');

    v.climatisation = -1 ;

    do
    {
        printf("\nVoiture climatise ( 1 : Oui / 0 : Non )? ");
        scanf("%d",&v.climatisation);
    }
    while ( (v.climatisation != 0) && (v.climatisation != 1) );


    v.nbPortes = -1 ;
    do
    {
        printf("\nNombre de porte (3 ou 5)? ");
        scanf("%d",&v.nbPortes);
    }
    while ( v.nbPortes != 3 && v.nbPortes != 5);


    v.nbPassagersMax = -1 ;
    do
    {
        printf("\nNombre maximale de passagers ( entre 2 et 9 )? ");
        scanf("%d",&v.nbPassagersMax);
    }
    while ( v.nbPassagersMax  < 2 ||  v.nbPassagersMax > 9 );


    v.nbCarteCreditExigee = -1 ;
    do
    {
        printf("\nNombre de carte de credit Exigeees ( >= 1 )? ");
        scanf("%d",&v.nbCarteCreditExigee);
    }
    while ( v.nbCarteCreditExigee  < 1 );



    v.airBagConducteur = -1 ;
    do
    {
        printf("\nAirBag Conducteur ( 1 : Oui / 0 : Non )? ");
        scanf("%d",&v.airBagConducteur);
    }
    while ( v.airBagConducteur != 0 && v.airBagConducteur != 1);



    v.airBagPassager = -1 ;
    do
    {
        printf("\nAirBag Passager ( 1 : Oui / 0 : Non )? ");
        scanf("%d",&v.airBagPassager);
    }
    while ( v.airBagPassager != 0 && v.airBagPassager != 1);


    v.abs = -1 ;
    do
    {
        printf("\nSysteme ABS ( 1 : Oui / 0 : Non )? ");
        scanf("%d",&v.abs);
    }
    while ( v.abs != 0 && v.abs != 1);


    v.fermetureCentralise = -1 ;
    do
    {
        printf("\nfermeture centralise ( 1 : Oui / 0 : Non )? ");
        scanf("%d",&v.fermetureCentralise);
    }
    while ( v.fermetureCentralise != 0 && v.fermetureCentralise != 1);



    v.directionAssiste = -1 ;
    do
    {
        printf("\nDirection Assiste ( 1 : Oui / 0 : Non )? ");
        scanf("%d",&v.directionAssiste);
    }
    while ( v.directionAssiste != 0 && v.directionAssiste != 1);

    v.kilometrage = -1 ;
    do
    {
        printf("\nKilometrage ( > 0 )? ");
        scanf("%f",&v.kilometrage);
    }
    while ( v.kilometrage < 0 );


    v.radio = -1 ;
    do
    {
        printf("\nRadio Disponible ( 1 : Oui / 0 : Non )? ");
        scanf("%d",&v.radio);
    }
    while ( v.radio != 0 && v.radio != 1);


    v.tarifJournalierEnEuro = -1 ;
    do
    {
        printf("\nTarif journalier en EURO ( entre 40.00 EURO et 70.00 EURO )? ");
        scanf("%f",&v.tarifJournalierEnEuro);
    }
    while ( v.tarifJournalierEnEuro < 40 || v.tarifJournalierEnEuro > 70);

    printf("\nMarque ( Ex FORD, Renault ... )? ");

    scanf("%s",v.marque);

    if (strlen(v.marque)==0)
    {
        do
        {
            printf("\n\nVeuillez Verifier votre saisie\n\nVeuillez Reessayer\n\n");
            printf("\nMarque ( Ex FORD, Renault ... )? ");

            scanf("%s",v.marque);


        }
        while(strlen(v.marque) == 0);
    }
    conv_min_maj(v.marque);


    printf("\nModele ( Ex Focus SW, Clio ... )? ");

    scanf("%s",v.modelele);

    if (strlen(v.modelele)==0)
    {
        do
        {
            printf("\n\nVeuillez Verifier votre saisie\n\nVeuillez Reessayer\n\n");
            printf("\nModele ( Ex Focus SW, Clio ... )? ");

            scanf("%s",v.modelele);


        }
        while(strlen(v.modelele) == 0);
    }
    conv_min_maj(v.modelele);

    do
    {
        printf("\nImmatriculation ( 2 Lettres suivies par 3 Chiffres et 2 Lettres - Exemple : AB123AB )? ");

        scanf("%s",v.immatriculation);

        conv_min_maj(v.immatriculation);
        if(chercherVehiculeParImmatricule(p,v.immatriculation) != -1)
        {
            printf("\n [ Erreur ] Immatriculation deja attribue a un autre vehicule\n");
        }
    }
    while ( strlen(v.immatriculation) != 7 || (v.immatriculation[0] > 'Z' ||
            v.immatriculation[0] < 'A')  ||
            (v.immatriculation[1] > 'Z' || v.immatriculation[1] < 'A')  ||
            (v.immatriculation[2] > '9' || v.immatriculation[2] < '0')  ||
            (v.immatriculation[3] > '9' || v.immatriculation[3] < '0')  ||
            (v.immatriculation[4] > '9' || v.immatriculation[4] < '0')  ||
            (v.immatriculation[5] > 'Z' || v.immatriculation[5] < 'A')  ||
            (v.immatriculation[6] > 'Z' || v.immatriculation[6] < 'A') || chercherVehiculeParImmatricule(p,v.immatriculation) != -1 );




    v.disponibilite = -1 ;

    do
    {
        printf("\nVoiture Disponible ( 1 : Oui / 0 : Non )? ");
        scanf("%d",&v.disponibilite);
    }
    while ( v.disponibilite != 0 && v.disponibilite != 1);

    return v;
}

void afficherVoiture(Voiture v)
{

    printf("\nID : %d", v.id);

    printf("\nCategorie : %c", v.categorie);
    if(v.typeDeTransmission == 1)
    {
        printf("\nType de transmission : Manuelle");
    }
    else
    {
        printf("\nType de transmission : Automatique");
    }
    if (v.climatisation == 1 )
    {
        printf("\nClimatisation : Disponible");
    }
    else
    {
        printf("\nClimatisation : Non Disponible");

    }
    printf("\nKilometrage : %.2f", v.kilometrage);
    printf("\nNombre de portes : %d", v.nbPortes);
    printf("\nNombre de passagers maximum : %d", v.nbPassagersMax);
    printf("\nNombre de cartes de credit Exigee : %d", v.nbCarteCreditExigee);
    if (v.airBagConducteur == 1 )
    {
        printf("\nAirbag conducteur : Disponible");
    }
    else
    {
        printf("\nAirbag conducteur : Non Disponible");

    }
    if (v.airBagPassager == 1 )
    {
        printf("\nAirbag passager : Disponible");
    }
    else
    {
        printf("\nAirbag passager : Non Disponible");

    }
    if (v.abs == 1 )
    {
        printf("\nABS : Disponible");
    }
    else
    {
        printf("\nABS : Non Disponible");

    }
    if (v.fermetureCentralise == 1 )
    {
        printf("\nFermeture centralisee : Disponible");
    }
    else
    {
        printf("\nFermeture centralisee : Non Disponible");

    }

    if (v.directionAssiste == 1 )
    {
        printf("\nDirection assistee : Disponible");
    }
    else
    {
        printf("\nDirection assistee : Non Disponible");

    }

    if (v.radio == 1 )
    {
        printf("\nRadio : Disponible");
    }
    else
    {
        printf("\nRadio : Non Disponible");

    }


    printf("\nTarif journalier en euro : %.2f", v.tarifJournalierEnEuro);
    printf("\nMarque : %s", v.marque);
    printf("\nModele : %s", v.modelele);
    printf("\nImmatriculation : %s", v.immatriculation);
    if(v.disponibilite == 1)
    {

        printf("\n\nVOITURE [ DISPONIBLE ]\n\n");

    }
    else
    {
        printf("\n\nVOITURE [ NON-DISPONIBLE ]\n\n");
    }

}


Voiture modifierVoiture(Parc p,Voiture v)
{
    printf("\nInformations actuelles de la voiture %04d",v.id);
    afficherVoiture(v);
    printf("\n\nVeuillez introduire les nouvelles informations\n");
    Voiture nvVoiture = saisirVoiture(p,v.id);
    return nvVoiture ;
}



Reservation saisirReservation(int id,int idVehicule,int idClient,int capacitePassagerMax,int tarifJournalierVoiture)
{
    Reservation r;
    r.id = id;
    r.idClient = idClient;
    r.idVehicule = idVehicule;
    printf("\nDate d'effet? ");
    do
    {
        r.effectueLe = saisirDate();
    }
    while(differenceJours(r.effectueLe,dateDAujourdhui()) > 0);
    afficherDate(r.effectueLe);
    do
    {
        printf("\nNombre de jours de location  ( > 1 ) : ");
        scanf("%d", &r.nbJours);
    }
    while(r.nbJours < 1);
    do
    {
        printf("\nNombre de passagers ( cette vehicule supporte %d passagers maximum ) : ",capacitePassagerMax);
        scanf("%d", &r.nbPassagers);
    }
    while ( r.nbPassagers < 1 || r.nbPassagers > capacitePassagerMax );
    do
    {
        printf("\nType d'assurance (1 pour basique, 2 pour avancee, 3 pour premium) : ");
        scanf("%d", &r.typeAssurance);
    }
    while ( r.typeAssurance != 1 && r.typeAssurance != 2 && r.typeAssurance != 3 );

    switch (r.typeAssurance)
    {
    case 1:
        r.tarifAssurance = (0.05 * tarifJournalierVoiture);
        break;
    case 2:
        r.tarifAssurance = (0.10 * tarifJournalierVoiture);
        break;
    case 3:
        r.tarifAssurance = (0.20 * tarifJournalierVoiture);
        break;

    }
    r.coutTotale = r.nbJours * ( r.tarifAssurance + tarifJournalierVoiture ) ;
    return r;
}


void afficherReservation(Reservation r)
{
    printf("\n\nReservation %04d", r.id);
    printf("\nID Client : %d", r.idClient);
    printf("\nID Vehicule : %d", r.idVehicule);
    printf("\nDate d'effectuation : ");
    afficherDate(r.effectueLe);
    printf("\nNombre de jours de location : %d", r.nbJours);
    printf("\nNombre de passagers : %d", r.nbPassagers);
    printf("\nType d'assurance : %d", r.typeAssurance);
    printf("\nTarif de l'assurance : %.2f", r.tarifAssurance);
    printf("\nCout total : %.2f", r.coutTotale);
    if ( r.annullee == 0 )
    {
        printf("\n\nReservation [ Confirmee ]\n\n");
    }
    else
    {
        printf("\n\nReservation [ Annullee ]\n\n");
    }
}

Reservation modifierReservation(Reservation r,int capacitePassagerMax,int tarifJournalierVoiture)
{
    printf("\nInformations actuelles de la reservation %04d",r.id);
    afficherReservation(r);
    printf("\n\nVeuillez introduire les nouvelles informations\n");
    Reservation nvReservation = saisirReservation(r.id,r.idClient,r.idVehicule,capacitePassagerMax,tarifJournalierVoiture);
    nvReservation.annullee = r.annullee;
    return nvReservation ;
}

// chercher un véhicule dans un parc donné en utilisant son identifiant idVoiture
int chercherVehicule(Parc p, int idVoiture)
{
    int i = 0;

    for (i = 0 ; i < p.nbVoitures ; i ++)
    {
        if (p.voitures[i].id == idVoiture)
        {
            return i;
        }
    }
    return -1;
}


int chercherVehiculeParImmatricule(Parc p, char * immatriculation)//cette fonction recherche l'indice de la voiture ayant l'immatriculation donnée dans le parc
{
    int i = 0;

    for (i = 0 ; i < p.nbVoitures ; i ++)
    {
        if (chaineExisteDansChaine(p.voitures[i].immatriculation,immatriculation))
        {
            return i;
        }
    }
    return -1;
}


int ajouterNouveauVehicule(Parc * p)// Vérifier si le nombre de voitures dans le parc n'a pas atteint la limite maximale
{
    if ( (*p).nbVoitures <= (*p).nbVoituresMax )
    {
        Voiture v = saisirVoiture((*p),(*p).nbVoitures +1 );
        (*p).voitures[(*p).nbVoitures] = v;
        (*p).nbVoitures++;
        return 1;
    }
    else
    {

        printf("\n\n[ ERREUR ] Saisie non valide : Capacite Maximale du parc atteinte\n\n");

    }
    return 0;

}
//changer la disponibilité d'un véhicule dans le parc en utilisant son identifiant (idVoiture)
int changeeDisponibiliteVehicule(Parc * p,int idVoiture)
{

    int indiceVoiture = chercherVehicule(*p,idVoiture);
    if(indiceVoiture >= 0)
    {
        int disponibiliteAcutelle = (*p).voitures[indiceVoiture].disponibilite;
        int nvDisponibilite = 1 - disponibiliteAcutelle; // Alterne entre 0 et 1 ( si 1 devient 0 et l'inverse si 0 devient 1 )
        (*p).voitures[indiceVoiture].disponibilite = nvDisponibilite;


        return nvDisponibilite;

    }
    return -1 ;// id voiture introuvable

}
//Afficher la liste des vehicules du parc
void afficherListeVehicule(Parc p)
{
    int i = 0;
    printf("\n\nPARC VEHICULE\n");
    printf("\nNombre de vehicules : %04d",p.nbVoitures);
    printf("\nCapacite Maximale : %04d",p.nbVoituresMax);
    printf("\n\nListe Vehicules : \n");

    for (i = 0 ; i < p.nbVoitures ; i++)
    {

        printf("\n------------------------------------------------\n");
        afficherVoiture(p.voitures[i]);

    }

}

int modifierVehicule(Parc * p,int idVoiture)
{
    int indiceVoiture = chercherVehicule(*p,idVoiture);
    if(indiceVoiture >= 0)//voiture trouvee
    {
        (*p).voitures[indiceVoiture] = modifierVoiture((*p),(*p).voitures[indiceVoiture]);
        return 1;//modification reussie
    }
    else
    {
        printf("\n\n[ ERREUR ] Saisie non valide : ID Vehicule inexistant\n\n");

    }
    return 0;
}

Client saisirClient(int id)
{
    Client c;
    c.id = id;
    printf("\nDonnez le nom du nouveau client : ");
    scanf("%s",c.nom);
	
	
	//verifier que les champs nom et prenom ne sont pas vides

    if (strlen(c.nom)==0)
    {
        do
        {
            printf("\n\nVeuillez Verifier votre saisie\n\nVeuillez Reessayer\n\n");
            printf("\nDonnez le nom du nouveau client : ");

            scanf("%s",c.nom);


        }
        while(strlen(c.nom) == 0);
    }
    printf("\nDonnez le prenom du nouveau client : ");

    scanf("%s",c.prenom);


    if (strlen(c.prenom)==0)
    {
        do
        {
            printf("\n\nVeuillez Verifier votre saisie\n\nVeuillez Reessayer\n\n");
            printf("\nDonnez le prenom du nouveau client : ");

            scanf("%s",c.prenom);


        }
        while(strlen(c.prenom) == 0);
    }
    printf("\nDate de naissance?");
    c.dateDeNaissance = saisirDate();
    printf("\nDate d'obtention du permis de conduire? ");
    c.dateObtentionDuPermis = saisirDate();
    printf("\nEntrez le numero de telephone (commencant par 0, avec la deuxieme lettre etant 7, 6 ou 1) : ");
    while (1)
    {

        scanf("%s",c.numTel);
        if (strlen(c.numTel) > 0 && c.numTel[strlen(c.numTel) - 1] == '\n')
        {
            c.numTel[strlen(c.numTel) - 1] = '\0';  // Replace newline with null character
        }
		//verifier que le numero est composer de 10 chiffres
        if ( strlen(c.numTel) != 10 )
        {
            printf("Le numero de telephone doit etre compose de 10 chiffres\nVeuillez reessayer: ");
        }
        else if (c.numTel[0] != '0' || (c.numTel[1] != '7' && c.numTel[1] != '6' && c.numTel[1] != '1')) //verifier que le numero commence par 0 et suivi par 6 ou 1 ou 7
        {
            printf("Le numero de telephone doit commencer par 0 et le deuxieme c doit etre 7, 6 ou 1.\nVeuillez reessayer: ");
        }
        else
        {
            break;
        }
    }

    printf("\nEntrez l'adresse email (doit se terminer par .com ou .fr et contenir @): ");
    while (1)
    {

        scanf("%s",c.email);
        if (strlen(c.email) > 0 && c.email[strlen(c.email) - 1] == '\n')
        {
            c.email[strlen(c.email) - 1] = '\0';  // Replace newline with null character
        }
        int i = 0;
        while (c.email[i] != '\0')
        {
            if (c.email[i] == '@')
            {
                if (strstr(c.email+i, ".com") != NULL || strstr(c.email+i, ".fr") != NULL)
                {
                    break;
                }
            }
            i++;
        }
        if (c.email[i] == '\0')
        {
            printf("L'adresse email doit se terminer par .com ou .fr et contenir @.\nVeuillez reessayer: ");
        }
        else
        {
            break;
        }
    }
    return c;
}

void afficherClient(Client c)
{

    printf("\nID : %04d\nNom : %s\nPrenom : %s\nTel : %s\nEmail : %s\nDate de naissance : ",c.id,c.nom,c.prenom,c.numTel,c.email);
    afficherDate(c.dateDeNaissance);
    printf("\nDate d'obtention du permis : ");
    afficherDate(c.dateObtentionDuPermis);

}


Client modifierClient(Client c)
{
    printf("\nInformations actuelles du client N-%04d",c.id);
    afficherClient(c);
    printf("\n\nVeuillez introduire les nouvelles informations\n");
    Client nvClient = saisirClient(c.id);
    return nvClient ;
}

int chercherClient(Agence * a, int idClient)
{

    int i = 0;

    for (i = 0 ; i < (*a).nbClients ; i ++)
    {
        if ( ((*a).clients[i].id) == idClient)
        {
            return i;
        }
    }
    return -1;
}


int menu_principal()
{
    int choix = -1;
    do
    {
        printf("\n------------------------------------------------\n");
        printf("\n-------------- MENU PRINCIPAL ------------------\n");
        printf("\n------------------------------------------------\n");
        printf("-1- Gerer les reservations\n");
        printf("-2- Gerer les clients\n");
        printf("-3- Gerer le parc automobile\n");
        printf("-0- Enregistrer et Quitter\n");
        printf("Choix : ");
        scanf("%d",&choix);
    }
    while (choix<0 || choix >3);
    return choix;

}

void procedure_principale(Agence * a)
{

    int choix=-1;
    do
    {
        choix = menu_principal();
        switch(choix)
        {
        case 1 :
            procedure_gestion_reservation(a);
            break;
        case 2 :
            procedure_gestion_clients(a);
            break;
        case 3 :
            procedure_gestion_parc(a);
            break;
        case 0 :
            quitter(a);
            break;
        }
    }
    while (choix != 0);
}

int menu_gestion_clients()
{

    int choix = -1 ;
    do
    {
        printf("\n------------------------------------------------\n");
        printf("\n----------- MENU GESTION CLIENTS ----------------\n");
        printf("\n------------------------------------------------\n");
        printf("-1- Consulter la liste des clients\n");
        printf("-2- Ajouter un nouveau client\n");
        printf("-3- Modifier les donnees d'un client\n");
        printf("-0- Revenir vers le menu principal\n");
        printf("Choix : ");
        scanf("%d",&choix);
    }
    while (choix<0 || choix >3);
    return choix;

}



void procedure_gestion_clients(Agence * a)
{

    int choix = -1;
    int idClient = -1;
    int ageMinimale = 21;
    int ageMaximale = 80;
    do
    {
        choix = menu_gestion_clients();
        switch(choix)
        {
        case 1 :
            afficherListeClient(*a);
            break;
        case 2 :
            if( ajouterNouveauClient(a,ageMinimale,ageMaximale) == 1)
            {
                printf("\n\n [ Succee ] Client ajoute avec succee\n\n");
            }
            break;
        case 3 :

            printf("\n Donnez l'id du client a modifier : ");
            scanf("%d",&idClient);
            if( modifierUnClient(a,idClient,ageMinimale,ageMaximale) == 1)
            {
                printf("\n\n [ Succee ] Client modifie avec succee\n\n");
            }
            break;
        case 0 :
            break;
        }
    }
    while (choix != 0);
}

int menu_gestion_parc()
{

    int choix = -1 ;
    do
    {
        printf("\n------------------------------------------------\n");
        printf("\n------------- MENU GESTION PARC ----------------\n");
        printf("\n------------------------------------------------\n");
        printf("-1- Consulter les vehicules\n");
        printf("-2- Ajouter un vehicule\n");
        printf("-3- Modifier un vehicule\n");
        printf("-0- Revenir vers le menu principal\n");
        printf("Choix : ");
        scanf("%d",&choix);
    }
    while (choix<0 || choix >4);
    return choix;

}

void procedure_gestion_parc(Agence * a)
{

    int choix = -1;
    int idVoiture = -1;
    do
    {
        choix = menu_gestion_parc();
        switch(choix)
        {
        case 1 :
            afficherListeVehicule((*a).parc);
            break;
        case 2 :
            if( ajouterNouveauVehicule(&((*a).parc)) == 1)
            {
                printf("\n\n [ Succee ] Vehicule ajoutee avec succee\n\n");
            }
            break;
        case 3 :

            printf("\n Donnez l'id du vehicule a modifier : ");
            scanf("%d",&idVoiture);
            if(modifierVehicule(&((*a).parc),idVoiture) == 1)
            {
                printf("\n\n [ Succee ] Vehicule modifiee avec succee\n\n");
            }
            break;
        case 0 :
            break;
        }
    }
    while (choix != 0);
}

int menu_gestion_reservations()
{
    int choix = -1 ;
    do
    {
        printf("\n------------------------------------------------\n");
        printf("\n-------- MENU GESTION RESERVATIONS -------------\n");
        printf("\n------------------------------------------------\n");
        printf("-1- Consulter les reservations\n");
        printf("-2- Rechercher l'id d'une voiture\n");
        printf("-3- Rechercher l'id d'un client\n");
        printf("-4- Creer une nouvelle reservation\n");
        printf("-5- Modifier une reservation\n");
        printf("-6- Annuler une reservation\n");
        printf("-0- Revenir vers le menu principal\n");
        printf("Choix : ");
        scanf("%d",&choix);
    }
    while (choix<0 || choix >6);
    return choix;

}

void procedure_gestion_reservation(Agence * a)
{
    int choix;
    int idVoiture;
    int indiceVoiture;
    int idReservation;
    int voitureExiste;
    int clientExiste;
    int indiceClient;
    int indiceReservation;
    int idClient;
    int i;
    char recherche[100];
    int nbResultatTrouvee;
    do
    {

        choix = -1;
        idVoiture = -1;
        idClient = -1;
        idReservation = -1;
        indiceVoiture = -1;
        indiceReservation = -1;
        indiceClient = -1;
        i = -1;
        choix = menu_gestion_reservations();
        switch(choix)
        {
        case 1 :
            afficherListeReservation((*a));
            break;
        case 2 :
            i=0;
            printf("\n\n Veuillez enter une recherche par Marque / Modele / Immatriculation : ");

            scanf("%s",recherche);

            conv_min_maj(recherche);
            printf("\n\n\n------------------ Resultat Recherche -----------------\n\n\n");
            nbResultatTrouvee = 0;
            for (i=0; i< (*a).parc.nbVoitures ; i++)
            {
                if (  chaineExisteDansChaine((*a).parc.voitures[i].marque, recherche) == 1 ||
                        chaineExisteDansChaine((*a).parc.voitures[i].modelele, recherche) == 1  ||
                        chaineExisteDansChaine((*a).parc.voitures[i].immatriculation, recherche) == 1 )
                {
                    afficherVoiture((*a).parc.voitures[i]);
                    nbResultatTrouvee++;
                }
            }
            if(nbResultatTrouvee == 0 )
            {

                printf("\n [ INFO ] Auccun resultat trouve \n\n\n");
            }
            else
            {
                printf("\n [ INFO ] %d resultat(s) trouve(s) \n\n\n", nbResultatTrouvee);
            }


            break;
        case 3 :
            i=0;
            printf("\n\n Veuillez enter une recherche par Nom / Prenom / Email / Numero de telephone : ");

            scanf("%s",recherche);

            printf("\n\n\n------------------ Resultat Recherche -----------------\n\n\n");
            nbResultatTrouvee = 0;
            for (i=0; i< (*a).nbClients ; i++)
            {
                if ( chaineExisteDansChaine((*a).clients[i].nom, recherche)  == 1 || chaineExisteDansChaine((*a).clients[i].prenom, recherche)  == 1 || chaineExisteDansChaine((*a).clients[i].numTel, recherche)   == 1 || chaineExisteDansChaine((*a).clients[i].email, recherche)  == 1)
                {
                    afficherClient((*a).clients[i]);
                    nbResultatTrouvee++;
                }
            }

            if(nbResultatTrouvee == 0 )
            {

                printf("\n [ INFO ] Auccun resultat trouve \n\n\n");
            }
            else
            {
                printf("\n [ INFO ] %d resultat(s) trouve(s) \n\n\n", nbResultatTrouvee);
            }

            break;
        case 4 :

            printf("\n Donnez l'id de la voiture de location : ");
            scanf("%d",&idVoiture);
            indiceVoiture = chercherVehicule((*a).parc,idVoiture);
            if ( indiceVoiture >= 0 )
            {
                if((*a).parc.voitures[indiceVoiture].disponibilite == 1)
                {
                    printf("\n Donnez l'id du client locataire : ");
                    scanf("%d",&idClient);

                    indiceClient = chercherClient(a,idClient);
                    if ( indiceClient >= 0 )
                    {
                        ajouterNouvelleReservation(a,idVoiture,idClient,(*a).parc.voitures[indiceVoiture].nbPassagersMax,(*a).parc.voitures[indiceVoiture].tarifJournalierEnEuro);

                        printf("\n\n [ Succee ] Votre reservation a ete enregistrer\n\n");

                    }
                    else
                    {

                        printf("\n\n[ ERREUR ] Saisie non valide : Client N-%04d inexistant\n\n",idClient);
                    }
                }
                else
                {


                    printf("\n\n[ ERREUR ] Saisie non valide : Voiture N-%04d deja louee\n\n",idVoiture);
                }

            }
            else
            {

                printf("\n\n[ ERREUR ] Saisie non valide : Voiture N-%04d inexistante\n\n",idVoiture);

            }
            break;
        case 5 :
            printf("\n Donnez l'id de la reservation a modifier : ");
            scanf("%d",&idReservation);
            if(modifierUneReservation(a,idReservation) == 1)
            {
                printf("\n\n [ Succee ] Reservation N-%04d modifiee avec succee\n\n",idReservation);
            }
            break;
        case 6 :
            printf("\n Donnez l'id de la reservation a annuler : ");
            scanf("%d",&idReservation);
            indiceReservation = chercherReservation(a,idReservation);
            if ( indiceReservation >= 0 )
            {
                (*a).reservations[indiceReservation].annullee = 1;
                changeeDisponibiliteVehicule(&((*a).parc),(*a).reservations[indiceReservation].idVehicule);
                printf("\n\n[ Succee ] Reservation N-%04d annullee avec succee\n\n\n\n",idReservation);
                printf("\n\n[ Info ] Voiture N-%04d est desormais disponible\n\n\n\n",(*a).reservations[indiceReservation].idVehicule);

            }
            else
            {
                printf("\n\n[ ERREUR ] Saisie non valide : Reservation %04d inexistante\n\n",idReservation);

            }

            break;
        case 0 :
            break;
        }
    }
    while (choix != 0);
}


int ajouterNouveauClient(Agence * a, int ageMin,int ageMax) //La fonction prend en entrée un pointeur vers l'agence et deux entiers, l'âge minimum et maximum pour être éligible en tant que client
{


    Client c = saisirClient((*a).nbClients + 1);
    if(differenceEnAnnees(c.dateDeNaissance,dateDAujourdhui()) >= ageMin && differenceEnAnnees(c.dateDeNaissance,dateDAujourdhui()) <= ageMax)
    {
        if(differenceEnAnnees(c.dateObtentionDuPermis,dateDAujourdhui()) >= 3 )//verifier que la date d'obtention du permis est superieur a 3ans
        {
            (*a).clients[(*a).nbClients] = c;
            (*a).nbClients++;
            return 1;
        }
        else
        {
            printf("\n\n[ ERREUR ] Saisie client no requise : Permis de conduire recent (minimum 3 ans)\n\n");
        }


    }
    else
    {

        printf("\n\n[ ERREUR ] Saisie client no requise : Age Conducteur Non Respecte (minimum 21 ans maximum 80 ans)\n\n");

    }


    return 0;
}

void afficherListeClient(Agence a)
{
    int i = 0;
    printf("\nNom Agence : %s",a.nom);
    printf("\nNombre de clients : %04d",a.nbClients);
    printf("\n\nListe clients : \n");

    for (i = 0 ; i < a.nbClients ; i++)
    {

        printf("\n------------------------------------------------\n");
        afficherClient(a.clients[i]);

    }


}

//modifier les informations du client dans l'agence
int modifierUnClient(Agence *  a,int idClient,int ageMin,int ageMax)
{

    int indiceClient = chercherClient(a,idClient);
    if(indiceClient >= 0)
    {
		// On modifie les informations du client en utilisant la fonction modifierClient()
        Client c = modifierClient((*a).clients[indiceClient]);
		
		    // On vérifie si les conditions d'âge et de permis sont respectées

        if(differenceEnAnnees(c.dateDeNaissance,dateDAujourdhui()) >= ageMin  && differenceEnAnnees(c.dateDeNaissance,dateDAujourdhui()) <= ageMax)
        {
            if(differenceEnAnnees(c.dateObtentionDuPermis,dateDAujourdhui()) >= 3)
            {

                (*a).clients[indiceClient] =  c;
                return 1;
            }
            else
            {

                printf("\n\n[ ERREUR ] Saisie non valide : Regles permis ou age non respecte\n\n");

            }
        }
        else
        {

            printf("\n\n[ ERREUR ] Saisie non valide : Regles permis ou age non respecte\n\n");

        }
    }
    else
    {
        printf("\n\n[ ERREUR ] Saisie non valide : ID Client inexistant\n\n");

    }
    return 0;
}

void afficherListeReservation(Agence a)
{
    int i = 0;
    printf("\nNom Agence : %s",a.nom);
    printf("\nNombre de reservations : %04d",a.nbResevations);
    printf("\n\nListe reservations : \n");

    for (i = 0 ; i < a.nbResevations ; i++)
    {

        printf("\n------------------------------------------------\n");
        afficherReservation(a.reservations[i]);

    }

}

void ajouterNouvelleReservation(Agence * a,int idVehicule,int idClient,int capacitePassagerMax,int tarifJournalierVoiture)
{

    Reservation r = saisirReservation((*a).nbResevations + 1,idVehicule,idClient,capacitePassagerMax,tarifJournalierVoiture);
    r.annullee = 0;
    changeeDisponibiliteVehicule(&((*a).parc),idVehicule);
    (*a).reservations[(*a).nbResevations] = r;
    (*a).nbResevations++;
    afficherReservation(r);

}
int chercherReservation(Agence * a, int idReservation)
{

    int i = 0;

    for (i = 0 ; i < (*a).nbResevations ; i ++)
    {
        if ((*a).reservations[i].id == idReservation)
        {
            return i;
        }
    }
    return -1;
}

int modifierUneReservation(Agence * a,int idReservation)
{
    int indiceVoiture=-1;
    int indiceClient=-1;
    int changerVehicule = 0;
    int changerClient = 0;
    int idVoiture = 0;
    int idClient = 0;

    int indiceReservation = chercherReservation(a,idReservation);
    if(indiceReservation >= 0)
    {
        do
        {
            printf("\n Voulez vous modifier le vehicule concerne  ( 1 : Oui / 0 : Non )? ");
            scanf("%d",&changerVehicule);
        }
        while (changerVehicule != 0 && changerVehicule !=1);
        do
        {
            printf("\n Voulez vous changer le client concerne ( 1 : Oui / 0 : Non )? ");
            scanf("%d",&changerClient);
        }
        while (changerClient != 0 && changerClient !=1);

        if( changerVehicule == 1 )
        {
            printf("\n Donnez le nouveau id de la voiture louee : ");
            scanf("%d",&idVoiture);
            indiceVoiture = chercherVehicule((*a).parc,idVoiture);
            if ( indiceVoiture == -1 )
            {
                printf("\n\n[ ERREUR ] Saisie non valide : Voiture %04d inexistante\n\n",idVoiture);
                return 0;
            }
            else
            {
                if((*a).parc.voitures[indiceVoiture].disponibilite == 1)
                {
                    // changer l'id voiture dans la reservation
                    (*a).reservations[indiceReservation].idVehicule = idVoiture;
                }
                else
                {

                    printf("\n\n[ ERREUR ] Saisie non valide : Voiture %04d deja louee\n\n",idVoiture);
                    return 0;
                }


            }
        }
        if(changerClient == 1)
        {
            printf("\n Donnez le nouveau id du client locataire : ");
            scanf("%d",&idClient);
            indiceClient = chercherClient(a,idClient);
            if ( indiceClient >= 0 )
            {
                // changer l'id client dans la reservation
                (*a).reservations[indiceClient].idClient = idClient;
            }

            else
            {

                printf("\n\n[ ERREUR ] Saisie non valide : Client %04d inexistant\n\n",idClient);
                return 0;
            }

        }

        indiceVoiture = chercherVehicule((*a).parc,(*a).reservations[indiceReservation].idVehicule );

        Reservation r = modifierReservation((*a).reservations[indiceReservation],(*a).parc.voitures[indiceVoiture].nbPassagersMax,(*a).parc.voitures[indiceVoiture].tarifJournalierEnEuro);
        (*a).reservations[indiceReservation] =  r;
        afficherReservation(r);

        return 1;
    }
    else
    {
        printf("\n\n[ ERREUR ] Saisie non valide : ID Reservation inexistant\n\n");

    }

    return 0;
}

void remplaceCaractereParUnAutre(char caractere_a_remplacer, char nv_caractere, char *chaine )
{
    for (int i = 0; chaine[i] != '\0'; i++)
    {
        if (chaine[i] == caractere_a_remplacer)
        {
            chaine[i] = nv_caractere;
        }
    }
}

Agence recupererAgenceApartirDuFichier(char * nomAgence,int nbVoituresMax)
{
    Agence agence ;
    strcpy(agence.nom, nomAgence);
    agence.nbClients = 0;
    agence.nbResevations = 0;
    agence.parc.nbVoitures = 0;
    agence.parc.nbVoituresMax = nbVoituresMax;
    int retourScanf = 0;
    char* p;
    // Ouverture du fichier en mode lecture
    FILE *f = fopen("sauvegarde.txt", "r");

    // Vérification si le fichier est bien ouvert
    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.");
        exit(1);
    }
    // Lecture du nom de l'agence
    fscanf(f, "Agence\n");
    fscanf(f, "%s\n", agence.nom);

    // Lecture des clients
    fscanf(f, "Clients\n");
    agence.nbClients = 0;

    while (!feof(f))
    {

        retourScanf = fscanf(f, "%d %s %s %d/%d/%d %d/%d/%d %s %s\n",
                             &agence.clients[agence.nbClients].id, agence.clients[agence.nbClients].nom, agence.clients[agence.nbClients].prenom,
                             &agence.clients[agence.nbClients].dateDeNaissance.jour, &agence.clients[agence.nbClients].dateDeNaissance.mois, &agence.clients[agence.nbClients].dateDeNaissance.annee,
                             &agence.clients[agence.nbClients].dateObtentionDuPermis.jour, &agence.clients[agence.nbClients].dateObtentionDuPermis.mois, &agence.clients[agence.nbClients].dateObtentionDuPermis.annee,
                             agence.clients[agence.nbClients].numTel, agence.clients[agence.nbClients].email);

        if ( retourScanf == 11)
        {


            agence.nbClients++;
        }

        else
        {
            break;
        }
    }

    // Lecture des voitures
    fscanf(f, "Voitures\n");
    agence.parc.nbVoitures = 0;
    while (!feof(f))
    {

        if (fscanf(f, "%d %d %d %c %d %d %d %d %d %d %d %d %d %f %f %s %s %s\n",
                   &agence.parc.voitures[agence.parc.nbVoitures].id, &agence.parc.voitures[agence.parc.nbVoitures].disponibilite,
                   &agence.parc.voitures[agence.parc.nbVoitures].typeDeTransmission, &agence.parc.voitures[agence.parc.nbVoitures].categorie,
                   &agence.parc.voitures[agence.parc.nbVoitures].climatisation, &agence.parc.voitures[agence.parc.nbVoitures].nbPortes,
                   &agence.parc.voitures[agence.parc.nbVoitures].nbPassagersMax, &agence.parc.voitures[agence.parc.nbVoitures].nbCarteCreditExigee,
                   &agence.parc.voitures[agence.parc.nbVoitures].airBagConducteur, &agence.parc.voitures[agence.parc.nbVoitures].airBagPassager,
                   &agence.parc.voitures[agence.parc.nbVoitures].abs, &agence.parc.voitures[agence.parc.nbVoitures].fermetureCentralise,
                   &agence.parc.voitures[agence.parc.nbVoitures].directionAssiste, &agence.parc.voitures[agence.parc.nbVoitures].tarifJournalierEnEuro,
                   &agence.parc.voitures[agence.parc.nbVoitures].kilometrage, agence.parc.voitures[agence.parc.nbVoitures].marque,
                   agence.parc.voitures[agence.parc.nbVoitures].modelele, agence.parc.voitures[agence.parc.nbVoitures].immatriculation) == 18)
        {
            remplaceCaractereParUnAutre('_',' ',agence.parc.voitures[agence.parc.nbVoitures].modelele);
            remplaceCaractereParUnAutre('_',' ',agence.parc.voitures[agence.parc.nbVoitures].marque);
            remplaceCaractereParUnAutre('_',' ',agence.parc.voitures[agence.parc.nbVoitures].immatriculation);


            agence.parc.nbVoitures++;
        }

        else
        {
            break;
        }
    }

    // Lecture des réservations
    fscanf(f, "Reservations\n");
    agence.nbResevations = 0;
    while (!feof(f))
    {

        if( fscanf(f, "%d %d %d %d/%d/%d %d %d %f %f %d\n",
                   &agence.reservations[agence.nbResevations].id,
                   &agence.reservations[agence.nbResevations].idClient,
                   &agence.reservations[agence.nbResevations].idVehicule,
                   &agence.reservations[agence.nbResevations].effectueLe.jour,
                   &agence.reservations[agence.nbResevations].effectueLe.mois,
                   &agence.reservations[agence.nbResevations].effectueLe.annee,
                   &agence.reservations[agence.nbResevations].nbJours,
                   &agence.reservations[agence.nbResevations].nbPassagers,
                   &agence.reservations[agence.nbResevations].tarifAssurance,
                   &agence.reservations[agence.nbResevations].coutTotale,
                   &agence.reservations[agence.nbResevations].annullee) == 11)
        {

            agence.nbResevations++;
        }
        else
        {
            break;
        }
    }
    printf("\n\n [ Succee ] Lecture du fichier effectuee avec succee\n\n");

    // Fermeture du fichier
    fclose(f);
    return agence;
}

void enregistrerAgenceDansSauvegarde(Agence agence)
{
    // Ouverture du fichier en mode écriture
    FILE *f = fopen("sauvegarde.txt", "w");

    // Vérification si le fichier est bien ouvert
    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.");
        exit(1);
    }

    // Ecriture du nom de l'agence
    fprintf(f, "Agence\n");
    fprintf(f, "%s\n", agence.nom);

    // Ecriture des clients
    fprintf(f, "Clients\n");
    for (int i = 0; i < agence.nbClients; i++)
    {
        remplaceCaractereParUnAutre(' ', '_', agence.clients[i].nom);
        remplaceCaractereParUnAutre(' ', '_', agence.clients[i].prenom);
        remplaceCaractereParUnAutre(' ', '_', agence.clients[i].numTel);
        remplaceCaractereParUnAutre(' ', '_', agence.clients[i].email);
        fprintf(f, "%d %s %s %d/%d/%d %d/%d/%d %s %s\n",
                agence.clients[i].id, agence.clients[i].nom,agence.clients[i].prenom,
                agence.clients[i].dateDeNaissance.jour, agence.clients[i].dateDeNaissance.mois, agence.clients[i].dateDeNaissance.annee,
                agence.clients[i].dateObtentionDuPermis.jour, agence.clients[i].dateObtentionDuPermis.mois, agence.clients[i].dateObtentionDuPermis.annee,
                agence.clients[i].numTel, agence.clients[i].email);


    }

    // Ecriture des voitures
    fprintf(f, "Voitures\n");
    for (int i = 0; i < agence.parc.nbVoitures; i++)
    {
        remplaceCaractereParUnAutre(' ', '_', agence.parc.voitures[i].marque);
        remplaceCaractereParUnAutre(' ', '_', agence.parc.voitures[i].modelele);
        remplaceCaractereParUnAutre(' ', '_', agence.parc.voitures[i].immatriculation);
        fprintf(f, "%d %d %d %c %d %d %d %d %d %d %d %d %d %f %f %s %s %s\n",
                agence.parc.voitures[i].id, agence.parc.voitures[i].disponibilite, agence.parc.voitures[i].typeDeTransmission,
                agence.parc.voitures[i].categorie, agence.parc.voitures[i].climatisation, agence.parc.voitures[i].nbPortes,
                agence.parc.voitures[i].nbPassagersMax, agence.parc.voitures[i].nbCarteCreditExigee,
                agence.parc.voitures[i].airBagConducteur, agence.parc.voitures[i].airBagPassager, agence.parc.voitures[i].abs,
                agence.parc.voitures[i].fermetureCentralise, agence.parc.voitures[i].directionAssiste,
                agence.parc.voitures[i].tarifJournalierEnEuro, agence.parc.voitures[i].kilometrage,
                agence.parc.voitures[i].marque, agence.parc.voitures[i].modelele, agence.parc.voitures[i].immatriculation);
    }

    // Ecriture des réservations
    fprintf(f, "Reservations\n");
    for (int i = 0; i < agence.nbResevations; i++)
    {
        fprintf(f, "%d %d %d %d/%d/%d %d %d %f %f %d\n",
                agence.reservations[i].id,
                agence.reservations[i].idClient,
                agence.reservations[i].idVehicule,
                agence.reservations[i].effectueLe.jour,
                agence.reservations[i].effectueLe.mois,
                agence.reservations[i].effectueLe.annee,
                agence.reservations[i].nbJours,
                agence.reservations[i].nbPassagers,
                agence.reservations[i].tarifAssurance,
                agence.reservations[i].coutTotale,
                agence.reservations[i].annullee
               );
    }
    printf("\n\n [ Succee ] Ecriture dans fichier effectuee avec succee\n\n");

// Fermeture du fichier
    fclose(f);

}

void quitter(Agence * a)
{
    enregistrerAgenceDansSauvegarde(*a);
    printf("Au revoir\n");
}

int main()
{
    char nomAgence[] = "FAST CAR";
    int nbVoituresMax = 100;

    printf("Bienvenue dans l'agence.\n");

    if (authentifier())
    {
        printf("Authentification reussie.\n\n");
        printf("Lancement de l'application...\n\n");
        Agence a = recupererAgenceApartirDuFichier(nomAgence,nbVoituresMax);
        procedure_principale(&a);
    }
    else
    {
        printf("Impossible de s'authentifier. Fermeture de l'application.\n");
    }


    return 0;
}
