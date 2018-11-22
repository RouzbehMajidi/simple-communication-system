clear;
ct_data = importdata('../data/lpf_continuous.dat');
dt_data = importdata('../data/lpf_discrete.dat');

%create new window for figure
figure(1);
hold on;
%create a discrete plot of the data
plot(ct_data);
stem(dt_data);