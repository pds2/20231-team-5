sudo dockerd -H unix:///var/run/docker.sock &

IMAGE=pds2_tp

docker build -t $IMAGE .
docker run -it $IMAGE clear; make clean; make tests;echo -e "\n"; bin/tester