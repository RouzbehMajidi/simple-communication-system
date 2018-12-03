close all
%load noiseless signal
filtered_signal = importdata('../data/task7/filtered_signal_output_no_noise.dat');

%load signal with N=10, noise power = 10%
filtered_signal_1010 = importdata('../data/task7/filtered_signal_output_noise10.dat');

%load signal with N=10, noise power = 25%
filtered_signal_1025 = importdata('../data/task7/filtered_signal_output_noise25.dat');

%load signal with N=20, noise power = 25%
filtered_signal_2020 = importdata('../data/task7/filtered_signal_output_noise20.dat');

eyediagram(filtered_signal, 40, 0.02); %plot eye diagram
title('Eye Diagram of Noiseless NRZ PAM Input'); %add title
xlabel('Time (s)'); %add x-axis label

eyediagram(filtered_signal_1010, 40, 0.02); %plot eye diagram
title('Eye Diagram for N=10 and 10% Noise Power'); %add title
xlabel('Time (s)'); %add x-axis label

eyediagram(filtered_signal_1025, 40, 0.02); %plot eye diagram
title('Eye Diagram for N=10 and 25% Noise Power'); %add title
xlabel('Time (s)'); %add x-axis label

eyediagram(filtered_signal_2020, 40, 0.02, 1); %plot eye diagram
title('Eye Diagram for N=20 and 20% Noise Power'); %add title
xlabel('Time (s)'); %add x-axis label