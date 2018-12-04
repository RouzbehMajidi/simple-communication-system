close all;
clear;

%load error rate data from file
data_optimal = csvread('../data/task8/output_5.dat'); %optimal error
data_suboptimal = csvread('../data/task9/part_b/output_5.dat'); %suboptimal error
snr_values = 1e-3:0.1:10e3; %snr values in linear units

%convert snr to dB
snr_dB_opt = 10*log10(data_optimal(:,2)); %optimal
snr_dB_sub = 10*log10(data_suboptimal(:,2)); %suboptimal
snr_dB = 10*log10(snr_values); %ideal

%calculate bit error rates
err_rate_opt = data_optimal(:,3) ./ data_optimal(:,4); %optimal
err_rate_sub = data_suboptimal(:,3) ./ data_suboptimal(:,4); %suboptimal
P_e = (1/2)*(1 - erf(sqrt(2*(snr_values/sqrt(2))))); %ideal

%calculate student-t distribution parameter
student_t = tinv(1-(1-0.95)/2, 250000-1); 

%calculate 95% confidence interval
err_opt = student_t*std(err_rate_opt)/sqrt(250000)*ones(length(err_rate_opt), 1);
err_sub = student_t*std(err_rate_sub)/sqrt(250000)*ones(length(err_rate_sub), 1);

figure(1);
set(gca,'YScale', 'log'); %use log scale for y-axis
hold on;
grid on;
plot(snr_dB_opt,err_rate_opt); %plot optimal BER
plot(snr_dB_sub,err_rate_sub); %plot suboptimal BER
plot(snr_dB, P_e); %plot ideal BER
xlabel('SNR [dB]'); %add x-axis label
ylabel('Bit Error Rate'); %add y-axis label
legend('Optimal Reciever','Sub-optimal reciever','Ideal Performance', 'Location' ,'SouthWest'); %add legend
hold off;