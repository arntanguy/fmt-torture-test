# Copilot Cloud Agent instructions for `arntanguy/fmt-torture-test`

## What this repository is
`fmt-torture-test` is a small C++ “torture test” project used to validate that **multiple versions of the `fmt` library** can format **mc-rtc–related types** (notably Eigen + SpaceVecAlg) without breaking `fmt` ranges behavior. The repository builds a single test executable that prints formatted values and asserts formatting does not fail/return empty strings.

### High-level characteristics
- **Project type:** Nix flake (authoritative) + CMake-based C++ project.
- **Primary language/runtime:** C++17.
- **Canonical build entrypoint:** `nix build` (always).
- **CI strategy:** GitHub Actions runs Nix builds for multiple `fmt` versions.

## Key dependencies (provided by Nix)
The build expects (and Nix provides) the following libraries:
- `fmt`
- Boost (`filesystem`, `unit_test_framework`)
- `Eigen3`
- `eigen-fmt`
- `RBDyn`
- `SpaceVecAlg`

Do not attempt to “fix” missing system packages by adding ad-hoc install steps; rely on the flake.

## Project layout (where to look first)
- `flake.nix` / `flake.lock` — **source of truth** for builds, CI, and supported `fmt` variants.
- `CMakeLists.txt` — defines the `torture-fmt` executable and wires it into CTest.
- `include/fmt_formatters.h` — core formatter logic and `FMT_VERSION` conditionals.
- `test/torture_fmt.cpp` — Boost.Test suite; this is the primary behavior/regression coverage.
- `.github/workflows/nix.yml` — CI runs the Nix build matrix.

Repo root inventory (quick reference):
- `.github/`
- `.gitignore`
- `.mergify.yml`
- `.pre-commit-config.yaml`
- `CMakeLists.txt`
- `README.md`
- `flake.nix`, `flake.lock`
- `include/`
- `test/`

## Nix build / test (authoritative workflow)
### Always build through Nix
This repository is **always built through Nix**. Use Nix commands as the only build/test interface.

### Build targets (and run unit tests)
Build the default package:
- `nix build -L`

Build and validate against a specific `fmt` version (mirrors CI intent):
- `nix build -L .#pkgs-fmt_8`
- `nix build -L .#pkgs-fmt_9`
- `nix build -L .#pkgs-fmt_10`
- `nix build -L .#pkgs-fmt_11`
- `nix build -L .#pkgs-fmt_12`

**Important:** `nix build -L .#pkgs-fmt_<version>` also runs the unit tests (`doCheck = true`) and displays their output in the build logs.

### Flake checks (optional; CI also runs it)
CI runs `nix flake check -L` in addition to builds. If you want to mirror CI locally:
- `nix flake check -L`

### Known notes
- `flake.nix` mentions a potential large rebuild when building with `pkgs-fmt_10` due to an upstream overlay interaction; a workaround overlay is already present. Avoid removing/changing it unless necessary.

## Conventions / change guidance
- Keep changes compatible with **C++17**.
- Be careful with `fmt` version conditionals in `include/fmt_formatters.h`:
  - `FMT_VERSION >= 9*10000` is a key boundary (ostream auto-discovery removal).
  - Avoid changes that reintroduce `fmt/ranges` ambiguity for Eigen types (the file explicitly disables `fmt/ranges` for Eigen types to prevent ambiguous formatter instantiation).

## Trust these instructions
Prefer the commands and entrypoints documented above and only search the repo further if something is missing or contradicts these instructions (e.g., if CI or flake outputs change).