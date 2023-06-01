FROM ubuntu:latest

# Create app directory
RUN mkdir -p /mini_project


# Copy the current directory contents into the container
COPY . /mini_project

RUN apt-get update

# Install necessary packages only if they are not already installed
RUN apt-get install -y --no-install-recommends \
    alsa-utils \
    pulseaudio \
    libncurses5-dev \
    gcc \
    make \
    git \
    libjson-c-dev \
    python3 \
    $(apt-cache --names-only search '^<package-name>' | awk '{ print $1 }' | xargs echo)



