## Tema 1

#### Cerințe
- [x] definirea a minim 3-4 clase folosind compunere cu clasele definite de voi; moștenirile nu se iau în considerare aici
- [x] constructori de inițializare cu parametri pentru fiecare clasă
- [x] pentru o aceeași (singură) clasă: constructor de copiere, operator= de copiere, destructor
- [x] operator<< pentru toate clasele pentru afișare (std::ostream) folosind compunere de apeluri cu operator<<
- [x] cât mai multe const (unde este cazul) și funcții private
- [x] implementarea a minim 3 funcții membru publice pentru funcționalități netriviale specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe
  - [x] nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector
- [x] scenariu de utilizare cu sens a claselor definite:
  - [x] crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
  - [x] vor fi adăugate în fișierul tastatura.txt DOAR exemple de date de intrare de la tastatură (dacă există); dacă aveți nevoie de date din fișiere, creați alte fișiere separat
- [x] minim 52-60% din codul propriu să fie C++; testele nu se pun
- [x] .gitattributes configurat corect (nu trebuie făcute modificări aici)
- [x] tag de git: de exemplu v0.1
- [x] serviciu de integrare continuă (CI) cu toate bifele; exemplu: GitHub Actions
- [ ] code review #1 2 proiecte


## Descriere
- # Bobis Bob Caffe - Sistem de Gestiune a unei Cafenele


#### De ce am ales această tema?
Am ales gestionarea unei cafenele deoarece mi s-a părut o provocare interesanta si un context foarte intuitiv pentru a aprofunda conceptele fundamentale de OOP. O astfel de aplicație modelează scenarii reale din viața de zi cu zi și a reprezentat o oportunitate excelentă de a mă familiariza cu:
- **Separarea logicii în clase:** Încapsularea stocurilor (`Ingrediente`), a compoziției produselor (`CReteta`), a băuturilor finale (`Reteta`) și a logicii de business (`Cafenea`).
- **Relații de compunere între clase:** Construirea unor structuri complexe fără moștenire, exclusiv prin agregare și compunere de obiecte definite de mine.
- **Gestiunea manuală a resurselor:** Alocare dinamică de memorie, redimensionare manuală de tablouri dinamice (atât pentru ingrediente, cât și pentru catalogul de rețete) și respectarea *Rule of Three* (constructor de copiere, `operator=` de copiere și destructor) pentru a preveni memory leak-urile.

#### Ce își propune să implementeze proiectul?
Aplicația simulează fluxul operațional complet al unei cafenele:
1. **Evidența stocurilor de materie primă:** Monitorizarea ingredientelor disponibile (cantitate, unitate de măsură, cost unitar de achiziție) și posibilitatea de reaprovizionare.
2. **Catalog de produse/rețete:** Definirea băuturilor pe baza ingredientelor necesare și a prețului de vânzare.
3. **Procesarea comenzilor:** Verificarea automată a stocurilor înainte de preparare, scăderea resurselor consumate și încasarea banilor (actualizarea balanței financiare).
4. **Analiză de rentabilitate:** Calculul costului de producție pentru fiecare rețetă raportat la stocul curent, afișarea profitului net per produs și a marjei procentuale de profit.
5. **Meniu interactiv:** O interfață simplă în consola pentru plasarea comenzilor și monitorizarea cafenelei, compatibila cu rularea demonstrativă din `tastatura.txt`.
