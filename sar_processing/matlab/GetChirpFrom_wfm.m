function chirp = GetChirpFrom_wfm(file_name)

fid = fopen(file_name);
chirp_iq = fread(fid,'int16', 'ieee-be');
chirp_iq = reshape(chirp_iq, 2,[]).';
chirp_w_z = complex(chirp_iq(:,1), chirp_iq(:,2));
chirp = chirp_w_z(find(chirp_w_z, 1, 'first'):find(chirp_w_z, 1, 'last'));
fclose(fid);
end