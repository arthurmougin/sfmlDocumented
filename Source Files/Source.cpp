/*


			Bienvenue sur le Projet d'Arthur Mougin


	Principe :

			C'est un code fonctionnel ou chaque fonction est document�e.
			De plus, m�me la structure est comment�e.


	Comment l'utiliser :

			1) R�duisez tout les commentaires en minuscule pour voir le 
			code brute.

			2) r�duisez les pragma pour voir les diff�rentes section de code
			
			3) Ouvrez les pragma et les commentaires qui vous interessent pour
			lire la documentation


	Attention :

			Ici sont propos�s des fonctions et usages ainsi que des 
			explications dans chaque commentaires. Ce sont des explications
			bas�es sur mon interpretation personnelle et des listes
			non exaustives filtr�es pour mettre en avant le potentiel de 
			chaque fonction.


	Bas� sur le projet et la doc :
	https://www.sfml-dev.org/documentation/2.5.1/
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

/*
	/!\ toutes les fonctions sfml sont pr�fix�es par sf::
	utiliser cette fonction permet de supprimer ce prefixage pour une meilleure lisibilit�

	  BEST PRACTICE : Si vous etes amen�s � #include beaucoups de librairies diff�rentes, 
	  le sf:: peut avoir son int�r�t si plusieurs librairies appellent leur fonction de
	  mani�re similaire
*/
using namespace sf;

