FROM nixos/nix:latest AS build

ENV NIX_CONFIG="experimental-features = nix-command flakes"
WORKDIR /app
COPY . .
RUN nix build .#defaultPackage.x86_64-linux

FROM nixos/nix:latest

ENV NIX_CONFIG="experimental-features = nix-command flakes"
RUN nix profile install nixpkgs#gnuplot
ENV PATH="/root/.nix-profile/bin:${PATH}"
ENV GNUTERM=dumb

WORKDIR /app
COPY --from=build /app/result /app/result

ENTRYPOINT ["/app/result/bin/tradesim"]
CMD ["10","100","1"]
