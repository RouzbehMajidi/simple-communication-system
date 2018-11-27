data1 = importdata('../data/Task4/NRZ_PAM_no_noise_10.dat'); %import NRZ PAM data N=10
data2 = importdata('../data/Task4/NRZ_PAM_no_noise_20.dat'); %import NRZ PAM data N=20
eyediagram(data1, 20, 0.02, 4); %draw eye diagram for N=10
title('Eye Diagram for N=10'); %add title
xlabel('Time (s)'); %add x-axis label
eyediagram(data2, 40, 0.02, 9); %draw eye diagram for N=20
title('Eye Diagram for N=20'); %add title
xlabel('Time (s)'); %add x-axis label

