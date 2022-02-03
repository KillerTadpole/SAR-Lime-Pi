
# run interactive podman with gui enabled
SAR_LIME_PI_DIR=~/Documents/sar_project/SAR-Lime-Pi

podman run -it \
	--rm \
	-e DISPLAY \
	-v /tmp/.X11-unix:/tmp/.X11-unix \
	--network=host \
	--privileged \
	--device=/dev/steam-2-3 \
	-v /dev:/dev \
	-v $SAR_LIME_PI_DIR:/home/SAR-Lime-Pi \
	--group-add keep-groups\
	--security-opt label=type:container_runtime_t \
	$1





