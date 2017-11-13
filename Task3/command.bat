set encoding utf8
set xl "t[sec]"
set yl "Amplitude"
set xrange [0:0.999878]
set yrange [0:1]
set grid
set title "Waveform"
plot "waveform.plt" with lp
