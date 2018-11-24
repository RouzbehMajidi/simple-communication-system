%import data of pseudo-random numbers
data = importdata('../data/autocovariance_gaussian.dat');
figure(1); %create new window for figure
stem(0:99, data); %create a discrete plot of the data
title('Crosscovariances for Normally Random Numbers'); %add title
xlabel('Value of m'); %add x-axis label
ylabel('Crosscovariance'); %add y-axis label

