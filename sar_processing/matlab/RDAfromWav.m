% get SAR data
addpath('sar_lib')
mph2mps = 0.44704;
c = 3e8;
Fc = 2.45e9;

short_chirp = GetChirpFrom_wfm('../data/the_chirp.wfm');
max_dist = 200; % meters
chunk_size = 4096 * 20;
[s0, Fs] = peakParse('../data/wavOfSlimData.wav', short_chirp, max_dist, chunk_size);
range_gate_s = 0;

car_speed = 20; % miles per hour
% Tr = 1/20; % 20 Hz
F_pr = 20; % 20 Hz
T_pr = 1/F_pr; % 20 Hz
Vr = mph2mps * car_speed;
lambda = c / Fc;
theta3dB = deg2rad(25);
[N_az, Nrangesamp] = size(s0);
tau = (1:Nrangesamp)/Fs + range_gate_s;
ada = (1:N_az) * T_pr;
ada_m = ada * Vr;

% plot range compressed data
figure(1)
imagesc([tau(1), tau(end)]*c/2, ada_m, real(s0))
xlabel('Range distance [m]')
ylabel('Azimuth distance [m]')
title('Real part of Received Signal')

figure(2)
imagesc([tau(1), tau(end)]*c/2, ada_m, log10(abs(s0)))
xlabel('Range distance [m]')
ylabel('Azimuth distance [m]')
title('abs log part of Received Signal')

%% Azmith compression
% make matched chirp filter for azimuth direction
Ka = -2*Vr^2 * cos(theta3dB)^2 ./ (lambda * tau*c/2).';
az_chirp_len = 800; % pixles
az_Tr = az_chirp_len*T_pr;
f_start_az = az_Tr/2*(-Ka);
az_chirp = makeChirp(f_start_az, az_Tr, F_pr, Ka, 0).';

% correlate matched chirp in azimuth
az_compressed = fft_corr(az_chirp, s0, 'A', -az_chirp_len/2);

% plot azimuth compression
figure(3)
imagesc([tau(1), tau(end)]*c/2,  ada_m, log10(abs(az_compressed)))
xlabel('Range distance [m]')
% mesh(abs(az_compressed))
% ylabel('Azimuth distance [m]')
title('Magnitude of Azimuth compressed signal')



