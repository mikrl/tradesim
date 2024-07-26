{
  description = "tradesim";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }: let
    system = "x86_64-linux";
    pkgs = import nixpkgs { inherit system; };
  in
  {
    defaultPackage.${system} = pkgs.stdenv.mkDerivation {
      name = "tradesim";
      src = self;
      buildInputs = [ pkgs.boost pkgs.cmake ];
      configurePhase = ''
        mkdir build
        cd build
        cmake ..
      '';
      buildPhase = ''
        make
      '';
      installPhase = ''
        mkdir -p $out/bin
        cp tradesim $out/bin/
      '';
    };
  };
}