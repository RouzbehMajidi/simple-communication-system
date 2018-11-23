close all;
clear;

noisy_signal = importdata('../data/noisy_signal_output.dat'); 
filtered_signal = importdata('../data/filtered_signal_output.dat');

figure(1);
hold on;
grid on;
subplot(2,1,1);
plot(noisy_signal);
grid on;
ylabel('Pre-LPF Signal')
subplot(2,1,2);
plot(filtered_signal);
grid on;
xlabel('Frequency')
ylabel('Post-LPF Signal')

fs = 1000;

x = fft(noisy_signal);

nx = length(noisy_signal);
fx = (0:nx-1)*(fs/nx);

y = fft(filtered_signal);

ny = length(filtered_signal);
fy = (0:ny-1)*(fs/ny);


power_x = abs(x).^2/nx;
power_y = abs(y).^2/ny;

figure(2);
hold on;
subplot(2,1,1);
plot(fx,power_x)
grid on;
ylabel('Pre-LPF Signal Power')
subplot(2,1,2);
plot(fy,power_y);
grid on;
xlabel('Frequency')
ylabel('Post-LPF Signal Power')