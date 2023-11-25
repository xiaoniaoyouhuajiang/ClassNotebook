{ lib, stdenv, fetchgit, wrapProgram }:
stdenv.mkDerivation {
    name = "sort-bench";
    nativeBuildInputs = [
        wrapProgram
    ];
    src = fetchgit {
        url = "https://github.com/travisdowns/sort-bench.git";
        sha256 = "H6xx"
    };

    installPhase = ''
      mkdir -p $out/bin
      cp bench $out/bin
      chmod +x $out/bin/bench
    '';
}