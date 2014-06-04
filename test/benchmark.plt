#!/usr/bin/env gnuplot

set terminal push
set terminal pdfcairo enhanced
set output "benchmark.pdf"

set logscale x
set logscale y
set xlabel "Array length" 
set ylabel "Elapsed time [s]"
set format x "10^{%T}"
set format y "10^{%T}"

set key bottom right
plot 'benchmark.log' using 1:2 title 'qsort', '' using 1:3 title 'qsort\_p'

unset logscale y
set ylabel "Speed up"
set format y "%g"
plot 'benchmark.log' using 1:4 notitle

unset output
set terminal pop
