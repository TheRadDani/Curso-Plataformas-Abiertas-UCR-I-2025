FROM ubuntu:22.04

# Install MPICH and dependencies
RUN apt-get update && \
    apt-get install -y mpich python3 python3-pip iputils-ping && \
    pip3 install mpi4py

# Copy files
COPY mpi_hello.py hosts.txt /app/
WORKDIR /app

# Configure MPICH environment
ENV MPICH_VERSION=4.1.2
ENV MPICH_DISABLE_SLOTS=1