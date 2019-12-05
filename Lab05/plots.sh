set term jpeg

set xlabel "iter"
set ylabel "S(iter)"

set logscale x

set title "Relaksacja wielosiatkowa"
set out "wielosiatkowa_S.jpeg"
plot "wielosiatkowa_S_k_16.dat" u 1:2 w l lw 1 t 'k=16',"wielosiatkowa_S_k_8.dat" u 1:2 w l lw 1 t 'k=8',"wielosiatkowa_S_k_4.dat" u 1:2 w l lw 1 t 'k=4',"wielosiatkowa_S_k_2.dat" u 1:2 w l lw 1 t 'k=2',"wielosiatkowa_S_k_1.dat" u 1:2 w l lw 1 t 'k=1'

unset logscale x

set xlabel "x"
set ylabel "y"
set zlabel "w"

set logscale z

set title "Relaksacja wielosiatkowa"
set out "wielosiatkowa_V_k_16.jpeg"
plot [-3:29][-3:29] "wielosiatkowa_V_k_16.dat" u 1:2:3 w p pt 5 ps 8 palette notitle

set title "Relaksacja wielosiatkowa"
set out "wielosiatkowa_V_k_8.jpeg"
plot [-3:29][-3:29] "wielosiatkowa_V_k_8.dat" u 1:2:3 w p pt 5 ps 4 palette notitle

set title "Relaksacja wielosiatkowa"
set out "wielosiatkowa_V_k_4.jpeg"
plot [-3:29][-3:29] "wielosiatkowa_V_k_4.dat" u 1:2:3 w p pt 5 ps 2 palette notitle

set title "Relaksacja wielosiatkowa"
set out "wielosiatkowa_V_k_2.jpeg"
plot [-3:29][-3:29] "wielosiatkowa_V_k_2.dat" u 1:2:3 w p pt 5 ps 1 palette notitle

set title "Relaksacja wielosiatkowa"
set out "wielosiatkowa_V_k_1.jpeg"
plot [-3:29][-3:29] "wielosiatkowa_V_k_1.dat" u 1:2:3 w p pt 7 palette notitle