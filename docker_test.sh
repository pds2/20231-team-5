docker build -f Dockerfile.dependencies -t pds2_tp_dependencies .
docker build -f Dockerfile.tests -t pds2_tp_tests .
docker run -it pds2_tp_tests