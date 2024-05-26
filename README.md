[![CMake](https://github.com/CandasKat/http_curl_wrapper/actions/workflows/msvc.yml/badge.svg)](https://github.com/CandasKat/http_curl_wrapper/actions/workflows/msvc.yml)

I recommend to use Clion for compile the project.

For install compilers:

```bash
sudo apt install cmake gcc g++
```

For install cURL:

```bash
sudo apt install curl
sudo apt install libssl-dev libcurl4-openssl-dev
```


For Windows:
I recommend to use Visual Studio for compile the project, and you can use vcpkg for install the dependencies.

For install vcpkg:

```bash
git clone https://github.com/microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat
```


For install Curl:

```bash
.\vcpkg\vcpkg install curl:x64-windows
.\vcpkg\vcpkg integrate install
```


For install Google Test:

```bash
.\vcpkg\vcpkg install gtest:x64-windows
```

And you can use the CMakeLists.txt file for compile the project.
For execute the project you need to use http_curl_wrapper_test.exe (tst\http_curl_wrapper_tst.exe)._

Analyse de Code

Nous avons effectué deux analyses de code distinctes en utilisant l'outil cppcheck en raison de problèmes pour trouver les fichiers d'en-tête de certaines bibliothèques tierces. Les résultats de ces analyses sont documentés comme suit :

Analyse Complète Incluant les Bibliothèques Tierces :

La première analyse inclut les bibliothèques tierces et peut être consultée dans code-analyses/all/index.html.
Cette analyse fournit une vue d'ensemble complète, incluant les bibliothèques dont nous dépendons.
Analyse de Notre Code Uniquement :
![image](https://github.com/CandasKat/http_curl_wrapper/assets/91725854/9ebf5715-bff8-415b-a2a9-12bfc8fd2352)


La seconde analyse se concentre uniquement sur le code que nous avons écrit, en excluant les bibliothèques tierces. Les résultats peuvent être consultés dans code-analyses/src-tst/index.html.
Cette analyse est plus ciblée et nous permet de nous concentrer sur la qualité de notre code sans influences externes:
![image](https://github.com/CandasKat/http_curl_wrapper/assets/91725854/d5d303c3-737a-4391-96f0-e83f95761ce4)


Conclusions

Sur la base de ces analyses, nous avons tiré les conclusions suivantes :
Structure Générale : Notre application semble bien structurée dans l'ensemble.
Bibliothèques Tierces : Il est crucial de s'assurer que les bibliothèques tierces sont fiables et maintenues à jour.
Réduction des Dépendances : Réduire autant que possible les dépendances est bénéfique. Par exemple, nous pourrions utiliser des structures de données standard comme map au lieu de dépendre d'une bibliothèque pour les structures JSON.
