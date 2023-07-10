docker build -f Dockerfile.dependencies -t pds2_tp_dependencies .
docker build -f Dockerfile.main -t pds2_tp_main .
docker run -it pds2_tp_main