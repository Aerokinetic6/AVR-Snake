random poz generálás műxik -> place_rnd()
rnd_cntr folyamatosan pörög annak %4 ill %16 maradéka lesz a rnd_xy koord.ja
chch_new() ellenőrzi, h elérte e a nxt_yx a rnd_yx poz.ót,
ha igen új rnd poz generálódik place_rnd();-vel
aránylag véletlenszerűnek tűnik rnd_cnt értéke ezen események bekövetkeztekor
holott cnt=100-nál lehet midnig csak place_rnd() esemény 
(vszeg azért nem baj mert cnt csak 100ig pörög, míg rnd_cnt 255nél fordul át,
íyg a kettő nincs szinkronban, bár magában hordozza a lehetőséget, h roudnrobin 
szerű rnd szám generálást biztosít csak -> ki kéne számolni)
