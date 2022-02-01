
# pull fedora image
ctr=$(buildah from fedora)
# set path variable
buildah config --env GOPATH=/root/buildah $ctr

buildah run dnf install xeyes
buildah run dnf install xorg-x11-apps-Xorg























