close all;
clear;

snr_values_5 = importdata('../data/task9/SNR_output_5.dat');
snr_values_10 = importdata('../data/task9/SNR_output_10.dat');
snr_values_20 = importdata('../data/task9/SNR_output_20.dat');
snr_values = 10e-3:0.1:10e3;

err_rate_5 = importdata('../data/task9/error_rate_output_5.dat'); 
err_rate_10 = importdata('../data/task9/error_rate_output_10.dat'); 
err_rate_20 = importdata('../data/task9/error_rate_output_20.dat');
P_e = (1/2)*(1 - erf(sqrt(2*(snr_values/sqrt(2)))));
% P_e1 = (1/2)*(1 - erf(sqrt((2/pi)*(snr_values/sqrt(2)))));

% err_rate_5 = spline(snr_values_10, err_rate_5, snr_values);
% err_rate_10 = spline(snr_values_10, err_rate_10, snr_values);
% err_rate_20 = spline(snr_values_10, err_rate_20, snr_values);

snr_dB_5 = 10*log10(snr_values_5);
snr_dB_10 = 10*log10(snr_values_10);
snr_dB_20 = 10*log10(snr_values_20);
snr_dB = 10*log10(snr_values);

figure(1);
set(gca,'YScale', 'log');
hold on;
grid on;
semilogy(snr_dB_10,err_rate_5);
semilogy(snr_dB_10,err_rate_10);
semilogy(snr_dB_10,err_rate_20);
semilogy(snr_dB, P_e);
% semilogy(snr_dB, P_e1);
xlabel('SNR [dB]');
ylabel('Bit Error Rate');
legend("5 Samples per Symbol","10 Samples per Symbol", "20 Samples per Symbol", "Ideal Performance", "Location" ,"SouthWest");
hold off;