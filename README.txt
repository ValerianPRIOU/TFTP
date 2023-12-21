Rapport d'étonnement:

Notre gettftp fonctionne malgré les erreures corrigées. Nous avons commencer à implémenter puttftp.
Ce TP nous a permis de bien comprendre la logique de la manipulation des sockets et la gestion des paquets réseau. Nous avons également pris en compétence sur la gestion d'erreurs réseau.





Erreurs rencontrées et résolutions:


Difficultés initiales dans la création et l'envoi de paquets correctement formatés, notamment la gestion correcte de la concaténation des chaînes de caractères.
Problèmes de synchronisation lors de la réception des acquittements (ACK).
Erreurs de segmentation dues à une mauvaise gestion de la mémoire lors de la création des paquets.

Problème de connexion au serveur: Initialement, le client ne parvenait pas à établir une connexion stable avec le serveur TFTP. Résolution: Modification des paramètres de socket pour garantir une compatibilité accrue avec notre serveur.
Gestion incorrecte des numéros de blocs: Les numéros de blocs n'étaient pas toujours correctement incrémentés. Résolution: Révision de la logique d'incrément des numéros de blocs pour assurer la cohérence avec la spécification TFTP.