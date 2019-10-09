/*


			Bienvenue sur le Projet d'Arthur Mougin


	Principe :

			C'est un code fonctionnel ou chaque fonction est documentée


	Comment l'utiliser :

			1) Réduisez tout les commentaires en minuscule pour voir le 
			code brute.
			
			2) Ouvrez les commentaires des fonctions et classes qui vous 
			intéresse.


	Attention :

			Ici sont proposés des fonctions et usages ainsi que des 
			explications dans chaque commentaires. Ce sont des explications
			basées sur mon interpretation personnelle et des listes
			non exaustives filtrées pour mettre en avant le potentiel de 
			chaque fonction.


	Basé sur le projet et la doc :
	https://www.sfml-dev.org/documentation/2.5.1/
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

/*
	/!\ toutes les fonctions sfml sont préfixées par sf::
	utiliser cette fonction permet de supprimer ce prefixage pour une meilleure lisibilité

	  BEST PRACTICE : Si vous etes amenés à #include beaucoups de librairies différentes, 
	  le sf:: peut avoir son intérêt si plusieurs librairies appellent leur fonction de
	  manière similaire
*/
using namespace sf;

int main()
{
	/*
		Créer la fenetre principale
	
		Ordre des dimensions initiales : largeur, hauteur 
		paramêtre optionnel : ModeBitsPerPixel 
			(je ne sais pas ce que c'est ?) défaut : 32


		Ce qu'on peut faire avec :

			Obtenir et modifier ses dimensions (utiles pour les cas de redimensionnement) 
				-> window.getSize()
				-> window.setSize(VotreDimension)	//Voir doc pour les types requis

			Prendre une photo -> window.capture()

			Connaitre et modifier sa position à l'écran (utiles pour des puzzles avec 
			plusieurs fenetres) 
				-> window.getPosition()
				-> window.setPosition(votrePosition)	//Voir doc pour les types requis
			
			nommer la fenetre -> setTitle(VotreTitre)	//Voir doc pour les types requis

			...

		(Liste non exaustive)


		DOC :
		https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderWindow.php
		https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1VideoMode.php
	*/
	RenderWindow window(VideoMode(800, 800), "SFML works!");

	/*

		Chargement en mémoire des Textures 
		C'est une ressource qui sera appelé plus tard.

		(Visual Studio)
		Pour importer des images : drag and drop dans le dossier 
		"Resource Files" de votre projet.


		Ce qu'on peut faire avec :

			obtenir les dimensions -> texture.getSize() (utile pour de l'optimisation)

			modifier tout ou partie de la texture a partir d'une tonne de sources
				-> texture.update(VosParametres)	//voir la doc pour toutes les options 
				possibles

			tester et appliquer un filtre smooth (utile pour sauver les meubles avec 
			des textures de mauvaise qualité)
				-> texture.setSmooth(booléain vrai ou faux)
				-> texture.isSmooth()

			tester ou activer la répétition (utile pour les parois ou motifs repetitifs)
				-> texture.isRepeated()
				-> texture.setRepeated(booléain vrai ou faux)

			...

		(Liste non exaustive)
		

		DOC :
		https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Texture.php

	*/
	Texture texture;
	//On charge l'image dans la texture, si ca marche, tout va bien, sinon on plante
	if (!texture.loadFromFile("dragon.png"))
		return EXIT_FAILURE;

	/*
		Représentation dessinable d'une texture 
		(que l'on peut déplacer dans la fenêtre à notre guise par exemple)
		Elle hérite de deux classes appelés Transformable et Drawable


		Ce qu'on peut faire avec :

			Créer une sprite à partir d'une partie de texture (utile pour des textures 
			contenant différentes sprites)
				-> sprite(texture, vosDimension)	//Voir doc pour les types requis
				ou après sprite(texture)
				-> sprite.setTextureRect(vosDimension)	//Voir doc pour les types requis
			 
			Obtenir les bords de l'image (utile pour le calcul de colisions)
				-> sprite.getGlobalBounds()	//Voir doc pour les types utilisés

				(Vous verrez une différence entre coordonnées Locales et Globales, demandez 
				moi de l'aide pour des explications si besoin)

			Deplacer la sprite (Hérité de la classe Transformable)
				-> sprite.move(VotreDirection)	//Voir doc pour les types requis
				(Incrémentation : utile pour les deplacements)
				ou 
				-> sprite.setPostition(VotrePosition)	//Voir doc pour les types requis
				(reecriture : utile pour les téléportations)

			Tourner la sprite (Hérité de la classe Transformable)
				-> sprite.rotate(VotreRotation)	//Voir doc pour les types requis
				(Incrémentation : utile pour les animations de rotation)
				ou
				-> sprite.setRotation(VotreRotation)	//Voir doc pour les types requis
				(reecriture : utile pour réinitialiser la rotation)

			Redimensionner la sprite (Hérité de la classe Transformable)
				-> sprite.scale(vosFacteurs)	//Voir doc pour les types requis
				(Incrémentation : utile pour les animations de taille)
				ou
				-> sprite.setScale(vosFacteurs)	//Voir doc pour les types requis
				(reecriture : utile pour réinitialiser une taille)
				

			...

		(Liste non exaustive)

		DOC :
		https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Sprite.php#aa795483096b90745b2e799532963e271
	
	*/
	Sprite sprite(texture);

	/*
	
		La classe Font permet de manipuler des polices d'ecriture
		
		En dehors d'utiliser la police pour écrire du texte, et du chargement de police,
		on ne peut pas la modifier.
		Seul la lecture d'informations particulières, comme les mesures en px de details,
		peut etre utile (et encore uniquement pour un usage esthétique).

		ATTENTION :
			Les polices "bipmap" peuvent causer problème, cherchez une version vectorielle
			à la place

		DOC :
		https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Font.php

	*/
	Font font;
	//On charge la police, si ca marche, tout va bien, sinon on plante
	if (!font.loadFromFile("arial.ttf"))
		return EXIT_FAILURE;

	/*
	
		Affichage de Texte

		paramêtres de constructeur : Texte à écrire, police, et taille en pixel d'un 
		caractère (defaut à 30)
		text("Hello SFML", font, 50);

		Ce qu'on peut faire avec :
				

	*/
	Text text("Hello SFML", font, 50);

}
