set term jpeg

set logscale x

set title "Relaksacja Globalna"
set out "relaksacja_globalna_results.jpeg"
plot "1_global_0.600000_res.dat" u 1:2 w l lw 1 t 'omega=0.6', "1_global_1.000000_res.dat" u 1:2 w l lw 1 t 'omega=1.0'

set title "Relaksacja Lokalna"
set out "relaksacja_lokalna_results.jpeg"
plot "1_local_1.000000_res.dat" u 1:2 w l lw 1 t 'omega=1.0', "1_local_1.400000_res.dat" u 1:2 w l lw 1 t 'omega=1.4', "1_local_1.800000_res.dat" u 1:2 w l lw 1 t 'omega=1.8', "1_local_1.900000_res.dat" u 1:2 w l lw 1 t 'omega=1.9'

unset logscale x

set xrange [0.0:15.0]
set yrange [0.0:10.0]

set title "Relaksacja Globalna - V"
set out "relaksacja_globalna_v_0.600000.jpeg"
plot "1_global_0.600000_grid.dat" u 1:2:3 w p pt 7 palette t 'V'

set out "relaksacja_globalna_v_1.000000.jpeg"
plot "1_global_1.000000_grid.dat" u 1:2:3 w p pt 7 palette t 'V'

set title "Relaksacja globalna - Error"
set out "relaksacja_globalna_err_0.600000.jpeg"
set cbrange [ 0.00000 : 0.0025 ]
plot "1_global_0.600000_err.dat" u 1:2:3 w p pt 7 palette t 'Error'

set out "relaksacja_globalna_err_1.000000.jpeg"
set cbrange [ 0.00000 : 0.003 ]
plot "1_global_1.000000_err.dat" u 1:2:3 w p pt 7 palette t 'Error'