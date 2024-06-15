FROM nixos/nix:latest

RUN nix-channel --update
# Set the working directory in the container to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
ADD . /app

# Make port 80 available to the world outside this container
EXPOSE 31337

# Run cmake . && make when the container launches
RUN nix-build

# Run the output program from the previous step
ENTRYPOINT ["/bin/sh"]