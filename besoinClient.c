#include <stdio.h>
#include "besoinClient.h"
#define tTaille 20

/**
 * \file besoinClient.c
 * \lire un fichier et écrire dedans
 * \author Nathan Verdier
 * \date 25 octobre 2021
 *
 * Lire un fichier nomme et afficher son contenu
 * Supprimer et ajouter des elements en fonction de l'utilisateur
 */

/**
 * \brief Afficher le menu et les choix possibles
 */
void afficheMenu(void)
{
	printf("+-------------------------------------------------------+\n");
	printf("|  1.\tAfficher le stock\t\t\t\t|\n");
	printf("|  2.\tConstituer le stock\t\t\t\t|\n");
	printf("|  3.\tPasser une commande\t\t\t\t|\n");
	printf("|  4.\tProduit en risque de rupture\t\t\t|\n");
	printf("|  5.\tDevis\t\t\t\t\t\t|\n");
	printf("|  6.\tReapprovisionner\t\t\t\t|\n");
	printf("|  7.\tSupprimer\t\t\t\t\t|\n");
	printf("|  9.\tQuitter\t\t\t\t\t\t|\n");
	printf("+-------------------------------------------------------+\n");
}

/**
 * \brief Lire le fichier stock.don dans 4 tables
 * \param tRef[] est un tableau de reference
 * \param tQuant[] est un tableau de quantite
 * \param tPrixU[] est un tableau de prix
 * \param tSeuil[] est un tableau de seuil
 * \param tMax est la taille physique des tableaux
 * \return taille logique des tableaux
 */
int fLecture(int tRef[], int tQuant[],float tPrixU[], int tSeuil[], int tMax)
{
	int i = 0, Ref, qte, seuilSecu;
	float prixU;
	FILE *fe;
	fe=fopen("stock.don","r");
	if(fe==NULL)
	{	
		printf("Probleme ouverture fichier(surement inexistant)\n");
		return 0;
	}
	fscanf(fe,"%d %d %f %d", &Ref, &qte, &prixU, &seuilSecu);
	while(feof(fe)==0)
	{	
		if(i==tMax)
		{
			printf("Taille des tableaux trop petits\n");
			fclose(fe);
			return -1;
		}
		tRef[i]=Ref;
		tQuant[i]=qte;
		tPrixU[i]=prixU;
		tSeuil[i]=seuilSecu;
		i++;
		fscanf(fe,"%d %d %f %d", &Ref, &qte, &prixU, &seuilSecu);
	}
	fclose(fe);
	return i;
}

/**
 * \brief Entrer les valeurs dans 4 tableaux
 * \param *tRef est un tableau de reference
 * \param *tQuant est un tableau de quantite
 * \param tPrixU[] est un tableau de prix
 * \param tSeuil[] est un tableau de seuil
 * \param tMax est la taille physique des tableaux
 * \param *n est un pointeur de taille logique des tableaux
 */
void Gstock(int *tRef, int *tQuant, float tPrixU[], int tSeuil[], int tMax, int *n)
{
	int i, Ref, qte, seuilSecu;
	float prixU;
	printf("Entrer la reference de votre produit, '0' pour arreter : ");
	scanf("%d", &Ref);
	printf("\n");
	while(Ref < 0)
	{
		printf("Erreur la reference de votre produit ne peut pas etre négative, retaper : ");
		scanf("%d", &Ref);
		printf("\n");
	}	
	while(Ref!= 0)
	{
		if(*n == tMax)
		{
			printf("Tableaux plein\n");
			return;
		}
		i = chercheRef(tRef, Ref, *n);
		if(i==-1)
		{
		saisieControle(&qte, &prixU, &seuilSecu);

		tRef[*n]=Ref;
		tQuant[*n]=qte;
		tPrixU[*n]=prixU;
		tSeuil[*n]=seuilSecu;
		(*n)++;
		}
		else
			printf("Reference deja existante (creation impossible)\n");
		printf("Entrer le numero de produit, '0' pour arreter : ");
		scanf("%d", &Ref);
		printf("\n");
		while(Ref < 0)
		{
			printf("Erreur le numProduit ne peut pas être negative, retaper : ");
			scanf("%d", &Ref);
			printf("\n");
		}	
	}
}

/**
 * \brief Verifier les valeurs entrees au clavier
 * \param *qte est un pointeur de quantite
 * \param *prixU est un pointeur de prix
 * \param *seuilSecu est un pointeur de seuil
 */
