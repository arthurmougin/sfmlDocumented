/*


			Bienvenue sur le Projet d'Arthur Mougin


	Principe :

			C'est un code fonctionnel ou chaque fonction est documentée.
			De plus, même la structure est commentée.


	Comment l'utiliser :

			1) Réduisez tout les commentaires en minuscule pour voir le 
			code brute.

			2) réduisez les pragma pour voir les différentes section de code
			
			3) Ouvrez les pragma et les commentaires qui vous interessent pour
			lire la documentation


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
		Initialisation :

		Comme un programme normal, on commence ici par créer les éléments à utiliser 
		durant la boucle d'execution.
	
		C'est la partie qui s'execute derrière le chargement initial d'un jeu ou d'un 
		programme.
*/
#pragma region Initialisation
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
				
				Paramêtrer l'affichage des caractères
					-> text.setCharacterSize(VotreDimension)	
								//Voir doc pour les types requis
					ou
					-> text.setLineSpacing(VotreDimension)	
								//Voir doc pour les types requis
					ou
					-> text.setLetterSpacing(VotreDimension)	
								//Voir doc pour les types requis
					...


				modifier l'aspect cosmétique du texte
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
		La musique est une classe fille héritant d'un ensemble de classes
		Music -> SoundStream -> SoundSource -> AlResource (basé sur openAL, voir doc)

		OpenAL permet de faire du son spacialisé dans un environement 3D, certaines 
		fonctions de cette classe vont dans ce sens (set/getPosition,
		setRelativeToListener, get/setMinDistance....). 


		Ce qu'on peut faire avec :
				
				gérer une répétition (utile pour les musiques d'embiance)
					-> music.setLoopPoints(votreParam)	//Voir doc pour les types requis
					ou
					-> music.getLoopPoints()

				Jouer la musique, la mettre en pause ou l'arreter et connaitre son état
				(utile par exemple pour arreter la musique d'embiance quand le menu est 
				ouvert)
					-> music.play(), music.pause(), music.stop()
					ou
					-> music.getStatus()

				atténuer la musique (par exemple au travers d'un mur)
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

		C'est une boucle d'affichage qui s'execute à chaque image, ca peut etre à 60 
		executions par seconde par exemple...

*/
#pragma region RunTime

	while (window.isOpen())
	{
	/*
		
			Section Logique

			Tout ce qui concerne le traitement des inputs, déplacement des objets dans 
			la scène et autre logique doit etre écrit avant l'affichage graphique du tout.
		
			Ce n'est pas obligatoire, c'est une bonne pratique. 

		*/
	#pragma region logique

		/*
		
			Dans le contexte de ce bete exercice,
			seul une gestion des événements est nécéssaire.

			Dans un projet à plus grande echelle,
			de nombreuses actions sont indépendantes des inputs du jouers.

			ils seront gérés différements du pattern suivant.

		*/
		#pragma region evenements

				/*
				
					Classe Event

					Classe mère de tous les événements possibles


					les sources d'événement sont :
						joystik (input, connection...), clavier, sourie(click, mouvement, 
						molette), capteurs en tout genre, la fenetre en elle meme 
						(redimension, saisie de texte, touché) ... (non exaustif)


					Usage et fonctionnement des événements :
						détaillé dans le commentaire en dessous 


					La liste exacte des type d'événement est :
						
							Closed			(émit à la fermeture de la fenetre)
								
							Resized			(émit quand la fenetre est redimenssionnée)
							
							LostFocus		(émit si l'utilisateur clique en dehors de 
											la fenetre)
							
							GainedFocus		(émit après un LostFocus si l'utilisateur 
											reclique sur la fenetre)
							
							TextEntered		(émit quand un caractère est tapé)
							
							KeyPressed		(émit quand une touche est appuyée)

							KeyReleased		(émit quand une touche est relachée)
							
							MouseWheelMoved			(NE PAS UTILISER, cet event va etre 
													supprimé dans les prochaines 
													versions)
							
							MouseWheelScrolled		(émit au scroll de la molette)

							MouseButtonPressed		(émit quand le bouton de la sourie 
													est appuyée)
							
							MouseButtonReleased		(émit quand le bouton de la sourie 
													est relachée)
							
							MouseMoved		(émit au déplacement de sourie)
							
							MouseEntered	(émit quand la sourie entre dans le cadre de 
											la fenetre)

							MouseLeft		(émit quand la sourie sors du le cadre de la 
											fenetre)
							
							JoystickButtonPressed	(émit quand un bouton du joystick
													est appuyé)
							
							JoystickButtonReleased	(émit quand un bouton du joystick 
													est relaché)

							joystickMoved		(émit quand un joystick se deplace sur un
												axe)
													
							JoystickConnected		(émit quand un joystick est connecté)
													
							JoystickDisconnected	(émit quand un joystick est
													déconnecté)
													
							TouchBegan		(émit quand quelqu'un pose un doigt sur une 
											surface tactile)
													
							TouchMoved		(émit quand quelqu'un deplace un doigt sur 
											une surface tactile)
													
							TouchEnded		(émit quand quelqu'un enlève un doigt d'une 
											surface tactile)
													
							SensorChanged	(émit quand la valeur d'un capteur change)
													
							Count			(retourne le nombre de type d'Event...
											inutile ?)

					Les types sont obtenus avec Event::EventType et chaque événement a son
					type définis dans event.type 

					(PS, certains événements incluent des informations, voir DOC)

					DOC:
					https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Event.php#af41fa9ed45c02449030699f671331d4aa67fd26d7e520bc6722db3ff47ef24941
				
				*/
				Event event;
				/*
					
					Traitement des événements

					general :

						Lorsqu'un événement a lieux, il est stocké dans une liste 
						d'Events. la fonction window.pollEvent(event) récupère le premier 
						evenement  de cette liste et le met dans la variable event. S'il
						n'y a pas d'événements à traiter, elle retourne false.

					le principe du while :

						Ce pattern de while(window.pollEvent(event)) permet de traiter 
						chaque événements intervenu depuis l'execution précédente s'il 
						y en a eu.

					l'interrieur du while :

						On devrait utiliser un switch pour tester toutes les valeurs
						possible pour le type d'événement afin de traiter tous les 
						événements possibles.
					
				*/
				while (window.pollEvent(event))
				{

					// Fermeture de la fenêtre  => fin du programme
					if (event.type == Event::Closed)
						window.close();
				}


		#pragma endregion


	#pragma endregion



	/*
		
		Section graphique

		Après avoir choisi ou se trouvent les éléments de la scène à l'instant T,
		on peut les afficher.

		Une solution a essayer :
			utiliser des tableaux qui identifient les plans de votre scène et
			dont l'index définis leur priorité d'affichage.
			Puis dessiner les éléments à l'interrieur d'une boucle for.

	*/
	#pragma region graphique


			/*
				Efface la scene precedente

				On remplace alors toute la fenetre par une seule couleur
				Par defaut c'est noir.

			*/
			window.clear();

			/*
				Dessin de tout les éléments qui héritent de la Classe drawable

				ATTENTION !
					Plus un élément est appelé tot dans l'ordre des draw, plus 
					il risque d'etre masqué par d'autres éléments.

					par exemple, le ciel/arrièrePlan doit toujours etre dessiné en premier 
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
