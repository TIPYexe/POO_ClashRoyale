# POO_ClashRoyale

# Recomandari:
  - MinGW v8
  - C++ 17
  - rulati programul din consola sau powershell (fie din CodeBlocks fie din consola direct)
      - g++ sa fie adaugat in PATH
      - comanda: g++ -std=c++17 *.cpp -o NumeFisier -pthread
  - am lasat doar doua personaje pentru ca intre ele se termina batalia in cel mai rezonabil timp;

# Programul contine
  - multi-threading pentru fiecare personaj si turn in parte, si pentru afisarea hartii;
  - functie virtuala (printElixir);
  - mosteniri (clasa Side mosteneste clasa Personaj si clasa Elixir);
  - factory cu metode statice;  
  - smart pointers: Lista de tipuri de Personaje este unique_ptr;
  - exceptii;
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

