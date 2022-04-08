PUT (nb : quand un joueur pose une carte, il faut l'ajouter à la liste playedCards de room. + verifier que la room a bien à state == à PLAY)
max 5 vies + 3 shurikens
Changer la seed du shuffle random

mettre des logs (afficher qui fait quoi)
verfifer les argument (bon nombre, valeur acceptable)
mettre des mutex pour protéger la liste de clients globale et des rooms (pour éviter les problèmes de connexions et de joins simultanés).
gérer les ACK
Verifier la creation de plustieurs salles d'affilé (déjà en cours de jeu ??)