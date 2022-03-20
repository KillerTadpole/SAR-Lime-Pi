% script looking at correlation artifacts
file_name = "../data/50MHzchirp1536Samples_2048TotSamp.wfm";

fid = fopen(file_name);
chirp_iq = fread(fid,'int16', 'ieee-be');
chirp_iq = reshape(chirp_iq, 2,[]).';
chirp_w_z = complex(chirp_iq(:,1), chirp_iq(:,2));
fclose(fid);
sig = repmat(chirp_w_z, 80, 1);

corr_chirp = GetChirpFrom_wfm(file_name);

%% plot signals
% figure(1)
% plot(real(sig))
% hold on
% plot(real(corr_chirp))
% hold off


%% plot correlation
compressed = fft_corr(corr_chirp, sig);

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
rg = 1536;
clear('M')
for i = 1:length(pks)-1
    M(i,:) = sig(inds(i):inds(i)+rg);
end

rec_avg = mean(M);
size(rec_avg)
rec_avg = fft_corr(corr_chirp, rec_avg.');

figure(4)
plot(log10(abs(rec_avg)))

