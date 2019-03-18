    In liniile urmatoare, voi prezent implementarea primei teme la apd.


Part 1. Super Sampling Anti Aliasing
    
    In cadrul acestei parti, am ales o abordare cu un vector pentru 
retinerea informatiei din imagine, cu exceptia elementelor de inceput
(tipul, width, height, maxVal). In cazul unei poze rgb folosesc un 
vector de structuri rgb (in cadrul acestei structuri am trei char-uri,
fiecare reprezentant cate un canal de culori), iar in cazul unei poze
alb-negru am folosit un vector de char-uri. De asemenea, pentru a 
trimite parametrii necesari functiei threadFunction, pentru rezolvarea
paralelizarii, am creat o structura care contine id-ul thread-ului si
doi pointeri la structuri de tip image.
    In cadrul functiei de citire, am extras separat valorile din antet
dupa care am citit informtia din imagine intr-unul din vectorii descrisi
mai sus, in functie de tipul pozei.
    In cadrul functiei de scriere, am procedat asemanator cu citirea, 
am scris in visier elementele din antet, dupa care am scris intr-un singur
fwrite toata informtia din imagine.
    In vederea realizarii functiei resize, am urmarit pasii parcursi in 
cadrul laboratoarelor pentru realizarea paralelizarii. Astfel, in functia
de resize tot ce fac este sa aloc memorie pentru imaginea finala, sa setez
valorile pe care le trimit ca parametru functiei threadFunction, sa creez
thread-urile si sa le dau join la final. In functia threadFunction, am 
implementat efectiv mecanismul de resize. Paralelizarea am facut-o pe linii
de blocuri de pixeli, asemanator cu ce am facut in cadrul laboratoarelor.
Astfel am patru for-uri, cu primele doua fac parcurgerea prin vectorul final, 
folosind acesti indici pentru calcularea pozitiei pixel-ului din conltul
din stanga sus a unui bloc din imaginea initiala si cu ajutorul a altor
doua for-uri iterez prin acel bloc si in functie de resize factor si de
tipul imaginii fac operatiile necesare calcularii valorii/valorilor
pixel-ului corespunzator din imaginea finala. Paralelizarea este facuta
pe primul for din cele patru descrise.


Part 2. Micro renderer

    In cadrul acestei parti, am ales o abordare tot cu un vector pentru
retinerea informatiei din imagine. In acest caz am doar un vector de char-uri.
De asemenea, pentru a trimite parametrii necesari functiei threadFunction,
pentru rezolvarea paralelizarii, am creat o structura care contine id-ul
thread-ului si un pointer la o structura de tip image.
    In cadrul functiei initialize, tot ce am facut a fost sa aloc memorie
pentru vectorul care contine informatia din imagine.
    In cadrul functiei de scriere, am procedat la fel ca in cadrul
scrierii din prima parte a temei.
    In vederea realizarii functiei de randare, am procedat aproape la fel ca
in candrul functiei resize din prima parte a temei. Am setat parametrii
necesari pentru functia threadFunction, am creat thread-urile si le-am dat
join. Pentru functia threadFunction am folosit doua for-uri, in cadrul
carora pentru fiecare pixel din imagine calculez dinstanta pana la dreapta
in fuctie de coordonatele x si y calculate in inainte (care la randul lor
sunt calculte in fuctie de i, j si lunigimea unui pixel). Dupa care, 
in functie de caz aleg sa fac pixelul alb sau negru. Am paralelizat primul
for, asemanator cu ce am facut la prima parte.   



