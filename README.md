# Deck Builder Mage Noir

Salut ... 

Bon je vous explique le contexte, en gros je suis fan du jeu Mage noire et comme il n'y avait pas de deck builder pour ce jeu, j'ai décidé de le faire moi-même.

De plus c'était un rendu de projet pour ma formation. Donc j'en ai profité pour faire un projet qui me plaisait.

Voilà donc SVP, soyez indulgent, je l'ai fait en 2 jours, et je pense (je ne promets rien) que je vais l'améliorer au fur et à mesure.

Je tiens à préciser que ce projet est strictement personnel. Bien que j'apprécie beaucoup le jeu, je n'ai aucun lien avec l'éditeur de Mage Noir.

Je vous remercie d'avance pour votre gentillesse.

## Installation
    Vu que je suis sur Ubuntu, je vais juste montrer la compilation pour ce système d'exploitation.

```bash
sudo apt-get install qt5-default

or

sudo apt install qtbase5-dev

sudo apt-get install cmake

cmake

make

./DeckBuilderMageNoir
```

Ah oui les dossiers "images" et "Data" doivent être dans le même répertoire que l'exécutable.

Je sais qu'il n'y a pas les images des cartes, vous pouvez les téléchargers sur le site officiel de Mage Noire 'https://magenoir.com/collection_fr.html'

## Utilisation
````
- 3 menues sont disponibles:
    - Menu principal
    - Menu de création de deck
    - Menu de visualisation des cartes
````
````
- Menu principal:
    - Permets de choisir entre les 2 autres menus
````

````
- Menu de création de deck:
    - Permets de choisir les cartes à ajouter au deck

Ajout d'une carte :
- Double-clique sur une carte dans la liste de gauche 
- Clique sur le bouton "Ajouter" après avoir sélectionné une carte
- La carte est ajoutée à la liste de droite

Suppression d'une carte :
- Double-clique sur une carte dans la liste de droite
- Cliquer sur le bouton "Supprimer" après avoir sélectionné une carte
- La carte est supprimée de la liste de droite
    
    
Ah oui, il y a aussi un filtre rudimentaire pour les cartes, il suffit de taper:
- le nom de la carte dans le champ de recherches
- ou/et cocher l'élément de la carte au-dessus du champ de recherche


Une fois que vous avez fini de créer votre deck, il suffit de cliquer sur le bouton "Sauvegarder" pour enregistrer le deck
- Un fichier .json est créé où vous souhaitez enregistrer le deck
- Vous pouvez aussi charger un deck en cliquant sur le bouton "Charger"
- pareil vous passez le chemin du fichier .json

````

````
- Menu de visualisation de deck:
    - Permets de visualiser les cartes du deck
    (je sais c'est un peu inutile, mais je voulais juste tester comment fonctionne Qt)

````

## Contributing

Bah si vous voulez contribuer, je suis ouvert à toute proposition.

Mais vous attendez pas à une réponse rapide, je suis un peu lent.

## License

Comment on met une licence, les copains ?
C'est obligatoire ?

## Remerciements

- Merci à moi-même pour avoir fait ce projet
- Merci à Double Combo Games pour avoir créé Mage Noir
- Merci à vous pour avoir lu ce README.md
