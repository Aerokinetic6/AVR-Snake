Snake is moving.
snake nevű tömb representálja x és y tömbök pedig a poziciókat tárolják

nxt_x és nxt_y követik nyomon realtime, h a fej (az aktuális first) hol van ill hova kell kerüljön bill leütés esetén, melyet a next_pos() fv számít ki.

alapvetően csak az utolsó szelvényt (last) pozicionáljuk át a next xy helyre. így az utolsóból első lesz, az utolsó előttiből pedig utolsó. 

ezzel a módszerrel csak arra van szükségünk, h a snake reprezentáló tömb mindenkor aktuális első és utolós elemét meg tudjuk jelölni