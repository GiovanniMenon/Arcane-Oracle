<h1 align="center"> Arcane Oracle </h1>

---

<p align="center">
    <img src="Code/asset/Icon/icon.png" style="width:auto;height:200px">
</p>

--- 

Arcane Oracle è  un progetto sviluppato per il corso di Programmazione ad Oggetti dell'Universita' degli Studi di Padova nell'anno Accademico 2022/2023.

Arcane Oracle è una applicazione per la generazione di Carta da Gioco che utiliza  [DALL·E API](https://openai.com/product/dall-e-2) per la generazione delle immagini.

Il progetto è stato scritto in **C++** usando il **framework QT**.

Svolto in collaborazione con [Endi Hysa](https://github.com/EndyXVIII).

## Requirements

|              | Versione di Test |
|-------------:|------------------|
| OS           | Ubuntu 22.04|
| Compilatore  | GCC 11.3.0       |
| Framework Qt | 6.2.4            |
| Versione Qmake  | 3.1.0  |
| Build system | Qmake+make       |

Arcane Oracle fa utilizzo di due librerie esterne necessarie per la compilazione del programma:
- [jsonCpp](https://github.com/open-source-parsers/jsoncpp) 
- [libCurl](https://curl.se/libcurl/)

Il progetto compila ed esegue corretteamente su Linux.

## Building
Lo script [./install.sh](./code/install.sh) scarica le due librerie necessarie per la compilazione e successivamente compila il programma eseguendo **qmake** e  **make**.
> [./install.sh](./code/install.sh) non e' pensato per essere usato in sistemi Operativi diversi da Ubuntu (Versione di Test).
Nel caso si voglia compilare il programma in un altro SO (escluso Windows) si compili manualmente tramite **qmake** e  **make** (assicurandosi prima di rispettare i Requirements).  
## Disclaimer
Il progetto e' stato rilasciato sotto licenza [MIT](./LICENSE).
> Il progetto è condiviso pubblicamente per essere fonte di ispirazione e di comprensione sulle meccaniche del framework QT. 
Sconsigliamo il riutilizzo del codice a fine Universitario.
Non ci assumiamo nessuna responsabilita' per l'utilizzo del codice.





