set term jpeg

set xlabel "t" # etykieta osi OX
set ylabel "Wartosci" # etykieta osi OY

set title "Metoda Newtona"
set out "newton.jpeg"
plot "1_newton_results.dat" u 1:2 w l lw 1 t 'v(t)', "1_newton_results.dat" u 1:3 w l lw 1 t 'u(t)'

set title "Metoda Picard'a"
set out "picard.jpeg"
plot "1_picard_results.dat" u 1:2 w l lw 1 t 'v(t)', "1_picard_results.dat" u 1:3 w l lw 1 t 'u(t)'

set title "Metoda RK2"
set out "rk2.jpeg"
plot "2_rk2_results.dat" u 1:2 w l lw 1 t 'v(t)', "2_rk2_results.dat" u 1:3 w l lw 1 t 'u(t)'