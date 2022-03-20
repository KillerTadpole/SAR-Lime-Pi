% peak parcer
function [M, Fs] = peakParse(wav_file, corr_chirp, range_gate, avgs)
% figure out chunck sizing
start = 1;
stop = 2e20;
[y, fs] = getComplexSamps(wav_file, start, stop);

%% plot correlation

compressed = fft_corr(IQ, corr_chirp);

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
clear('M')
for i = 1:length(pks)-1
    M(i,:) = compressed(inds(i):inds(i)+rg);
end

rec_avg = mean(M);

figure(2)
plot(log10(abs(rec_avg)))

end

function [y, fs] = getComplexSamps(file_name, start, stop)
[x, fs] = audioread(file_name, [start, stop]);
y = complex(x(:,1), x(:,2));
end







