Updatelve lett a chck_new()

letisztultabb módszerrel, csak azt vizsgáljuk, h a kövi poz rnd_xy-nal egyezik-e
ha igen akkor még az új fej kirajzolása előtt számítunk egy újabb nxt_pos()-t mintha 
"tolná" maga előtt a megadott irányba a kígyó az új elemet.

Ezzel most rákanyarodáskor is működik a snake_add()

- fő gond, h felvételkor nincs lehetőség spontán irányváltásra, hanem, mindenképp
  a már megkezdett irányba történik a lépés onnan ahol rnd_xy le van helyezve
  (nxt_xy oda generálódik) és csak ezután lehet másmerre kanyarodni, ha akarunk

- a féregjárat effekt több kipróbálás után sem jelentkezett eddig, vszeg megszűnt,
  de továbbra is rejtélyes pontosan mi okozta, ezexerint annyi elmondható, h a 
  régi kissé kaotikus chck_new() eljárással vt összefüggésben a bug

- ha a farok mellett van közvetlen, ill. ha a farok úgymond átmegy 'X'-en
  lépéskor láthatalanná válhat az új szelvény
  ez elvileg megszűnne, ha a kígyótestbe nem generálódhatna rndom pos-ós 'X'
  bár ebbe nem vok biztos -> végig kell gondolni az eseteket
  
- rndm szám generálás továbbra is elégtelen (csak 16 poz váltakozik véletlenszerűen)
  


