Alexandre Verkyndt
Anne-Sophie Saint-Omer

-> make
-> ./displaystack 


Appels de fonctions imbriquees

Numero de l'appel : 5
Valeur ESP : 0xbf888e30
Valeur EBP :0xbf888e48
---------------------
Numero de l'appel : 4
Valeur ESP : 0xbf888e10
Valeur EBP :0xbf888e28
---------------------
Numero de l'appel : 3
Valeur ESP : 0xbf888df0
Valeur EBP :0xbf888e08
---------------------
Numero de l'appel : 2
Valeur ESP : 0xbf888dd0
Valeur EBP :0xbf888de8
---------------------
Numero de l'appel : 1
Valeur ESP : 0xbf888db0
Valeur EBP :0xbf888dc8
---------------------
Numero de l'appel : 0
Valeur ESP : 0xbf888d90
Valeur EBP :0xbf888da8
---------------------

Appels de fonctions successifs

Numero de l'appel : 0
Valeur ESP : 0xbf888e30
Valeur EBP :0xbf888e48
---------------------
Numero de l'appel : 0
Valeur ESP : 0xbf888e30
Valeur EBP :0xbf888e48
---------------------
Numero de l'appel : 0
Valeur ESP : 0xbf888e30
Valeur EBP :0xbf888e48
---------------------
Numero de l'appel : 0
Valeur ESP : 0xbf888e30
Valeur EBP :0xbf888e48
---------------------
Numero de l'appel : 0
Valeur ESP : 0xbf888e30
Valeur EBP :0xbf888e48
---------------------

Explications :

Les variables locales sont dupliquées à chaque appel. Ces variables sont enregistrées dans le registre ESP. Elles ont une adresse au sommet de la pile.


Lors des appels successifs à une même fonction les valeurs de ESP et EBP restent identiques. 
Lors de l'execution de la fonction, cette derniere entre dans la pile et occupe donc une portion de la mémoire avec pour début EBP et pour position courante ESP. Une fois l'execution terminee elle libère l'espace qu'elle prenait dans la pile. Ce qui fait que lors d'un nouvel appel à cette même fonction, elle aura les mêmes valeurs ESP et EBP qui representent respectivement la position courante dans la pile et la base de la pile. 
En ce qui concerne les appels imbriqués, la fonction étant récursive, le contexte du premier appel ne  pourra seulement se libérer que lorsque tous les autres appels qui suivront seront terminés. Cela implique donc d'empiler chacun des contextes les uns après les autres. Les valeurs de EBP et ESP sont donc différentes.



