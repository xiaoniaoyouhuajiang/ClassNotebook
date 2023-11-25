let
  pkgs = import <nixpkgs> {};
  fetchgit-no-verify = pkgs.fetchgit // {
    __functor = self : args :
        (pkgs.fetchgit.__functor self args).overrideAttrs (oldAttrs:{GIT_SSL_NO_VERIFY=true;});
  };
  build = pkgs.callPackage ./package.nix {fetchgit = fetchgit-no-verify;};
in {
  inherit build;
  shell = pkgs.mkShell {
    inputsFrom = [build];
  };
}