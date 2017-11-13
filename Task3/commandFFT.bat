set encoding utf8
set xl "f[Hz]"
set yl "Amplitude"
set xrange [0:200]
set yrange [0:4096]
set grid
set title "Apply FFT"
plot "FFT.plt" with lp
