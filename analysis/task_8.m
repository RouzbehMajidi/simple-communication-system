close all;
clear;

tx_signal = importdata('../data/task8/transmitted_symbol_output.dat'); 
recv_signal = importdata('../data/task8/received_signal_output.dat'); 
filtered_signal = importdata('../data/task8/filtered_signal_output.dat');
symbol_average = importdata('../data/task8/signal_correlation_output.dat');
digital_signal = importdata('../data/task8/received_symbol_output.dat');

figure(1);
hold on;

subplot(5,2,1);
plot(tx_signal);
grid on;
xlabel('Time');
ylabel('Transmitted Signal');
ylim([-1.5 1.5]);

subplot(5,2,3);
plot(recv_signal);
grid on;
xlabel('Time');
ylabel('Pre-LPF Received Signal');

subplot(5,2,5);
plot(filtered_signal);
grid on;
xlabel('Time');
ylabel('Post-LPF Received Signal');

subplot(5,2,7);
plot(symbol_average);
grid on;
xlabel('Time');
ylabel('Received Symbol Averaged Signal');

subplot(5,2,9);
plot(digital_signal);
grid on;
xlabel('Time');
ylabel('Received Digital Signal');
ylim([-1.5 1.5]);


fs = 10000;


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

a = fft(symbol_average);
a = fftshift(a);
na = length(symbol_average);
fa = (-na/2:na/2-1)*(fs/na);

d = fft(digital_signal);
d = fftshift(d);
nd = length(digital_signal);
fd = (-nd/2:nd/2-1)*(fs/nd);


power_t = 10*log10(abs(t).^2/nt);
power_x = 10*log10(abs(x).^2/nx);
power_y = 10*log10(abs(y).^2/ny);
power_a = 10*log10(abs(a).^2/na);
power_d = 10*log10(abs(d).^2/nd);

subplot(5,2,2);
plot(ft,power_t)
grid on;
xlabel('Frequency');
ylabel('Transmitted Signal Power');

subplot(5,2,4);
plot(fx,power_x)
grid on;
xlabel('Frequency');
ylabel('Pre-LPF Received Signal Power');

subplot(5,2,6);
plot(fy,power_y);
grid on;
xlabel('Frequency');
ylabel('Post-LPF Received Signal Power');

subplot(5,2,8);
plot(fa,power_a);
grid on;
xlabel('Frequency');
ylabel('Received Symbol Averaged Signal');

subplot(5,2,10);
plot(fd,power_d);
grid on;
xlabel('Frequency');
ylabel('Received Digital Signal Power');