FROM ubuntu:latest

# Create app directory
RUN mkdir -p /mini_project

# Set the working directory
WORKDIR /mini_project

# Copy all files to the container
COPY . /mini_project

# Install necessary packages
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    alsa-utils \
    pulseaudio \
    libncurses5-dev \
    gcc \
    make

