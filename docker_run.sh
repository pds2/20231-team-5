sudo dockerd -H unix:///var/run/docker.sock &

IMAGE=pds2_tp

docker build -t $IMAGE .
docker run -it $IMAGE clear; make clean; make main;echo -e "\n"; bin/main