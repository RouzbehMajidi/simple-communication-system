%import data of pseudo-random numbers
data = importdata('../data/autocovariance.dat');

%create new window for figure
figure(1);

%create a discrete plot of the data
stem(0:99, data);
title('Crosscovariances for Uniformly Random Numbers'); %add title to plot
xlabel('Value of m'); %add x-axis label
ylabel('Crosscovariance'); %add y-axis label