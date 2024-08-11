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
      dontStrip = true;
      buildInputs = with pkgs; [ boost cmake clang lldb clang-tools gtest gcc libcxx ];
      nativeBuildInputs = with pkgs; [ cmake ];
      #cmakeFlags = [ "-DCMAKE_BUILD_TYPE=Debug" "-DCMAKE_EXPORT_COMPILE_COMMANDS=1" ];
      installPhase = ''
        mkdir -p $out/bin
        cp tradesim $out/bin/
      '';
      shellHook = ''
        export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${pkgs.libcxx}/lib
      '';

    };
    devShell.${system} = pkgs.mkShell {
      buildInputs = [ pkgs.lldb pkgs.libcxx ];
    };
  };
}