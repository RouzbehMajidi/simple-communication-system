close all;
clear;

tx_signal = importdata('../data/task7/transmitted_signal_output_no_noise.dat'); 
recv_signal = importdata('../data/task7/received_signal_output_no_noise.dat'); 
filtered_signal = importdata('../data/task7/filtered_signal_output_no_noise.dat');

figure(1);
hold on;

subplot(3,2,1);
plot(tx_signal);
grid on;
title('Transmitted Signal');
xlabel('Sample');
ylabel('Amplitude');
ylim([-1.5 1.5]);

subplot(3,2,3);
plot(recv_signal);
grid on;
title('Pre-LPF Received Signal');
xlabel('Sample');
ylabel('Amplitude');
ylim([-1.5 1.5]);

subplot(3,2,5);
plot(filtered_signal);
grid on;
title('Post-LPF Received Signal');
xlabel('Sample');
ylabel('Amplitude');
ylim([-1.5 1.5]);

fs = 1000;

t = fft(tx_signal);
t = fftshift(t);

nt = length(tx_signal);
ft = (-nt/2:nt/2-1)*(fs/nt);

x = fft(recv_signal);
x = fftshift(x);

nx = length(recv_signal);
fx = (-nx/2:nx/2-1)*(fs/nx);

y = fft(filtered_signal);
y = fftshift(y);

ny = length(filtered_signal);
fy = (-ny/2:ny/2-1)*(fs/ny);


power_t = abs(t).^2/nt;
power_x = abs(x).^2/nx;
power_y = abs(y).^2/ny;

subplot(3,2,2);
plot(ft,power_t)
grid on;
title('Transmitted Signal Power Spectrum');
xlabel('Frequency');
ylabel('Amplitude');

subplot(3,2,4);
plot(fx,power_x)
grid on;
title('Pre-LPF Received Signal Power');
xlabel('Frequency');
ylabel('Amplitude');

subplot(3,2,6);
plot(fy,power_y);
grid on;
ylabel('Post-LPF Received Signal Power');
xlabel('Frequency');
ylabel('Amplitude');