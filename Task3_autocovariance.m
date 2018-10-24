data = importdata('autocovariance2_Gaussian.dat'); %import data of pseudo-random numbers
figure(1); %create new window for figure
stem(data); %create a discrete plot of the data
title('Crosscovariances for Normally Random Numbers'); %add title
xlabel('Value of m'); %add x-axis label
ylabel('Crosscovariance'); %add y-axis label