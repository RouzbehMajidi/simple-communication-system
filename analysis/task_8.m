close all;
clear;

snr_values = importdata('../data/task8/SNR_output.dat'); 
err_rate = importdata('../data/task8/error_rate_output.dat'); 

snr_values = 10*log10(snr_values);

figure(1);
plot(snr_values, err_rate);
grid on;
xlabel('SNR [dB]');
ylabel('Bit Error Rate');