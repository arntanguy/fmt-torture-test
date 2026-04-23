{
  description = "fmt torture test for mc-rtc types";

  inputs.mc-rtc-nix.url = "github:mc-rtc/nixpkgs";

  outputs =
    inputs:
    inputs.mc-rtc-nix.lib.mkFlakoboros inputs (
      { lib, ... }:
      {
        extends.fmt_9 = final: _prev: { fmt = final.fmt_9; };
        extends.fmt_10 = final: _prev: { fmt = final.fmt_10; };
        extends.fmt_11 = final: _prev: { fmt = final.fmt_11; };
        extends.fmt_12 = final: _prev: { fmt = final.fmt_12; };

        # FIXME: building with pkgs-fmt_10 causes qt6base to rebuild
        # even though nothing here depends on it.
        # This is due to flakoboros' ros overlay here
        # https://github.com/Gepetto/flakoboros/blob/main/lib/mk-lib.nix#L95
        overlays = [
          (_final: _: {
            qt6.qtbase = null;
            qt6.wrapQtAppsHook = null;
          })
        ];

        packages = {
          fmt-torture-test =
            {
              stdenv,
              cmake,
              catch2_3,
              fmt,
              eigen-fmt,
              spacevecalg,
              rbdyn,
              boost, # for testing boost::filesystem::path
              ...
            }:
            stdenv.mkDerivation {
              name = "fmt-torture-test";
              src = lib.cleanSource ./.;
              nativeBuildInputs = [ cmake ];
              propagatedBuildInputs = [
                fmt
                spacevecalg
                rbdyn
                catch2_3
                eigen-fmt
                boost
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
