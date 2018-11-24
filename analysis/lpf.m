close all;
ct_data = importdata('../data/lpf_continuous.dat');
dt_data = importdata('../data/lpf_discrete.dat');

N_dt = 0:length(dt_data) - 1:length(ct_data);

scaleFactor = dt_data(end) / ct_data(end)
scaleFactor_squared = scaleFactor^2


%create new window for figure
figure(1);
hold on;
%create a discrete plot of the data
plot(ct_data);
stem(N_dt, dt_data/scaleFactor);