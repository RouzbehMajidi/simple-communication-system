close all;
clear;

%load error rate data from file
data_5 = csvread('../data/task9/part_b/output_5.dat');
snr_values = 1e-3:0.1:10e3; %snr values in linear units

%convert snr to dB
snr_dB_5 = 10*log10(data_5(:,2)); %N=5
snr_dB = 10*log10(snr_values); %ideal BER case

%calculate bit error rate
err_rate_5 = data_5(:,3) ./ data_5(:,4); %N=5
P_e = (1/2)*(1 - erf(sqrt(2*(snr_values/sqrt(2))))); %ideal

%calculate student-t distribution parameter
student_t = tinv(1-(1-0.95)/2, 250000-1); 

%calculate 95% confidence interval
err_5 = student_t*std(err_rate_5)/sqrt(250000)*ones(length(err_rate_5), 1);

figure(1);
set(gca,'YScale', 'log'); %log scale for y-axis
hold on;
grid on;
plot(snr_dB_5,err_rate_5); %plot BER for N=5
plot(snr_dB, P_e); %plot ideal BER
xlabel('SNR [dB]'); %add x-axis label
ylabel('Bit Error Rate'); %add y-axis label
legend('5 Samples per Symbol', 'Ideal Performance', 'Location' ,'SouthWest'); %add legend
hold off;