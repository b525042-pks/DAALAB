set title "Tower of Hanoi"
set xlabel "Number of Discs"
set ylabel "Number of Moves"
set grid

plot "toh.dat" using 1:2 with linespoints lw 2 pt 7 title "Moves"

pause -1