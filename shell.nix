{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.cmake
    pkgs.boost
  ];

  shellHook = ''
    export CMAKE_PREFIX_PATH="${pkgs.boost}/include"  '';
}