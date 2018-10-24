
 %import data of pseudo-random numbers
data = importdata('../data/random_out.dat');

 %create histogram
h = histogram(data);

%print out histogram details
h %#ok<NOPTS>
 %add title to histogram
title('Histogram of Uniform Pseudo-Random Number Generator');
%add y-axis label
ylabel('Number of pseudo-random numbers per bin');
%add x-axis label
xlabel('Bins');
dist_mean = mean(data) %#ok<NOPTS>