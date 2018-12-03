close all;
clear;

tx_signal = importdata('../data/task9/test_data/transmitted_symbol_output.dat'); 
recv_signal = importdata('../data/task9/test_data/received_signal_output.dat'); 
filtered_signal = importdata('../data/task9/test_data/filtered_signal_output.dat');
symbol_average = importdata('../data/task9/test_data/signal_correlation_output.dat');
digital_signal = importdata('../data/task9/test_data/received_symbol_output.dat');

fs = 1000;

hold on;

figure(1);

subplot(2,1,1);
plot(tx_signal);
grid on;
title('Transmitted signal');
xlabel('Time');
ylabel('Amplitude');
ylim([-1.5 1.5]);

t = fft(tx_signal);
t = fftshift(t);
nt = length(tx_signal);
ft = (-nt/2:nt/2-1)*(fs/nt);

power_t = 10*log10(abs(t).^2/nt);

subplot(2,1,2);
plot(ft,power_t)
grid on;
xlabel('Frequency');
title('Transmitted Signal Power Spectrum');
ylabel('Signal Power [dBW]');



figure(2);

subplot(2,1,1);
plot(recv_signal);
grid on;
title('Pre-LPF Received Signal');
xlabel('Time');
ylabel('Amplitude');

x = fft(recv_signal);
x = fftshift(x);
nx = length(recv_signal);
fx = (-nx/2:nx/2-1)*(fs/nx);

power_x = 10*log10(abs(x).^2/nx);

subplot(2,1,2);
plot(fx,power_x)
grid on;
xlabel('Frequency');
title('Pre-LPF Received Signal Power Spectrum');
ylabel('Signal Power [dBW]');

figure(3);

subplot(2,1,1);
plot(filtered_signal);
grid on;
title('Post-LPF Received Signal');
xlabel('Time');
ylabel('Amplitude');

y = fft(filtered_signal);
y = fftshift(y);
ny = length(filtered_signal);
fy = (-ny/2:ny/2-1)*(fs/ny);

power_y = 10*log10(abs(y).^2/ny);

subplot(2,1,2);
plot(fy,power_y);
grid on;
xlabel('Frequency');
title('Post-LPF Received Signal Power Spectrum');
ylabel('Signal Power [dBW]');


figure(4)

subplot(2,1,1);
plot(symbol_average);
grid on;
title('Correlator Reciever Output');
xlabel('Time');
ylabel('Amplitude');

a = fft(symbol_average);
a = fftshift(a);
na = length(symbol_average);
fa = (-na/2:na/2-1)*(fs/na);

power_a = 10*log10(abs(a).^2/na);

subplot(2,1,2);
plot(fa,power_a);
grid on;
xlabel('Frequency');
title('Correlator Reciever Output Power Spectrum');
ylabel('Signal Power [dBW]');


figure(5)

subplot(2,1,1);
plot(digital_signal);
grid on;
title('Received Digital Signal');
xlabel('Time');
ylabel('Amplitude');
ylim([-1.5 1.5]);

d = fft(digital_signal);
d = fftshift(d);
nd = length(digital_signal);
fd = (-nd/2:nd/2-1)*(fs/nd);

power_d = 10*log10(abs(d).^2/nd);

subplot(2,1,2);
plot(fd,power_d);
grid on;
xlabel('Frequency');
title('Received Digital Signal Power Spectrum');
ylabel('Signal Power [dBW]');