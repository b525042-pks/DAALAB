set terminal windows
set title "Bubble Sort Comparison"
set xlabel "Algorithm"
set ylabel "Comparisons"

set style data histograms
set style fill solid
set boxwidth 0.5

set yrange [0:*]
set grid ytics

plot "bubble_compare.dat" using 2:xtic(1) title "Comparisons"

pause -1