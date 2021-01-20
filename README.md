# POO_ClashRoyale

# Recomandari:
  - MinGW v8
  - C++ 17
  - rulati programul din consola sau powershell (fie din CodeBlocks fie din consola direct)
      - g++ sa fie adaugat in PATH
      - comanda: g++ -std=c++17 *.cpp -o NumeFisier -pthread

# Programul contine
  - multi-threading pentru fiecare personaj si turn in parte, si pentru afisarea hartii;
  - mosteniri (clasa Side mosteneste clasa Personaj);
  - clasa factory cu metode statice;  
  - smart pointers: Lista de tipuri de Personaje este unique_ptr;
  - exceptii;
  - definire clase, constructori, creare metode;
  
# Rules
  - echipa Friendly pleaca din dreapta hartii (deci Enemy din stanga);
  - fiecare echipa este compusa din cate un turn si un personaj ales random dintre cele disponibile;
  
  ## Caractere
  - fiecare personaj este unic: prin HP, pauza dintre atacuri, puterea atacului, range-ul de atac;
  - unele persoanje merg pe pamant, iar altele zboara (niciuna nu le face pe amandoua);
  - unele personaje le pot ataca doar pe cele terestre, in timp ce altele pot si aerian (niciuna nu poate ataca doar personaje zburatoare);
  - personajele stiu sa mearga intr-o singura directie (deci nu se pot intoarce dupa persoanjul inamic, in cazul in care acesta trece pe langa ele);
  
  ## Turnuri
  - turnurile ambelor echipe sunt identice: putere de atac, pauza intre atacui si range-ul de atac;
  - nu isi pot ataca membrii echipei (fara friendly fire);
  - nu-si pot schimba pozitia;
  


