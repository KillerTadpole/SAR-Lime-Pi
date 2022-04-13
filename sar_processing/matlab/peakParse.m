% peak parcer
function [M, Fs] = peakParse(wav_file, corr_chirp, range_gate, chunk_size, N_frames)
% figure out chunck sizing
c = 3e8;
start = 1;
stop = chunk_size;
[IQ, Fs] = getComplexSamps(wav_file, start, stop);
rg_samps = floor(range_gate * 2 / c * Fs);

% get min value for cross talk peak
compressed = fft_corr(corr_chirp, IQ);
figure(23)
plot(abs(compressed))
title("Select a height to capture peaks")
[~, min_peak_hight] = ginput(1);
close(23)

fs = Fs;
cnt = 1;
M = [];
while fs
    compressed = fft_corr(corr_chirp, IQ);
    [pks, inds] = findpeaks(abs(compressed),'MinPeakHeight', min_peak_hight);
    % average across chunk
    for i = 2:length(pks)-1
        A(i,:) = compressed(inds(i):inds(i)+rg_samps);
    end
    % add averaged chunk to data matrix
    M(cnt,:,:) = A(2:N_frames+1,:).';%mean(A);
    if cnt == 6750
        figure(23)
        plot(abs(M(cnt,:,4)))
        pause
    end
    cnt = cnt+1;
    start = stop+1;
    stop = start + chunk_size - 1;
    [IQ, fs] = getComplexSamps(wav_file, start, stop);
end
end

function [y, fs] = getComplexSamps(file_name, start, stop)
try
    [x, fs] = audioread(file_name, [start, stop]);
    y = complex(x(:,1), x(:,2));
catch
    fs = 0;
    y = [];
end
end







