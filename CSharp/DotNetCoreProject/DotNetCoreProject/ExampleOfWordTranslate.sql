SELECT name FROM word WHERE idWord=18097
"простые метеорологические условия"

SELECT idCategory FROM wordCategory WHERE idWord=18097;
"10005"

SELECT w.idWord, w.name FROM categoryWord cw JOIN word w ON w.idWord=cw.idWord WHERE idCategory=10005;
"5264"	"einfache Wetterbedingungen"
"16490"	"Schönwetter"

SELECT idCategory FROM wordCategory WHERE idWord=5264;
"70458"
SELECT idCategory FROM wordCategory WHERE idWord=16490;
"861" "862" "863"

SELECT w.idWord, w.name FROM categoryWord cw JOIN word w ON w.idWord=cw.idWord WHERE idCategory=70458;
"18097"	"простые метеорологические условия"
SELECT w.idWord, w.name FROM categoryWord cw JOIN word w ON w.idWord=cw.idWord WHERE idCategory=861 OR idCategory=862 OR idCategory=863;
"18099"	"ясная погода"
"18100"	"хорошая погода"
"16653"	"лётная погода"
"18098"	"простые метеоусловия"
"18097"	"простые метеорологические условия"

-- ################################################################### --
SELECT name FROM word WHERE idWord=16583
"мать"

SELECT idCategory FROM wordCategory WHERE idWord=16583;
"1352" "1353" "1354" "1355"

SELECT w.idWord, w.name FROM categoryWord cw JOIN word w ON w.idWord=cw.idWord WHERE idCategory=1352 OR idCategory=1353 OR idCategory=1354 OR idCategory=1355;
"18095"	"Mütter"
"18094"	"Erzeugerin"
"16574"	"Alte"
"18093"	"meine alte Dame"

SELECT idCategory FROM wordCategory WHERE idWord=18095;
"10014" "10015" "10016" "10017" "10018"

SELECT idCategory FROM wordCategory WHERE idWord=18094;
"10019" "10020" "10021"

SELECT idCategory FROM wordCategory WHERE idWord=16574;
"1221" "1222" "1223" "1224"

SELECT idCategory FROM wordCategory WHERE idWord=18093;
"10022" "10023"

SELECT w.idWord, w.name FROM categoryWord cw JOIN word w ON w.idWord=cw.idWord WHERE idCategory=10014 OR idCategory=10015 OR idCategory=10016 OR idCategory=10017 OR idCategory=10018;
"307"	"мама"
"16583"	"мать"
"16576"	"матка"
"305"	"источник жизни"
"306"	"прародительница"
"5257"	"пресс-форма"
"5258"	"гайка"
"5260"	"матрица"
"314"	"гуща"
"17162"	"осадок"

SELECT w.idWord, w.name FROM categoryWord cw JOIN word w ON w.idWord=cw.idWord WHERE idCategory=10019 OR idCategory=10020 OR idCategory=10021;
"302"	"родительница"
"16583"	"мать"
"5929"	"производитель"

SELECT w.idWord, w.name FROM categoryWord cw JOIN word w ON w.idWord=cw.idWord WHERE idCategory=1221 OR idCategory=1222 OR idCategory=1223 OR idCategory=1224;
"16411"	"старик"
"16554"	"классики древности"
"16555"	"древние греки и римляне"
"16556"	"античные народы"
"16558"	"прежнее"
"16560"	"старое"
"16562"	"старуха"
"16563"	"предки"
"16575"	"родители"
"16576"	"матка"
"16577"	"старший валет"
"16411"	"старик"
"16428"	"отец"
"16582"	"жена"
"16583"	"мать"
"16584"	"начальница"
"16585"	"командир"
"16586"	"капитан"
"16587"	"муж"
"16588"	"начальник"
"16589"	"сама"
"16590"	"хозяйка"
"16591"	"моя половина"
"16592"	"жёнушка"
"16593"	"старушка"
"16594"	"мастер"
"16595"	"шеф"
"16596"	"хозяин"
"16597"	"сам"
"16598"	"муженёк"






