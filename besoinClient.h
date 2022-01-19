/**
 * \file besoinClient.h
 * \Creer des prototypes
 * \author Nathan Verdier
 * \date 25 octobre 2021
 *
 * Creer des prototypes pour le fichier besoinClient.c
 */

/**
 * \brief Afficher le menu et les choix possibles
 */
void afficheMenu(void);

/**
 * \brief Lire le fichier stock.don dans 4 tables
 * \param tRef[] est un tableau de reference
 * \param tQuant[] est un tableau de quantite
 * \param tPrixU[] est un tableau de prix
 * \param tSeuil[] est un tableau de seuil
 * \param tMax est la taille physique des tableaux
 * \return taille logique des tableaux
 */
int fLecture(int tRef[], int tQuant[],float tPrixU[], int tSeuil[], int tMax);

/**
 * \brief Entrer les valeurs dans 4 tableaux
 * \param *tRef est un tableau de reference
 * \param *tQuant est un tableau de quantite
 * \param tPrixU[] est un tableau de prix
 * \param tSeuil[] est un tableau de seuil
 * \param tMax est la taille physique des tableaux
 * \param *n est un pointeur de taille logique des tableaux
 */
void Gstock(int *tRef, int *tQuant, float tPrixU[], int tSeuil[], int tMax, int *n);

/**
 * \brief Verifier les valeurs entrees au clavier
 * \param *qte est un pointeur de quantite
 * \param *prixU est un pointeur de prix
 * \param *seuilSecu est un pointeur de seuil
 */
void saisieControle(int *qte, float *prixU, int *seuilSecu);

/**
 * \brief Ouvre le fichier stock.don en mode ecriture et ecrit dedans
 * \param *tRef est un tableau de reference
 * \param tQuant[] est un tableau de quantite
 * \param *tPrixU est un tableau de prix
 * \param tSeuil[] est un tableau de seuil
 * \param n est la taille logique des tableaux
 */
void fSauvegarde(int *tRef, int tQuant[], float *tPrixU, int tSeuil[], int n);

/**
 * \brief Cherche la réference d'un produit
 * \param *tRef est un tableau de reference
 * \param val est la valeur recherchee
 * \param n est la taille logique des tableaux
 * \return la position de la valeur
 */
int chercheRef(int *tRef, int val, int n);

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
void traitementCommande(int *tRef, int tQuant[], float *tPrixU, int tSeuil[], int *tRefDevis, int tQuantDevis[], float *tPrixUDevis, int *d, int n);

/**
 * \brief Affiche l'etat du stock
 * \param *tRef est un tableau de reference
 * \param tQuant[] est un tableau de quantite
 * \param *tPrixU est un tableau de prix
 * \param tSeuil[] est un tableau de seuil
 * \param n est la taille maximum des tableaux
 */
void affiche(int *tRef, int tQuant[], float *tPrixU, int tSeuil[], int n);

/**
 * \brief Affiche les produits en risque de rupture
 * \param *tRef est un tableau de reference
 * \param tQuant[] est un tableau de quantite
 * \param *tPrixU est un tableau de prix
 * \param tSeuil[] est un tableau de seuil
 * \param n est la taille maximum des tableaux
 */
void seuilSecu(int *tRef, int tQuant[], float *tPrixU, int tSeuil[], int n);

/**
 * \brief Affiche les devis d'une commande et la quantité
 * \param *tRef est un tableau de reference
 * \param tQuant[] est un tableau de quantite
 * \param *tPrixU est un tableau de prix
 * \param tSeuil[] est un tableau de seuil
 * \param d est la taille maximum des tableaux
 */
void devis(int *tRefDevis, int tQuantDevis[], float *tPrixUDevis, int d);

/**
 * \brief Réapprovisionne le produit choisi
 * \param *tRef est un tableau de reference
 * \param tQuant[] est un tableau de quantite
 * \param n est la taille maximum des tableaux
 */
void Reapprovisionnement(int *tRef, int tQuant[], int n);

/**
 * \brief Verifie si la reference existe est fait appel a une fonction de suppression 
 * \param *tRef est un tableau de reference
 * \param tQuant[] est un tableau de quantite
 * \param *tPrixU est un tableau de prix
 * \param tSeuil[] est un tableau de seuil
 * \param n est un pointeur de taille logique des tableaux
 */
void suppression(int *tRef, int tQuant[], float *tPrixU, int tSeuil[], int *n);

/**
 * \brief Supprime un element d'une table par rapport a une position donnee, diminue la taille logique de 1
 * \param *tRef est un tableau de reference
 * \param tQuant[] est un tableau de quantite
 * \param *tPrixU est un tableau de prix
 * \param tSeuil[] est un tableau de seuil
 * \param n est la taille logique des tableaux
 * \param pos est la position de l'element a supprimer
 */
int supDecalage(int *tRef, int tQuant[], float *tPrixU, int tSeuil[], int n, int pos);

/**
 * \brief fonction globale fait appel a toutes les fonctions
*/
void global(void);
