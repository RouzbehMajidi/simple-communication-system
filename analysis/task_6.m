close all; %close any open figures
ct_data = importdata('../data/Task6/lpf_continuous.dat'); %load ct response data
dt_data = importdata('../data/Task6/lpf_discrete.dat'); %load dt response data

N_dt = 0:length(dt_data) - 1:length(ct_data); %calculate time for x-axis

scaleFactor = dt_data(end) / ct_data(end) %calculate scale factor for dt response

%create new window for figure
figure(1);
hold on;
%create a discrete plot of the data
plot(ct_data); %plot ct response
stem(N_dt, dt_data/scaleFactor); %plot scaled dt response
title('LPF CT vs DT Response'); %add title
xlabel('Time (s)'); %add x-axis label
ylabel('Amplitude'); %add y-axis label
legend('Continuous Time', 'Discrete Time'); %add legend
hold off;