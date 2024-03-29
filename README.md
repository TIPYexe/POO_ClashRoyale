[![en](https://img.shields.io/badge/lang-en-red.svg)](https://github.com/TIPYexe/POO_ClashRoyale/blob/master/README.en.md)
[![ro](https://img.shields.io/badge/lang-ro-green.svg)](https://github.com/TIPYexe/POO_ClashRoyale/blob/master/README.md)

# 2D Clash Royale | Programare Orientata pe Obiecte | C++

In acest proiect am implementat o versiune simplificata a jocului [Clash Royale](https://supercell.com/en/games/clashroyale/). Am pastrat toate regulile din joc, dar am limitat numarul de entitati de pe campul de lupta si am implementat doar o parte dintre caractere.

# Recomandari:
  - MinGW v8
  - C++ 17
  - rulati programul din consola sau powershell (fie din CodeBlocks fie din consola direct)
      - g++ sa fie adaugat in PATH
      - comanda: g++ -std=c++17 *.cpp -o NumeFisier -pthread
  - am lasat doar doua personaje pentru ca intre ele se termina batalia in cel mai rezonabil timp;

# Programul contine
  - [multi-threading](https://github.com/TIPYexe/POO_ClashRoyale/blob/main/ConsoleApplication1.cpp#L61-L67) pentru fiecare personaj si turn in parte, si pentru afisarea hartii;
  - functie virtuala ([Elixir::printElixir](https://github.com/TIPYexe/POO_ClashRoyale/blob/e68358130cd3d86c33fa093938a929d9d68237fe/Elixir.cpp#L21-L23) [Side::printElixir](https://github.com/TIPYexe/POO_ClashRoyale/blob/main/Side.cpp#L45-L50));
  - mosteniri (clasa Side [mosteneste clasa Personaj si clasa Elixir](https://github.com/TIPYexe/POO_ClashRoyale/blob/main/Side.h#L9));
  - [factory](https://github.com/TIPYexe/POO_ClashRoyale/blob/main/Personaj_factory.h#L8-L14) cu metode statice;  
  - smart pointers: [Lista de tipuri de Personaje este unique_ptr](https://github.com/TIPYexe/POO_ClashRoyale/blob/main/ConsoleApplication1.cpp#L16);
  - [exceptii](https://github.com/TIPYexe/POO_ClashRoyale/blob/main/ConsoleApplication1.cpp#L41-L53);
  - definire clase, constructori, creare metode;
  
# Rules
  - echipa Friendly pleaca din stanga hartii (deci Enemy din dreapta);
  - fiecare echipa este compusa din cate un turn si un personaj ales random dintre cele disponibile;
  - fiecare echipa poate strange pana la maxim 10 elixir;
  - jocul se incheie atunci cand se darama un turn, sau cand sunt ambele personaje moarte in acelasi timp;
  
    ## Caractere
        - fiecare personaj este unic: prin HP, pauza dintre atacuri, puterea atacului, range-ul de atac;
        - unele persoanje merg pe pamant, iar altele zboara (niciuna nu le face pe amandoua);
        - unele personaje le pot ataca doar pe cele terestre, in timp ce altele pot si aerian (niciuna nu poate ataca doar personaje zburatoare);
        - personajele stiu sa mearga intr-o singura directie (deci nu se pot intoarce dupa persoanjul inamic, in cazul in care acesta trece pe langa ele);
  
    ## Turnuri
        - turnurile ambelor echipe sunt identice: putere de atac, pauza intre atacui si range-ul de atac;
        - nu isi pot ataca membrii echipei (fara friendly fire);
        - nu-si pot schimba pozitia;
  
    ## Elixir
        - elixirul creste cu 0.35/s;
        - cu elixirul poate fi cumparat un nou personaj de acelasi fel cu cel de inceput, 
          dar numai atunci cand moare celalalt (deci nu putem avea 2 personaje la aceeasi echipa simultan);

