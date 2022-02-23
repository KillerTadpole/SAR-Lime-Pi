% Add these paths once
% addpath('sar_lib/')
% addpath('.')
% load('../data/DumpsterChirp2_16b50mhz256clen.mat')
fid = fopen('../data/LimeRxData/256Chirp2048Tot_Krate5.8594e12_50MHzBW.wfm');
IQ = reshape(IQ, [], 1);
chirp_iq = fread(fid,'int16', 'ieee-be');
chirp_iq = reshape(chirp_iq, 2,[]).';
chirp = complex(chirp_iq(:,1), chirp_iq(:,2));

%% plot time domain
figure(1)
plot(abs(IQ))
% %% plot chirp
% figure(2)
% plot(abs(chirp(1:256)))
% 
% 
% %% plot freq donain
% IQ_fft = fftshift(fft(IQ));
% figure(2)
% plot(abs(IQ_fft))

%% plot correlation
compressed = fft_corr(IQ, chirp(1:256));

figure(23)
plot(abs(compressed))
title("Select a height to capture peaks")

%% find peaks
[~, y] = ginput(1);

[pks, inds] = findpeaks(abs(compressed),'MinPeakHeight', y);

hold on
stem(inds, pks)
hold off

%% stack matrix
rg = 1000;
for i = 1:length(pks)-1
    M(i,:) = compressed(inds(i):inds(i)+rg);
end

rec_avg = mean(M);

figure(22)
plot(log10(abs(rec_avg)))











