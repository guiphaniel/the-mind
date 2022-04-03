# The Mind
Ce projet est un portage du jeu de société `The Mind`, par Guilhem RICHAUD et Baptiste STUBLJAR, pour le projet de Client-Serveur du Semestre 4 réalisé à l'IUT Lyon 1 (site de Bourg-en-Bresse) en 2022. 

Vous trouverez ici le code source pour le serveur, en C++. Le code source du client Android est disponible ici : https://github.com/baptistestubljar/theMind-Client

## Installation
* Protobuf : résumé d'installation (https://github.com/protocolbuffers/protobuf/blob/main/src/README.md)
  * Installer les outils nécessaires :

        sudo apt-get install autoconf automake libtool curl make g++ unzip

  * Télécharger une des releases au format `protobuf-cpp-[VERSION].tar.gz` disponibles ici : https://github.com/protocolbuffers/protobuf/releases/latest
  * Afin de compiler et d'installer l'environnement d'exécution et le compilateur (protoc) de Protocol Buffer pour C++, exécuter les commandes suivantes :

        ./configure --prefix=/usr
        make -j$(nproc) # $(nproc) ensures it uses all cores for compilation
        make check
        sudo make install
        sudo ldconfig # refresh shared library cache.

* Recompiler les fichiers .proto dans `src/protos` :

        protoc -I=. --cpp_out=. nom_du_fichier.proto 

* Générer les fichiers Makefile du projet :

        qmake -o Makefile theMindServer.pro

* Compiler le projet :

        make