with import <nixpkgs> {};
let
  pythonenv = ( let
    nfoursid = python310.pkgs.buildPythonPackage rec {
        pname = "nfoursid";
        version = "1.0.1";
        src = fetchPypi {
            inherit pname version;
            hash = "sha256-1IHorVjxnrpCkkmOpP0TJFcqMcd2/mzyyndOpCRIwEs=";
        };
        nativeBuildInputs = [
            python310.pkgs.setuptools
            python310.pkgs.wheel
        ];

        doCheck = false;

        meta = {
            homepage = "https://github.com/spmvg/nfoursid";
        };
    };

    in python310.withPackages (ps: with ps; [
        pandas
        scikit-learn
        matplotlib
        nfoursid
    ])
  );
in mkShell {
    packages = [
        pythonenv
        ipmitool
    ];
}
