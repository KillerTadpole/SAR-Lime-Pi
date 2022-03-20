function data = getRawData(file_name)

fid = fopen(file_name);
chirp_iq = fread(fid,'int16');
chirp_iq = reshape(chirp_iq, 2, []).';
data = complex(chirp_iq(:,1), chirp_iq(:,2));
fclose(fid);
end