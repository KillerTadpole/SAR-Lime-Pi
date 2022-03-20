% testing the correlation function
sig = [4 4 4 4 4 4 0 0 0 0 0 0 0 0 0 0].';
match = sig; %circshift(sig, -2);

corr = fft_corr2(match, sig);

figure(1)
plot(corr)




