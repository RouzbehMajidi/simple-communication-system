close all;
clear;

data_5 = csvread("../data/task9/part_b/output_5.dat");
% data_10 = csvread("../data/task9/part_b/output_10.dat");
% data_20 = csvread("../data/task9/part_b/output_20.dat");
snr_values = 10e-3:0.1:10e3;

snr_dB_5 = 10*log10(data_5(:,2));
% snr_dB_10 = 10*log10(data_10(:,2));
% snr_dB_20 = 10*log10(data_20(:,2));
snr_dB = 10*log10(snr_values);

err_rate_5 = data_5(:,3) ./ data_5(:,4);
% err_rate_10 = data_10(:,3) ./ data_10(:,4);
% err_rate_20 = data_20(:,3) ./ data_20(:,4);
P_e = (1/2)*(1 - erf(sqrt(2*(snr_values/sqrt(2)))));

figure(1);
set(gca,'YScale', 'log');
hold on;
grid on;
semilogy(snr_dB_5,err_rate_5);
% semilogy(snr_dB_10,err_rate_10);
% semilogy(snr_dB_10,err_rate_20);
semilogy(snr_dB, P_e);
% semilogy(snr_dB, P_e1);
xlabel('SNR [dB]');
ylabel('Bit Error Rate');
legend("5 Samples per Symbol", "Ideal Performance", "Location" ,"SouthWest");
% legend("5 Samples per Symbol","10 Samples per Symbol", "20 Samples per Symbol", "Ideal Performance", "Location" ,"SouthWest");
hold off;