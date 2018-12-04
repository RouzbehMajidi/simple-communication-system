data1 = importdata('../data/Task5/NRZ_PAM_with_noise_10_0.1.dat'); %import NRZ PAM data N=10 10% noise power
data2 = importdata('../data/Task5/NRZ_PAM_with_noise_10_0.25.dat'); %import NRZ PAM data N=10 25% noise power
data3 = importdata('../data/Task5/NRZ_PAM_with_noise_20_0.1.dat'); %import NRZ PAM data N=20 10% noise power
data4 = importdata('../data/Task5/NRZ_PAM_with_noise_20_0.25.dat'); %import NRZ PAM data N=20 25% noise power
eyediagram(data1, 20, 0.02, 4); %draw eye diagram for 10% noise power
title('Eye Diagram for N=10 and 10% Noise Power'); %add title
xlabel('Time (s)'); %add x-axis label
eyediagram(data2, 20, 0.02, 4); %draw eye diagram for 25% noise power
title('Eye Diagram for N=10 and 25% Noise Power'); %add title
xlabel('Time (s)'); %add x-axis label
eyediagram(data3, 40, 0.02, 9); %draw eye diagram for 10% noise power
title('Eye Diagram for N=20 and 10% Noise Power'); %add title
xlabel('Time (s)'); %add x-axis label
eyediagram(data4, 40, 0.02, 9); %draw eye diagram for 25% noise power
title('Eye Diagram for N=20 and 25% Noise Power'); %add title
xlabel('Time (s)'); %add x-axis label

