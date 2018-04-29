Alapfunkciók jól műxenek.
Megmaradt hiányosságok:
- Rnd koord generálás félkész
- kígyótestbe is kerül
- "hátraarc kivégzés"

Végül úgy lett megírva, h amikor rámegy a fej egy 'X'-re akkor nem nő meg egyből,
 csak a kövi körben, úgy, hogy az utolsó szelvény akkoron nem törlődik, csak egy
 plusz adódik hozzá (fejként), aképp, h a nxt_pos() koord-kra rajzolódik ki ill 
 snake_add() fv segítségével be insertáljuk mint új koord az x-y [] tömb párba, 
 h tartós legyen a hatás.
 
 a fenti hiányosságokon túl már csak extrák vannak mint menük, sebesség állítás
 pontszám kijelzés stb. de az alpjáték már majdnem kész.
