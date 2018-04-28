elég egy változó amiben az aktuális last le van tárolva. (lastban az utolsó szelvény koordinátáit tároló index 
van letáárolva, tehát last tképpen egy mutató féleség ami az x[] és y[] tömbnek vmely elemére mutat (azáltal, 
h tárolja az utolsó szelvény x-y tömb indexét, mint koord tároló cím) ). 
ennyit elég ismernünk plusz a kígyó aktuális hosszát (l) hogy tudjuk rotálni melyik az aktuális x[last] y[last] 
tároló index.
(first és snake[64] változók törölve mert feleslegesek.)

minden lépésnél előszőr: gotoyx(y[last], x[last])pozicón töröljük a kaarktert 
aztán next_pos(); számítása globális nxt_y és nxt_x változókba

mivel x[last]y[last] indexeken tárolt koordinájú karaktert töröltük ezért ez a pozició sem érdekes már számunkra 
(ott már nincs kígyó szelvény)!
Tehát erre a címre nyugodtan letárolhatjuk az újonnan keletkezett fej (first) koordinátákat ami nxt_y és nxt_x
(így nem kell új változókat és elemeket igénybe vennia  tömbben, ill a programban, hanem konzisztens marad)
ezáltal válik az eleddig x-y[last] tömbök ezen indexű eleme most a fej koordinátáit tároló elemmé.

természetesen a koord rögzítése után (v akár még előtte, mind1, a lényeg, h tároljuk le)
lcd-re is kirajzoltatjuk az új szelvényt: gotoyx_lcd(nxt_y, nxt_x);

ha a y-x[last]-ba tárolás is megtörtént, last ráálítjuk a kövi elemre (az eddigi utsóelőttire, lévén ő lett 
az utolsó!): 

last++; kivéve ha last == l, akkor újra last=0;

a többi x[]y[] koord így automatikusan shiftelődik egyet last irányába.
