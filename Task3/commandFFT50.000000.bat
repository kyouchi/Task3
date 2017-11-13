set encoding utf8
set xl "f[Hz]"
set yl "Amplitude"
set xrange [0:200]
set yrange [0:2048]
set grid
set title "Apply FFT"
plot "FFT50.000000.plt" with lp