void saisieControle(int *qte, float *prixU, int *seuilSecu)
{
	printf("Taper la quantite : ");
	scanf("%d", qte);
	printf("\n");
	while (*qte<0)
	{
		printf("Erreur, retaper (ne peut pas etre negative) : ");
		printf("\n");
		scanf("%d", qte);
	}
	printf("Tapez le Prix : ");
	scanf("%f", prixU);
	printf("\n");
	while (*prixU<0)
	{
		printf(" Erreur, retaper (ne peut pas etre negatif) : ");
		scanf("%f", prixU);
		printf("\n");
	}
	printf("Taper le seuil de Securite : ");
	scanf("%d", seuilSecu);
	printf("\n");
	while (*seuilSecu<0)
	{
		printf("Erreur, retaper (ne peut pas etre negatif) : ");
		scanf("%d", seuilSecu);
		printf("\n");
	}
		
}

/**
 * \brief Ouvre le fichier stock.don en mode ecriture et ecrit dedans
 * \param *tRef est un tableau de reference
 * \param tQuant[] est un tableau de quantite
 * \param *tPrixU est un tableau de prix
 * \param tSeuil[] est un tableau de seuil
 * \param n est la taille logique des tableaux
 */
void fSauvegarde(int *tRef, int tQuant[], float *tPrixU, int tSeuil[], int n)
{
	FILE *fi;
	fi=fopen("stock.don","w");
	if(fi == NULL)
	{
		printf("Probleme a l'ouverture du fichier");
		return;
	}
	for(int i=0;i<n;i++)
	{
		fprintf(fi,"%d %d %.2f %d\n", tRef[i], tQuant[i], tPrixU[i], tSeuil[i]);
	}
	fclose(fi);
}

/**
 * \brief Cherche la réference d'un produit
 * \param *tRef est un tableau de reference
 * \param val est la valeur recherchee
 * \param n est la taille logique des tableaux
 * \return la position de la valeur
 */
int chercheRef(int *tRef, int val, int n)
{
	for(int i=0;i<n;i++)
	{
		if(val == tRef[i])
			return i;
	}
	return -1;
}

/**
 * \brief Entre la valeur dans un tableau
 * \param *tRef est un tableau de reference
 * \param tQuant[] est un tableau de quantite
 * \param *tPrixU est un tableau de prix
 * \param tSeuil[] est un tableau de seuil
 * \param *tRefDevis est un tableau de reference des devis
 * \param tQuantDevis[] est un tableau de la quantite des devis
 * \param *tPrixUDevis est un tableau des prix unitaires des Devis
 * \param n est la taille maximum des tableaux
 */
void traitementCommande(int *tRef, int tQuant[], float *tPrixU, int tSeuil[], int *tRefDevis, int tQuantDevis[], float *tPrixUDevis, int *d, int n)
{
	int i, s, qte, seuil, commande;
	char toutStock;
	printf("Entrer la reference du produit que vous voulez commander, '0' pour arreter : ");
	scanf("%d", &commande);
	printf("\n");
	while(commande < 0)
	{
		printf("Erreur la reference de votre produit ne peut pas etre negative, retaper : ");
		scanf("%d", &commande);
		printf("\n");
	}
	while(commande != 0)
	{
	i = chercheRef(tRef, commande, n);
	s = chercheRef(tRefDevis, commande, n);
	if(s == -1 && i != -1)
	{
		s=*d;
		tRefDevis[s]=commande;
		(*d)++;
	}
	if(i != -1)
	{
		printf("Quelle quantité souhaitez vous ?\n");
		scanf("%d%*c", &qte);
		while(qte < 0)
		{
			printf("Erreur la quantite de votre produit ne peut pas etre negative, retaper : ");
			scanf("%d%*c", &qte);
			printf("\n");
		}
		if(qte <= tQuant[i])
		{
			tPrixUDevis[s] = tPrixU[i];
			tQuantDevis[s] += qte;
			tQuant[i] = tQuant[i] - qte;
			printf("Stock suffisant\nCommande validee\n");
		}
		else{
			printf("Stock insuffisant \nNous disposons actuellement pour ce produit d'un stock de %d\nVoulez-vous prendre tous notre stock disponible?(O/o pour oui ou N/n pour non)\n", tQuant[i]);
			scanf("%c%*c", &toutStock);
			if(toutStock == 'O' || toutStock == 'o')
			{
				tPrixUDevis[s] = tPrixU[i];
				tQuantDevis[s] += tQuant[i];
				tQuant[i] = 0;
				printf("Commande validee\n");
			}
		}
	}
	else
		printf("Reference de votre commande introuvable\n");	
	printf("Entrer la reference du produit que vous voulez commander, '0' pour arreter : ");
	scanf("%d", &commande);
	printf("\n");
	while(commande < 0)
		{
			printf("Erreur la reference de votre produit ne peut pas etre negative, retaper : ");
			scanf("%d", &commande);
			printf("\n");
		}
	}
}

/**
 * \brief Affiche l'etat du stock
 * \param *tRef est un tableau de reference
 * \param tQuant[] est un tableau de quantite
 * \param *tPrixU est un tableau de prix
 * \param tSeuil[] est un tableau de seuil
 * \param n est la taille maximum des tableaux
 */
