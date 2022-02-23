function chirp = makeChirp(f_start, Tr, Fs, K, phase)

t_chirp = ((1:floor(Tr*Fs))-1)/Fs;
chirp = exp(1j*(phase + 2*pi*f_start.*t_chirp + pi*K*t_chirp.^2));

end