FROM rockylinux:9-minimal

RUN microdnf -y install \
        ca-certificates \
        clang \
        cmake \
        make \
        boost-devel \
    && microdnf clean all

WORKDIR /app
COPY . .

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build -j

ENTRYPOINT ["/app/build/tradesim"]
CMD ["10","100","1"]
