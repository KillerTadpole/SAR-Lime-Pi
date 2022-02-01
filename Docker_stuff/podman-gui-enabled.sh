
# run interactive podman with gui enabled

podman run -it --rm -e DISPLAY \
	   -v /tmp/.X11-unix:/tmp/.X11-unix \
	   --security-opt label=type:container_runtime_t $1






