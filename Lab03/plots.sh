set term jpeg

set title "Metoda RK2 - x(t)"
set out "rk2_xt.jpeg"
plot "1_rk2_results_0.000010.dat" u 1:3 w l lw 1 t 'tol = 10^-5', "1_rk2_results_0.010000.dat" u 1:3 w l lw 1 t 'tol = 10^-2'

set title "Metoda RK2 - v(t)"
set out "rk2_vt.jpeg"
plot "1_rk2_results_0.000010.dat" u 1:4 w l lw 1 t 'tol = 10^-5', "1_rk2_results_0.010000.dat" u 1:4 w l lw 1 t 'tol = 10^-2'

set title "Metoda RK2 - dt(t)"
set out "rk2_dtt.jpeg"
plot "1_rk2_results_0.000010.dat" u 1:2 w l lw 1 t 'tol = 10^-5', "1_rk2_results_0.010000.dat" u 1:2 w l lw 1 t 'tol = 10^-2'

set title "Metoda RK2 - v(x)"
set out "rk2_vx.jpeg"
plot "1_rk2_results_0.000010.dat" u 3:4 w l lw 1 t 'tol = 10^-5', "1_rk2_results_0.010000.dat" u 3:4 w l lw 1 t 'tol = 10^-2'

set title "Metoda Trapezow - x(t)"
set out "trapez_xt.jpeg"
plot "1_trapez_results_0.000010.dat" u 1:3 w l lw 1 t 'tol = 10^-5', "1_trapez_results_0.010000.dat" u 1:3 w l lw 1 t 'tol = 10^-2'

set title "Metoda Trapezow - v(t)"
set out "trapez_vt.jpeg"
plot "1_trapez_results_0.000010.dat" u 1:4 w l lw 1 t 'tol = 10^-5', "1_trapez_results_0.010000.dat" u 1:4 w l lw 1 t 'tol = 10^-2'

set title "Metoda Trapezow - dt(t)"
set out "trapez_dtt.jpeg"
plot "1_trapez_results_0.000010.dat" u 1:2 w l lw 1 t 'tol = 10^-5', "1_trapez_results_0.010000.dat" u 1:2 w l lw 1 t 'tol = 10^-2'

set title "Metoda Trapezow - v(x)"
set out "trapez_vx.jpeg"
plot "1_trapez_results_0.000010.dat" u 3:4 w l lw 1 t 'tol = 10^-5', "1_trapez_results_0.010000.dat" u 3:4 w l lw 1 t 'tol = 10^-2'