#  Sistem de Gestiune a unei Cafenele

## Programul simulează gestiunea unei cafenele.


## Componentele sistemului
- **Stoc de ingrediente:** Urmărește resursele disponibile (cafea, lapte, sirop etc.), cantitățile curente, unitățile de măsură și costurile unitare de achiziție.
- **Catalog de rețete:** Definește băuturile disponibile (Espresso, Cappuccino, Vanilla Latte etc.), ingredientele necesare preparării și prețul de vânzare.
- **Balanță financiară:** Actualizată automat (crește la vânzarea produselor și scade la achiziția/reaprovizionarea ingredientelor).
- **Clienți și fidelitate:** Evidență a comenzilor per client, calcul al sumelor cheltuite și acumulare de puncte de fidelitate.
- **Istoric și rapoarte:** Păstrarea comenzilor finalizate, calculul statisticilor de rentabilitate și persistența datelor prin salvare în fișiere.

---

## Meniu și funcționalități
1. **Stare cafenea:** Afișează stocurile curente de ingrediente, soldul financiar și catalogul de rețete.
2. **Comandă Espresso:** Prepară și vinde un Espresso, actualizând stocurile și balanța.
3. **Comandă Cappuccino:** Prepară și vinde un Cappuccino, actualizând stocurile și balanța.
4. **Comandă Vanilla Latte:** Prepară și vinde un Vanilla Latte, actualizând stocurile și balanța.
5. **Verificare disponibilitate:** Verifică dacă există suficiente ingrediente în stoc pentru o băutură specificată.
6. **Raport de rentabilitate:** Afișează indicatorii financiari și marja de profit.
7. **Reaprovizionare ingredient:** Adaugă stoc suplimentar pentru un ingredient ales, scăzând costul din fondurile cafenelei.
8. **Comandă client (multi-produs):** Permite înregistrarea unei comenzi complexe cu mai multe produse, asociată unui cont de client.
9. **Clienți și niveluri fidelitate:** Afișează lista clienților, sumele totale cheltuite și punctele acumulate.
10. **Istoric vânzări:** Listează tranzacțiile și comenzile procesate anterior.
11. **Salvare raport în fișier:** Exportă istoricul și statisticile de vânzare într-un fișier text extern.
0. **Ieșire:** Încheie execuția programului.
Gestiune clienți: Vizualizarea bazei de date cu clienți și a nivelurilor de fidelitate asociate.

Istoric și persistență: Consultarea istoricului detaliat al comenzilor finalizate și exportarea raportului complet de vânzări într-un fișier extern.
