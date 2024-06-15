{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  name = "tradesim";
  nativeBuildInputs = [ pkgs.cmake pkgs.gcc pkgs.gnumake pkgs.autoPatchelfHook];
  buildInputs = [ pkgs.gnuplot pkgs.boost];

  src = pkgs.lib.cleanSource ./.;

  dontPatchELF = false;

  configurePhase = ''
    # mkdir build
    # cd build
    # cmake ..
    cmake .
  '';

  buildPhase = ''
    # cd build
    make
  '';

  installPhase = ''
    runHook preInstall
    mkdir -p $out/bin
    cp tradesim $out/bin
    runHook postInstall
  '';
}