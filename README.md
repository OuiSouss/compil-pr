Mini-projet de compilation:

De Pichon Alexis et Risi Amélie, Groupe A3

Objectif : 
- Créer un interpréteur du langage IMP : fait
- Créer un interpréteur du langage C3A : non fait
- Créer un traducteur de IMP à C3A : fait mais petits problèmes persistants
- Créer un traducteur de C3A à Y86 : non fait

Structure des fichiers :


Voici donc la structure de fichiers utilisée:

-iimp.l : correspond au lexer qui nous permet de spécifier le comportement lors de la lecture d'une commande. Exemple: X1:=X2

-iimp.y : Notre parser qui spécifie la grammaire de IMP. Utilisation du module environ qui nous permet de gérer l'envionnement sous lequel on se trouve. De plus, nous utilisons un autre module qui nous transforme une commande en arbre. 

- Module environ : Fichiers fourni pour le mini-projet

- Module node : Structure de donnée : Arbre d'analyse syntaxique

	Il gère donc des noeuds qui sont soit de type : 
		- constante, un entier, ex : 10
		- identifiant, une chaîne de caractères, ex : X2
		- opérateur, un entier ( Af, Pl, Mo...), son nombre de paramètre et ses paramètres.

- Module Evalexpr :
  Module de gestion de l'environnement et de l'AST.


- Ast.c : 
   Fichier qui nous permet de gérer l'affichage de l'arbre syntaxique de la commande tapée.
   
- C3A.c : 
  Fichier qui gère l'affichage du code à trois addresse à partir de notre arbre syntaxique
  

Création de l'exécutable: 

	Dans le répertoire courant faire un: make
	
	Pour nettoyer les fichiers intermédiares : make clean
	
L'exécutable créé s'appelle : iimp

Problème rencontrés et persistants :

	- Modules environ et bilquad pas très clair. Et ils nous ont créer des erreurs de segmentations, que nous avons réglés.
	- Le choix d'utiliser une structure node s'est imposé à nous car l'utilisation de bilquad aurait été fastidieuse.
	- Passage au C3A complique: problème non résolu
		Nous avons réussi à gérer seulement le cas de l'affectation sur constante.
	- Le passage au C3A n'est pas fonctionnel comme demandé car nous avons perdu beaucoup de temps à essayer d'affecter les variables au moment de leur apparition (pour une constante, mise dans un registre au cours d'une opération insérée par précédence ; pour les variables de type X1, ..., de la même façon nous avons perdu du temps à essayer de les affecter au préalable lorsqu'on les rencontre si elles ne sont pas affectées à ce moment).
	
	
