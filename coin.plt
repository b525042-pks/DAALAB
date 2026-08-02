set title "Fair vs Biased Coin Toss"
set xlabel "Number of Tosses"
set ylabel "Probability of Heads"
set grid

plot "coin.dat" using 1:2 with lines lw 2 title "Fair Coin", \
     "coin.dat" using 1:3 with lines lw 2 title "Biased Coin"

pause -1