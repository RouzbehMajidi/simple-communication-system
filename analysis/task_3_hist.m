data = importdata('../data/random_gaussian_out.dat'); %import data of pseudo-random numbers
h = histogram(data); %create histogram
h %#ok<NOPTS> %print out histogram details
title('Histogram of Gaussian Pseudo-Random Number Generator'); %add title
ylabel('Number of pseudo-random numbers per bin'); %add y-axis label
xlabel('Bins'); %add x-axis label
dist_mean = mean(data) %#ok<NOPTS> %calculate mean
dist_var = var(data)  %#ok<NOPTS> %calculate variance