void affiche(int *tRef, int tQuant[], float *tPrixU, int tSeuil[], int n)
{
	if(n>0)
	{
		printf("Reference\tQuantite\tPrix\tSeuil de securite\n");
		for(int i=0; i<n; i++)
			printf("%d\t\t%d\t\t%.2f\t\t%d\n", tRef[i], tQuant[i], tPrixU[i], tSeuil[i]);
	}
	else
		printf("Rien a afficher, tableau vide\n");
}

/**
 * \brief Affiche les produits en risque de rupture
 * \param *tRef est un tableau de reference
 * \param tQuant[] est un tableau de quantite
 * \param *tPrixU est un tableau de prix
 * \param tSeuil[] est un tableau de seuil
 * \param n est la taille maximum des tableaux
 */
void seuilSecu(int *tRef, int tQuant[], float *tPrixU, int tSeuil[], int n)
{
	int y=0;
	if(n>0)
	{
		printf("Reference\tQuantite\tPrix\tSeuil de securite\n");
		for(int i=0;i<n;i++)
		{
			if(tQuant[i] < tSeuil[i])
				printf("%d\t\t%d\t\t%.2f\t\t%d\n", tRef[i], tQuant[i], tPrixU[i], tSeuil[i]);
			else
				y++;
		}
		if(y==n)
			printf("Aucuns produits en dessous du seuil de securiter\n");

	}
	else
		printf("Rien a afficher, tableau vide\n");
}

/**
 * \brief Affiche les devis d'une commande et la quantité
 * \param *tRef est un tableau de reference
 * \param tQuant[] est un tableau de quantite
 * \param *tPrixU est un tableau de prix
 * \param tSeuil[] est un tableau de seuil
 * \param d est la taille maximum des tableaux
 */
void devis(int *tRefDevis, int tQuantDevis[], float *tPrixUDevis, int d)
{
	float totalPrix;
	char tele;
	FILE *fd;
	fd=fopen("devis.don","a");
	if(d>0)
	{
		printf("Reference\tQuantite\tPrix\n");
		for(int i=0;i<d;i++)
		{
			if(tQuantDevis[i] > 0)
			{
				printf("%d\t\t%d\t\t%.2f\n", tRefDevis[i], tQuantDevis[i], tPrixUDevis[i]);
				totalPrix += tPrixUDevis[i] * tQuantDevis[i];
			}
		}
		printf("Montant total a payer %.2f\n", totalPrix);
	}	
	else
		printf("Rien a afficher, tableau vide\n");
	printf("Voulez-vous le telecharger (T/t pour telecharger)?\n");
	scanf("%c%*c", &tele);
	if(tele == 'T' || tele == 't')
	{
		fprintf(fd,"Reference\tQuantite\tPrix\n");
		for(int i=0;i<d;i++)
		{
			fprintf(fd,"%d\t\t%d\t\t%.2f\n", tRefDevis[i], tQuantDevis[i], tPrixUDevis[i]);
		}
		fprintf(fd,"\n");
		fprintf(fd,"Montant total a payer %.2f\n", totalPrix);
		fprintf(fd,"-------------------------------------------------------\n\n");
		printf("Devis telecharge\n");
	}
	fclose(fd);
}

/**
 * \brief Réapprovisionne le produit choisi
 * \param *tRef est un tableau de reference
 * \param tQuant[] est un tableau de quantite
 * \param n est la taille maximum des tableaux
 */
void Reapprovisionnement(int *tRef, int tQuant[], int n)
{
	int ref, pos, qte;
	printf("Entrer la reference du produit, '0' pour arreter : ");
	scanf("%d",&ref);
	while(ref < 0)
	{	
		printf("Erreur la reference ne peut pas etre negative\nEntrer la reference du produit, '0' pour arreter : ");
		scanf("%d",&ref);
	}
	while(ref != 0)
	{	
		pos=chercheRef(tRef,ref,n);
		if(pos==-1)
		{	printf("La reference n'exite pas!\n");
			return;
		}
		printf("Entrer la quantite que vous voulez ajouter : ");
		scanf("%d",&qte);
		while(qte < 0)
		{	
			printf("Erreur la quantite ne peut pas etre negative\nReessayer, '0' pour annuler : ");
			scanf("%d",&qte);
		}

		if(qte > 0)
		{
		tQuant[pos] += qte;
		printf("Produit reapprovionner!\n");
		}
		else if(qte == 0)
			printf("Annulation du reapprovisionnement\n");
		printf("Entrer la reference du produit, '0' pour arreter : ");
		scanf("%d",&ref);
	}	
}

