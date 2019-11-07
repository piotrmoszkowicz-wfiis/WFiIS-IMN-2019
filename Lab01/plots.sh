set term jpeg

set xlabel "Kolejne iteracje" # etykieta osi OX
set ylabel "Wartosci" # etykieta osi OY

set title "Metoda jawna Eulera"
set out "euler.jpeg"
plot "euler_0.010000.dat" u 1:2 w l lw 1 t 'dt = 0.01s', "euler_0.100000.dat" u 1:2 w l lw 1 t 'dt = 0.1s', "euler_1.000000.dat" u 1:2 w l lw 5 t 'dt = 1.0s', "euler_def.dat" u 1:2 w p pt 7 ps 0.2 t 'definicja'

set title "Metoda jawna Eulera - blad"
set out "euler_err.jpeg"
plot "euler_0.010000_err.dat" u 1:2 w l lw 1 t 'dt = 0.01s', "euler_0.100000_err.dat" u 1:2 w l lw 1 t 'dt = 0.1s', "euler_1.000000_err.dat" u 1:2 w l lw 5 t 'dt = 1.0s'

set title "Metoda RK2"
set out "rk2.jpeg"
plot "rk2_0.010000.dat" u 1:2 w l lw 1 t 'dt = 0.01s', "rk2_0.100000.dat" u 1:2 w l lw 1 t 'dt = 0.1s', "rk2_1.000000.dat" u 1:2 w l lw 5 t 'dt = 1.0s', "rk2_def.dat" u 1:2 w p pt 7 ps 0.2 t 'definicja'

set title "Metoda RK2 - blad numeryczny"
set out "rk2_err.jpeg"
plot "rk2_0.010000_err.dat" u 1:2 w l lw 1 t 'dt = 0.01s', "rk2_0.100000_err.dat" u 1:2 w l lw 1 t 'dt = 0.1s', "rk2_1.000000_err.dat" u 1:2 w l lw 5 t 'dt = 1.0s'

set title "Metoda RK2 - blad numeryczny2"
set out "rk2_err_2.jpeg"
plot "rk2_0.010000_err.dat" u 1:2 w l lw 1 t 'dt = 0.01s', "rk2_0.100000_err.dat" u 1:2 w l lw 1 t 'dt = 0.1s'

set title "Metoda RK4"
set out "rk4.jpeg"
plot "rk4_0.010000.dat" u 1:2 w l lw 1 t 'dt = 0.01s', "rk4_0.100000.dat" u 1:2 w l lw 1 t 'dt = 0.1s', "rk4_1.000000.dat" u 1:2 w l lw 5 t 'dt = 1.0s', "rk4_def.dat" u 1:2 w p pt 7 ps 0.2 t 'definicja'

set title "Metoda RK4 - blad numeryczny"
set out "rk4_err.jpeg"
plot "rk4_0.010000_err.dat" u 1:2 w l lw 1 t 'dt = 0.01s', "rk4_0.100000_err.dat" u 1:2 w l lw 1 t 'dt = 0.1s', "rk4_1.000000_err.dat" u 1:2 w l lw 5 t 'dt = 1.0s'

set title "Metoda RK4 - blad numeryczny2"
set out "rk4_err_2.jpeg"
plot "rk4_0.010000_err.dat" u 1:2 w l lw 1 t 'dt = 0.01s', "rk4_0.100000_err.dat" u 1:2 w l lw 1 t 'dt = 0.1s'

set title "RLC omega = 0.5 omega_0"
set out "rlc_50.jpeg"
plot "rlc_50.000000.dat" u 1:2 w l lw 1 t 'Q(t)', "" u 1:3 w l lw 1 t 'I(t)'

set title "RLC omega = 0.5 omega_0"
set out "rlc_50_q.jpeg"
plot "rlc_50.000000.dat" u 1:2 w l lw 1 t 'Q(t)'

set title "RLC omega = 0.8 omega_0"
set out "rlc_80.jpeg"
plot "rlc_80.000000.dat" u 1:2 w l lw 1 t 'Q(t)', "" u 1:3 w l lw 1 t 'I(t)'

set title "RLC omega = 0.8 omega_0"
set out "rlc_80_q.jpeg"
plot "rlc_80.000000.dat" u 1:2 w l lw 1 t 'Q(t)'

set title "RLC omega = 1.0 omega_0"
set out "rlc_100.jpeg"
plot "rlc_100.000000.dat" u 1:2 w l lw 1 t 'Q(t)', "" u 1:3 w l lw 1 t 'I(t)'

set title "RLC omega = 1.0 omega_0"
set out "rlc_100_q.jpeg"
plot "rlc_100.000000.dat" u 1:2 w l lw 1 t 'Q(t)'

set title "RLC omega = 1.2 omega_0"
set out "rlc_120.jpeg"
plot "rlc_120.000000.dat" u 1:2 w l lw 1 t 'Q(t)', "" u 1:3 w l lw 1 t 'I(t)'

set title "RLC omega = 1.2 omega_0"
set out "rlc_120_q.jpeg"
plot "rlc_120.000000.dat" u 1:2 w l lw 1 t 'Q(t)'