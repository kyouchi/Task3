set encoding utf8
set xl "f[Hz]"
set yl "Amplitude"
set xrange [0:8191.5]
set yrange [7.3385e-19:8192]
set grid
set title "Apply FFT"
plot "FFT2.plt" with lp