/**
 * \brief Verifie si la reference existe est fait appel a une fonction de suppression 
 * \param *tRef est un tableau de reference
 * \param tQuant[] est un tableau de quantite
 * \param *tPrixU est un tableau de prix
 * \param tSeuil[] est un tableau de seuil
 * \param n est un pointeur de taille logique des tableaux
 */
void suppression(int *tRef, int tQuant[], float *tPrixU, int tSeuil[], int *n)
{
	int ref, pos;
       	char sup;
	printf("Entrer la reference du produit que vous voulez supprimer, '0' pour arreter : ");
	scanf("%d%*c",&ref);
	while(ref < 0)
	{	
		printf("Erreur la reference ne peut pas etre negative\nEntrer la reference du produit, '0' pour arreter : ");
		scanf("%d%*c",&ref);
	}
	while(ref != 0)
	{	
		pos=chercheRef(tRef, ref, *n);
		if(pos==-1)
		{	printf("La reference n'exite pas!\n");
			return;
		}
		if(tQuant[pos] > 0)
			printf("Quantite restante de ce produit dans votre stock = %d\n", tQuant[pos]);
		else
			printf("Votre stock est vide pour ce produit\n");
		printf("Etes vous sur de vouloir la supprimer (O/o pour oui) ?\n");
		scanf("%c%*c", &sup);
		if(sup == 'O' || sup == 'o')
		{
			*n = supDecalage(tRef, tQuant, tPrixU, tSeuil, *n, pos);
			printf("Suppression confirmee\n");
		}
		else
			printf("Suppression annulee\n");
		printf("Entrer la reference du produit, '0' pour arreter : ");
		scanf("%d%*c",&ref);
	}	
}

/**
 * \brief Supprime un element d'une table par rapport a une position donnee, diminue la taille logique de 1
 * \param *tRef est un tableau de reference
 * \param tQuant[] est un tableau de quantite
 * \param *tPrixU est un tableau de prix
 * \param tSeuil[] est un tableau de seuil
 * \param n est la taille logique des tableaux
 * \param pos est la position de l'element a supprimer
 */
int supDecalage(int *tRef, int tQuant[], float *tPrixU, int tSeuil[], int n, int pos)
{
	for(int i=pos;i<n-1;i++)
	{
		tRef[i] = tRef[i+1];
		tQuant[i] = tQuant[i+1];
		tPrixU[i] = tPrixU[i+1];
		tSeuil[i] = tSeuil[i+1];
	}
	return n-1;
}

/**
 * \brief fonction globale fait appel a toutes les fonctions
*/
void global(void)
{
	int choix, n=0, tMax, tRef[tTaille], tQuant[tTaille], tSeuil[tTaille], tRefDevis[tTaille], tQuantDevis[tTaille]= {0}, d=0;
	float tPrixU[tTaille], tPrixUDevis[tTaille];
	tMax = tTaille;
	afficheMenu();
	printf("Choix : ");
	scanf("%d", &choix);
	while(choix<1||choix>9)
	{
		printf("Le choix doit etre compris entre 1 et 9 : ");
		scanf("%d%*c", &choix);
	}
	n = fLecture(tRef, tQuant, tPrixU,tSeuil, tMax);
	if(n==-1) return;
	while(choix != 9)
	{
		switch(choix)
		{
			case 1: 
				printf("-------------------------------------------------------\n");
				affiche(tRef, tQuant, tPrixU, tSeuil, n);
				printf("-------------------------------------------------------\n");
			break;
			case 2: 
				printf("-------------------------------------------------------\n");
				Gstock(tRef, tQuant, tPrixU,tSeuil, tMax, &n);
				printf("-------------------------------------------------------\n");
			break;
			case 3: 
				printf("-------------------------------------------------------\n");
				traitementCommande(tRef, tQuant, tPrixU, tSeuil, tRefDevis, tQuantDevis, tPrixUDevis, &d, n);
				printf("-------------------------------------------------------\n");
			break;
			case 4: 
				printf("-------------------------------------------------------\n");
				seuilSecu(tRef, tQuant, tPrixU, tSeuil, n);
				printf("-------------------------------------------------------\n");
			break;
			case 5: 
				printf("-------------------------------------------------------\n");
				devis(tRefDevis, tQuantDevis, tPrixUDevis, d);
				printf("-------------------------------------------------------\n");
			break;
			case 6: 
				printf("-------------------------------------------------------\n");
				Reapprovisionnement(tRef, tQuant, n);
				printf("-------------------------------------------------------\n");
			break;
			case 7: 
				printf("-------------------------------------------------------\n");
				suppression(tRef, tQuant, tPrixU, tSeuil, &n);
				printf("-------------------------------------------------------\n");
			break;

		}
		afficheMenu();
		printf("Choix : ");
		scanf("%d%*c", &choix);
	}
	fSauvegarde(tRef, tQuant, tPrixU, tSeuil, n);
}
