{
  description = "fmt torture test for mc-rtc types";

  inputs.mc-rtc-nix.url = "github:mc-rtc/nixpkgs";

  outputs =
    inputs:
    inputs.mc-rtc-nix.lib.mkFlakoboros inputs (
      { lib, ... }:
      {
        packages = {
          fmt-torture-test =
            {
              stdenv,
              cmake,
              catch2_3,
              fmt,
              spacevecalg,
              ...
            }:
            stdenv.mkDerivation {
              name = "fmt-torture-test";
              src = lib.cleanSource ./.;
              nativeBuildInputs = [ cmake ];
              propagatedBuildInputs = [
                fmt
                spacevecalg
                catch2_3
              ];

              cmakeFlags = [ ];
              doCheck = true;
              dontInstall = true;

              meta = with lib; {
                description = "fmt library torture test on mc-rtc types";
                homepage = "https://github.com/arntanguy/fmt-torture-test";
                license = licenses.bsd2;
                platforms = platforms.all;
              };
            };
        };
      }
    );
}
