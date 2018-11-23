clear;
desired_error_dB = 0.05;
desired_error = 10^(desired_error_dB/10)

lambda_factor = @(N) desired_error - ((4*pi)./N)./(1-exp(-((4*pi)./N)));


ceil(fsolve(lambda_factor, 10))
