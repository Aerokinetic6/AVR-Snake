Snake is moving.
snake nevű tömb representálja x és y tömbök pedig a poziciókat tárolják

nxt_x és nxt_y követik nyomon realtime, h a fej (az aktuális first) hol van ill hova kell kerüljön bill leütés esetén,
melyet a next_pos() fv számít ki.

alapvetően csak az utolsó szelvényt (last) pozicionáljuk át a next xy helyre. így az utolsóból első lesz, az 
utolsó előttiből pedig utolsó. 

ezzel a módszerrel csak arra van szükségünk, h a snake reprezentáló tömb mindenkor aktuális első és utolós elemét 
meg tudjuk jelölni. 
a last indexen tárolt érték fogja kijelölni ezután, h az x és y tömbökben tárolt koordináták közül meik az utolsó. 
ha ze meg van ezen a pozición lévő karaktert töröljük ill. a kiszámított nxt xy helyre kirajzolunk egy újat
(végeredményben így olyan mintha átrajzoltuk volna az utolós szelvényt oda ahova lépnie kell a fejnek) 

ez annyiban merül ki, h inicializálás után az utolsóelőtti ([last+1]) lesz a last és 

-------------

lényegiben az történik h a fejet követjük nxt xy változókkal és oda fogunk új elemet kirajzoltatni (ill. előzőleg 
letárolni (felülírni) ezt az új poziciót x és y tömbökbe, méghozzá a [first] indexre, ami eddig a last vt (de mivel
a lastot töröljük, ezért a hozzá tartozó x y koordinátákat írjuk felül ))

végül a tömbnek mindig 1ik eleme az utolsó amit törlünk a másik az első amit kirajzolunk a többi pedig a helyén marad.
és az egész eggyel arréb shiftelődik a kövi körre mígnem körbe nem ér és kezdődik előlről. -> rotálás
