close all;
clear;

data_optimal = csvread("../data/task8/output_5.dat");
data_suboptimal = csvread("../data/task9/part_b/output_5.dat");
snr_values = 10e-3:0.1:10e3;

snr_dB_5 = 10*log10(data_optimal(:,2));
snr_dB_10 = 10*log10(data_suboptimal(:,2));
snr_dB = 10*log10(snr_values);

err_rate_5 = data_optimal(:,3) ./ data_optimal(:,4);
err_rate_10 = data_suboptimal(:,3) ./ data_suboptimal(:,4);
P_e = (1/2)*(1 - erf(sqrt(2*(snr_values/sqrt(2)))));

figure(1);
set(gca,'YScale', 'log');
hold on;
grid on;
semilogy(snr_dB_10,err_rate_5);
semilogy(snr_dB_10,err_rate_10);
semilogy(snr_dB, P_e);
% semilogy(snr_dB, P_e1);
xlabel('SNR [dB]');
ylabel('Bit Error Rate');
legend("Optimal Reciever","Sub-optimal reciever","Ideal Performance", "Location" ,"SouthWest");
hold off;