main.c: Se citesc comenzi de la tastatura pana se citeste quit si se apeleaza
functiile corespunzatoare comenzilor
basic.c: Implementare comenzi edit, save
edit.c: Implementare comenzi insert, set, draw, fill
draw_functions.c: Functii pentru draw (line, tri, rect)

edit, save:
    Se citeste calea fisierului-imagine, se citeste/scrie header-ul fisierului,
    se aloca dinamic si se citeste/scrie matricea de pixeli
insert:
    Se citesc offset-ul, latimea, inaltimea si matricea de pixeli din fisierul
    imaginii ce trebuie inserate. Se pleaca de la pozitia data si se copiaza
    pixelii din imaginea de inserat pana aceasta se termina sau se iese din
    limitele imaginii curente
set:
    Seteaza culoarea/latimea creionului in variabilele pen/fill_data
    pentru comenzile draw/fill
draw:
    Citeste comanda pentru draw si apeleaza functia specifica
draw_line:
    Deseneaza o linie, afland mai intai pe ce axa se afla intervalul maxim,
    il parcurge de la minim la maxim si afla cealalta coordonata a punctului
    in functie de formula data. Patratele in care sunt incadrati pixelii
    principali sunt umpluti folosind functia fill_rect
draw_tri, draw_rect: 
    Folosesc functia draw_line pentru a desena liniile unui triunghi/dreptunghi
fill:
    Functie care implementeaza umplerea recursiva. Verifica daca pixelul curent 
    se afla in limitele bitmap-ului si daca culoarea acestuia este aceeasi ca
    cea a pixelului de start, modifica pixelul in culoare setata si apoi trece
    la verificarea pixelilor care sunt vecini cu cel curent