int main()
{

/*
		Initialisation :

		Comme un programme normal, on commence ici par cr�er les �l�ments � utiliser 
		durant la boucle d'execution.
	
		C'est la partie qui s'execute derri�re le chargement initial d'un jeu ou d'un 
		programme.
*/
#pragma region Initialisation
	/*
		Cr�er la fenetre principale
	
		Ordre des dimensions initiales : largeur, hauteur 
		param�tre optionnel : ModeBitsPerPixel 
			(je ne sais pas ce que c'est ?) d�faut : 32


		Ce qu'on peut faire avec :

			Obtenir et modifier ses dimensions (utiles pour les cas de redimensionnement) 
				-> window.getSize()
				-> window.setSize(VotreDimension)	//Voir doc pour les types requis

			Prendre une photo -> window.capture()

			Connaitre et modifier sa position � l'�cran (utiles pour des puzzles avec 
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

		Chargement en m�moire des Textures 
		C'est une ressource qui sera appel� plus tard.

		(Visual Studio)
		Pour importer des images : drag and drop dans le dossier 
		"Resource Files" de votre projet.


		Ce qu'on peut faire avec :

			obtenir les dimensions -> texture.getSize() (utile pour de l'optimisation)

			modifier tout ou partie de la texture a partir d'une tonne de sources
				-> texture.update(VosParametres)	//voir la doc pour toutes les options 
				possibles

			tester et appliquer un filtre smooth (utile pour sauver les meubles avec 
			des textures de mauvaise qualit�)
				-> texture.setSmooth(bool�ain vrai ou faux)
				-> texture.isSmooth()

			tester ou activer la r�p�tition (utile pour les parois ou motifs repetitifs)
				-> texture.isRepeated()
				-> texture.setRepeated(bool�ain vrai ou faux)

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
		Repr�sentation dessinable d'une texture 
		(que l'on peut d�placer dans la fen�tre � notre guise par exemple)
		Elle h�rite de deux classes appel�s Transformable et Drawable


		Ce qu'on peut faire avec :

			Cr�er une sprite � partir d'une partie de texture (utile pour des textures 
			contenant diff�rentes sprites)
				-> sprite(texture, vosDimension)	//Voir doc pour les types requis
				ou apr�s sprite(texture)
				-> sprite.setTextureRect(vosDimension)	//Voir doc pour les types requis
			 
			Obtenir les bords de l'image (utile pour le calcul de colisions)
				-> sprite.getGlobalBounds()	//Voir doc pour les types utilis�s

				(Vous verrez une diff�rence entre coordonn�es Locales et Globales, demandez 
				moi de l'aide pour des explications si besoin)

			Deplacer la sprite (H�rit� de la classe Transformable)
				-> sprite.move(VotreDirection)	//Voir doc pour les types requis
				(Incr�mentation : utile pour les deplacements)
				ou 
				-> sprite.setPostition(VotrePosition)	//Voir doc pour les types requis
				(reecriture : utile pour les t�l�portations)

			Tourner la sprite (H�rit� de la classe Transformable)
				-> sprite.rotate(VotreRotation)	//Voir doc pour les types requis
				(Incr�mentation : utile pour les animations de rotation)
				ou
				-> sprite.setRotation(VotreRotation)	//Voir doc pour les types requis
				(reecriture : utile pour r�initialiser la rotation)

			Redimensionner la sprite (H�rit� de la classe Transformable)
				-> sprite.scale(vosFacteurs)	//Voir doc pour les types requis
				(Incr�mentation : utile pour les animations de taille)
				ou
				-> sprite.setScale(vosFacteurs)	//Voir doc pour les types requis
				(reecriture : utile pour r�initialiser une taille)
				

			...

		(Liste non exaustive)

		DOC :
		https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Sprite.php#aa795483096b90745b2e799532963e271
	
	*/
	Sprite sprite(texture);

	/*
	
		La classe Font permet de manipuler des polices d'ecriture
		
		En dehors d'utiliser la police pour �crire du texte, et du chargement de police,
		on ne peut pas la modifier.
		Seul la lecture d'informations particuli�res, comme les mesures en px de details,
		peut etre utile (et encore uniquement pour un usage esth�tique).

		ATTENTION :
			Les polices "bipmap" peuvent causer probl�me, cherchez une version vectorielle
			� la place

		DOC :
		https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Font.php

	*/
	Font font;
	//On charge la police, si ca marche, tout va bien, sinon on plante
	if (!font.loadFromFile("arial.ttf"))
		return EXIT_FAILURE;

	/*
	
		Affichage de Texte

		param�tres de constructeur : Texte � �crire, police, et taille en pixel d'un 
		caract�re (defaut � 30)
		text("Hello SFML", font, 50);

		Ce qu'on peut faire avec :
				
				Param�trer l'affichage des caract�res
					-> text.setCharacterSize(VotreDimension)	
								//Voir doc pour les types requis
					ou
					-> text.setLineSpacing(VotreDimension)	
								//Voir doc pour les types requis
					ou
					-> text.setLetterSpacing(VotreDimension)	
								//Voir doc pour les types requis
					...


				modifier l'aspect cosm�tique du texte
					-> text.setStyle(VotreStyle)	//Voir doc pour les types requis
					ou
					-> text.setColor(VotreCouleur)	//Voir doc pour les types requis
					...

			...

		(Liste non exaustive)

		DOC:
		https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Text.php
	*/
	Text text("Hello SFML", font, 50);

	/*
		La musique est une classe fille h�ritant d'un ensemble de classes
		Music -> SoundStream -> SoundSource -> AlResource (bas� sur openAL, voir doc)

		OpenAL permet de faire du son spacialis� dans un environement 3D, certaines 
		fonctions de cette classe vont dans ce sens (set/getPosition,
		setRelativeToListener, get/setMinDistance....). 


		Ce qu'on peut faire avec :
				
				g�rer une r�p�tition (utile pour les musiques d'embiance)
					-> music.setLoopPoints(votreParam)	//Voir doc pour les types requis
					ou
					-> music.getLoopPoints()

				Jouer la musique, la mettre en pause ou l'arreter et connaitre son �tat
				(utile par exemple pour arreter la musique d'embiance quand le menu est 
				ouvert)
					-> music.play(), music.pause(), music.stop()
					ou
					-> music.getStatus()

				att�nuer la musique (par exemple au travers d'un mur)
					-> music.setAttenuation(votreParam)	//Voir doc pour les types requis
					ou
					-> music.getAttenuation()

				...

		(Liste non exaustive)
	
		DOC :
		http://www.openal.org/
		https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Music.php
	*/
	Music music;
	if (!music.openFromFile("AMemoryAway.ogg"))
		return EXIT_FAILURE;
	music.play();

	// Vous pouvez instancier autant de choses que vous voulez ici
#pragma endregion


/*

		Boucle d'execution ou RunTime :

		C'est une boucle d'affichage qui s'execute � chaque image, ca peut etre � 60 
		executions par seconde par exemple...

*/
#pragma region RunTime

	while (window.isOpen())
	{
	/*
		
			Section Logique

			Tout ce qui concerne le traitement des inputs, d�placement des objets dans 
			la sc�ne et autre logique doit etre �crit avant l'affichage graphique du tout.
		
			Ce n'est pas obligatoire, c'est une bonne pratique. 

		*/
	#pragma region logique

		/*
		
			Dans le contexte de ce bete exercice,
			seul une gestion des �v�nements est n�c�ssaire.

			Dans un projet � plus grande echelle,
			de nombreuses actions sont ind�pendantes des inputs du jouers.

			ils seront g�r�s diff�rements du pattern suivant.

		*/
		#pragma region evenements

				/*
				
					Classe Event

					Classe m�re de tous les �v�nements possibles


					les sources d'�v�nement sont :
						joystik (input, connection...), clavier, sourie(click, mouvement, 
						molette), capteurs en tout genre, la fenetre en elle meme 
						(redimension, saisie de texte, touch�) ... (non exaustif)


					Usage et fonctionnement des �v�nements :
						d�taill� dans le commentaire en dessous 


					La liste exacte des type d'�v�nement est :
						
							Closed			(�mit � la fermeture de la fenetre)
								
							Resized			(�mit quand la fenetre est redimenssionn�e)
							
							LostFocus		(�mit si l'utilisateur clique en dehors de 
											la fenetre)
							
							GainedFocus		(�mit apr�s un LostFocus si l'utilisateur 
											reclique sur la fenetre)
							
							TextEntered		(�mit quand un caract�re est tap�)
							
							KeyPressed		(�mit quand une touche est appuy�e)

							KeyReleased		(�mit quand une touche est relach�e)
							
							MouseWheelMoved			(NE PAS UTILISER, cet event va etre 
													supprim� dans les prochaines 
													versions)
							
							MouseWheelScrolled		(�mit au scroll de la molette)

							MouseButtonPressed		(�mit quand le bouton de la sourie 
													est appuy�e)
							
							MouseButtonReleased		(�mit quand le bouton de la sourie 
													est relach�e)
							
							MouseMoved		(�mit au d�placement de sourie)
							
							MouseEntered	(�mit quand la sourie entre dans le cadre de 
											la fenetre)

							MouseLeft		(�mit quand la sourie sors du le cadre de la 
											fenetre)
							
							JoystickButtonPressed	(�mit quand un bouton du joystick
													est appuy�)
							
							JoystickButtonReleased	(�mit quand un bouton du joystick 
													est relach�)

							joystickMoved		(�mit quand un joystick se deplace sur un
												axe)
													
							JoystickConnected		(�mit quand un joystick est connect�)
													
							JoystickDisconnected	(�mit quand un joystick est
													d�connect�)
													
							TouchBegan		(�mit quand quelqu'un pose un doigt sur une 
											surface tactile)
													
							TouchMoved		(�mit quand quelqu'un deplace un doigt sur 
											une surface tactile)
													
							TouchEnded		(�mit quand quelqu'un enl�ve un doigt d'une 
											surface tactile)
													
							SensorChanged	(�mit quand la valeur d'un capteur change)
													
							Count			(retourne le nombre de type d'Event...
											inutile ?)

					Les types sont obtenus avec Event::EventType et chaque �v�nement a son
					type d�finis dans event.type 

					(PS, certains �v�nements incluent des informations, voir DOC)

					DOC:
					https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Event.php#af41fa9ed45c02449030699f671331d4aa67fd26d7e520bc6722db3ff47ef24941
				
				*/
				Event event;
				/*
					
					Traitement des �v�nements

					general :

						Lorsqu'un �v�nement a lieux, il est stock� dans une liste 
						d'Events. la fonction window.pollEvent(event) r�cup�re le premier 
						evenement  de cette liste et le met dans la variable event. S'il
						n'y a pas d'�v�nements � traiter, elle retourne false.

					le principe du while :

						Ce pattern de while(window.pollEvent(event)) permet de traiter 
						chaque �v�nements intervenu depuis l'execution pr�c�dente s'il 
						y en a eu.

					l'interrieur du while :

						On devrait utiliser un switch pour tester toutes les valeurs
						possible pour le type d'�v�nement afin de traiter tous les 
						�v�nements possibles.
					
				*/
				while (window.pollEvent(event))
				{

					// Fermeture de la fen�tre  => fin du programme
					if (event.type == Event::Closed)
						window.close();
				}


		#pragma endregion


	#pragma endregion



	/*
		
		Section graphique

		Apr�s avoir choisi ou se trouvent les �l�ments de la sc�ne � l'instant T,
		on peut les afficher.

		Une solution a essayer :
			utiliser des tableaux qui identifient les plans de votre sc�ne et
			dont l'index d�finis leur priorit� d'affichage.
			Puis dessiner les �l�ments � l'interrieur d'une boucle for.

	*/
	#pragma region graphique


			/*
				Efface la scene precedente

				On remplace alors toute la fenetre par une seule couleur
				Par defaut c'est noir.

			*/
			window.clear();

			/*
				Dessin de tout les �l�ments qui h�ritent de la Classe drawable

				ATTENTION !
					Plus un �l�ment est appel� tot dans l'ordre des draw, plus 
					il risque d'etre masqu� par d'autres �l�ments.

					par exemple, le ciel/arri�rePlan doit toujours etre dessin� en premier 
					et (sauf cas exceptionnel) l'interface utilisateur en dernier.

			*/
			window.draw(sprite);
			window.draw(text);
		
			//Met a jour la fenetre
			window.display();

	#pragma endregion

	}
	//fin de programme
	return EXIT_SUCCESS;
#pragma endregion
}
