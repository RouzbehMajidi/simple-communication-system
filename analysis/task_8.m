close all;
clear;

%load error rate data from files
data_5 = csvread('../data/task8/output_5.dat');
data_10 = csvread('../data/task8/output_10.dat');
data_20 = csvread('../data/task8/output_20.dat');

snr_values = 1e-3:0.1:10e3; %snr values in linear units

%convert SNR to dB for each sampling rate
snr_dB_5 = 10*log10(data_5(:,2)*10); %N=5
snr_dB_10 = 10*log10(data_10(:,2)*10); %N=10
snr_dB_20 = 10*log10(data_20(:,2)*10); %N=20
snr_dB = 10*log10(snr_values); %ideal and analytical

%calculate the bit error rate
err_rate_5 = data_5(:,3) ./ data_5(:,4); %N=5
err_rate_10 = data_10(:,3) ./ data_10(:,4); %N=10
err_rate_20 = data_20(:,3) ./ data_20(:,4); %N=20
P_e = (1/2)*(1 - erf(sqrt(2*(snr_values/sqrt(2))))); %ideal BER
P_e1 = (1/2)*(1 - erf(sqrt((2/pi)*(snr_values/sqrt(2))))); %approximate BER

student_t = tinv(1-(1-0.95)/2, 250000-1); %calcualte student-t distribution parameter

%calculate 95% confidence interval
err_5 = student_t*std(err_rate_5)/sqrt(250000)*ones(length(err_rate_5), 1); %N=5
err_10 = student_t*std(err_rate_10)/sqrt(250000)*ones(length(err_rate_10), 1); %N=10
err_20 = student_t*std(err_rate_20)/sqrt(250000)*ones(length(err_rate_20), 1); %N=20

figure(1);
set(gca,'YScale', 'log'); %use logarithmic scale for y-axis
hold on;
grid on;
plot(snr_dB_5,err_rate_5); %plot BER for N=5
plot(snr_dB_10,err_rate_10); %plot BER for N=10
plot(snr_dB_20,err_rate_20); %plot BER for N=20
plot(snr_dB, P_e); %plot ideal BER
plot(snr_dB, P_e1); %plot approximate BER
xlabel('SNR [dB]'); %add x-axis label
ylabel('Bit Error Rate'); %add y-axis label
%add legend
legend('5 Samples per Symbol','10 Samples per Symbol', '20 Samples per Symbol', ...
    'Ideal Performance', 'Analytical Performance', 'Location' ,'SouthWest');
hold off;