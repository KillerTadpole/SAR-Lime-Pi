% get SAR data
addpath('sar_lib')
mph2mps = 0.44704;
c = 3e8;
Fc = 2.475e9;

% filename = '../data/wavOfSlimData.wav'; % undersampled azimuth
% filename = '../data/15mphSARtrailerMedGain_keep40960_175Hzrep.wav';
% filename = '../data/15mphSARownHouseDir_keep40960_175Hzrep.wav';
% filename = '../data/15mphSARtrailerHighGain_keep40960_175Hzrep.wav';
% filename = '../data/15mphSARTrailerFar_keep40960_175Hzrep.wav';

short_chirp = GetChirpFrom_wfm('../data/the_chirp.wfm');
max_dist = 300; % meters
chirps_per_chunk = 10;
N_transmit_samps = 4096;
chunk_size = N_transmit_samps * chirps_per_chunk;
N_frames = chirps_per_chunk - 3;
[r_compressed, Fs] = peakParse(filename, short_chirp, max_dist, chunk_size, N_frames);
range_gate_s = 0;

% save data
% save('15mphTrailerFar.mat', 'r_compressed');
%% set constants
car_speed = 15; % miles per hour
% Tr = 1/20; % 20 Hz
F_pr = 175; % 20 Hz
T_pr = 1/F_pr; % 20 Hz
[temp,~] = size(short_chirp);
Tr = temp / Fs; % chirp duration
Vr = mph2mps * car_speed;
lambda = c / Fc;
theta3dB = deg2rad(25);
[N_az, Nrangesamp, n_frames] = size(r_compressed);
tau = (1:Nrangesamp)/Fs + range_gate_s;
ada = (1:N_az) * T_pr;
ada_m = ada * Vr;

% plot range compressed data
figure(1)
imagesc([tau(1), tau(end)]*c/2, ada_m, real(mean(r_compressed,3)))
xlabel('Range distance [m]')
ylabel('Azimuth distance [m]')
title('Real part of Received Signal')

figure(2)
imagesc([tau(1), tau(end)]*c/2, ada_m, abs(mean(r_compressed,3)))
xlabel('Range distance [m]')
ylabel('Azimuth distance [m]')
title('abs log part of Received Signal')

% Azmith compression
% make matched chirp filter for azimuth direction
Ka = -2*Vr^2 ./ (lambda * tau*c/2).';
az_chirp_len = 500; % pixles
az_Tr = az_chirp_len*T_pr;
f_start_az = az_Tr/2*(Ka);
az_chirp = makeChirp(f_start_az, az_Tr, F_pr, Ka, 0).';

% correlate matched chirp in azimuth
clear('az_compressed');
for i = 1:N_frames
    az_compressed(:,:,i) = fft_corr(az_chirp, r_compressed(:,:,i), 'A', -az_chirp_len/2);
end


% plot azimuth compression
figure(3)
imagesc([tau(1), tau(end)]*c/2,  ada_m, abs(mean(az_compressed,3)))
xlabel('Range distance [m]')
% mesh(abs(az_compressed))
% ylabel('Azimuth distance [m]')
title('Magnitude of Azimuth compressed signal')




