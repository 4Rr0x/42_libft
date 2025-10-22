<p align="center">
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C badge">
  <img src="https://img.shields.io/badge/Make-427819?style=for-the-badge&logo=cmake&logoColor=white" alt="Make badge">
  <img src="https://img.shields.io/badge/Shell-4EAA25?style=for-the-badge&logo=gnu-bash&logoColor=white" alt="Shell badge">
  <img src="https://img.shields.io/badge/Valgrind-773344?style=for-the-badge&logo=gnu&logoColor=white" alt="Valgrind badge">
  <img src="https://img.shields.io/badge/GDB-800000?style=for-the-badge&logo=gnu&logoColor=white" alt="GDB badge">
</p>
<h1 align="center">Libft (extended)</h1>
<p align="center">Reusable C building blocks with an in-repo tester tuned for 42 project evaluations.</p>

1. [At a Glance](#at-a-glance)
2. [About This Library](#about-this-library)
3. [Subject Compliance](#subject-compliance)
4. [Repository Layout](#repository-layout)
5. [Build & Integration](#build--integration)
6. [Usage Guidelines](#usage-guidelines)
7. [Feature Deep Dive](#feature-deep-dive)
8. [Input & Validation](#input--validation)
9. [Rendering & Output](#rendering--output)
10. [Internal Architecture](#internal-architecture)
11. [Tester Workflow](#tester-workflow)
12. [Results & Reporting](#results--reporting)

## At a Glance
> **Highlights:** Static C library covering all mandatory libft calls plus field-tested helpers.
- Ships 40+ string, memory, FD, conversion, and list routines backed by `libft.a`.
- Adds practical extras (`ft_atol`, `ft_isnumeric`, `ft_max`, `ft_str_append_char`) proven useful in later 42 milestones.
- Bundles local copies of `printf/` and `gnl/` so dependent projects link without external fetches during defense.
- Includes a colorized regression tester under `.testers/libft` to preflight submissions.

## About This Library
> **Highlights:** Norm-compliant foundations with pragmatic ergonomics.
- Written in pure C, respecting 42 Norm guidelines and minimal dependencies (standard headers only inside `libft/`).
- Favors readability: short helpers like `ft_words_counter` keep complex flows (e.g., `ft_split`) approachable for peer review.
- Optional utilities sit alongside mandatory functions but remain header-gated so downstream repos can opt in selectively.
- Memory ownership is explicit—every allocator returns heap pointers that callers must release (tester cross-checks accidental leaks).

## Subject Compliance
> **Highlights:** Matches the scope mandated in `docs/subject_libft.pdf` while flagging deviations.
- Mandatory Part 1/2 functions mirror prototypes and behavior described on pages 7–12 of the subject PDF.
- Bonus linked-list API implements the full `t_list` toolchain in `libft/`, meeting bonus segregation rules.
- Makefile exposes `all`, `clean`, `fclean`, and `re`, compiles with `-Wall -Wextra -Werror`, and avoids needless relinks via object caching in `obj/`.
- Extra helpers stay within subject constraints; only `ft_swapstrs` currently behaves as a pointer swap stub (planned refinement noted below).

<details>
<summary>Covered functions</summary>

- Character/ctype checks, core string/memory routines, conversion helpers, FD printers
- Full linked-list API (`ft_lst*`) with content-aware assertions and cleanups
- Current scope excludes newer helpers like `ft_isnumeric` or `ft_str_append_char`; see Feature Deep Dive for intended expansion
</details>

## Repository Layout
> **Highlights:** Flat structure keeps evaluation navigation fast.
- `docs/subject_libft.pdf` — official 42 brief kept alongside the repo for audits.
- `libft/` — implementation sources plus `libft.h` covering mandatory and bonus APIs.
- `.testers/libft/` — tester harness (`tests.c`, `functions/`, `run_tests.sh`, `results.txt`).
- `printf/` & `gnl/` — local working copies cloned once, stripped of history, ready for downstream linking.
- `obj/` — build artifacts created by the Makefile; safe to delete via `make clean`.
- `libft.a` — compiled static archive; regenerated on each `make`.

## Build & Integration
> **Highlights:** Default target prepares dependencies then produces `libft.a`.
- `make` ensures `printf/` and `gnl/` exist (cloning only if missing), creates `obj/`, and archives every `.o` into `libft.a`.
- `make clean` clears objects, `make fclean` also removes `libft.a` plus the cloned dependency folders for a true fresh start.
- `make re` chains `fclean` then `all`, rebuilding the full toolchain in one go.
- Compilation stays deterministic: no hidden flags, and every translation unit uses the same warning set.

```sh
make          # build libft.a (clones printf/gnl if absent)
make clean    # remove obj/
make fclean   # clean + remove libft.a, printf/, gnl/
make re       # force pristine rebuild
```

## Usage Guidelines
> **Highlights:** Intended for reuse across 42 repos without manual tweaking.
- Include with `#include "libft/libft.h"` or adjust include paths to suit your project layout.
- Link the archive via `cc your_main.c ../libft.a` or add `-L`/`-lft` flags inside larger build systems.
- Keep helper usage optional: if a downstream subject forbids extras, only call functions present in the official PDF.
- Re-run `.testers/libft/run_tests.sh` after edits; failed cases flag mismatches immediately through `results.txt`.

## Feature Deep Dive
> **Highlights:** Modular helpers organized by use case.
- String toolkit ranges from safe copying (`ft_strlcpy`, `ft_strlcat`) to builders (`ft_strjoin`, `ft_strtrim`, `ft_split`).
- Memory primitives (`ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_calloc`) offer low-level control without hidden allocations.
- Numeric conversions include defensive parsing (`ft_atoi`, `ft_atol`) and formatting via `ft_itoa` for FD output helpers.
- Linked-list suite (`ft_lstnew` through `ft_lstmap`) follows the subject spec, with tester coverage for iterator/map corner cases.

<details>
<summary>Helper spotlight</summary>

- `ft_isnumeric` validates optional sign + digits for gatekeeping user input before conversion.
- `ft_str_append_char` rebuilds buffers incrementally; it frees the old pointer on failure to prevent leaks.
- `ft_swapstrs` currently swaps pointer values locally; plan to extend it to swap caller buffers once references are passed by address.
- `ft_max` provides a tiny arithmetic utility for readability when normalizing bounds.
</details>

## Input & Validation
> **Highlights:** Tolerant parsing with explicit whitespace handling.
- `ft_iswhitespace` and `ft_isspace` distinguish control-space vs. literal space to tune tokenizers.
- `ft_atoi` rejects duplicate leading signs (`--`, `++`) to avoid silent UB before conversion.
- `ft_atol` mirrors that behavior for wider ranges, enabling safe bounds checks before casting back to `int`.
- `ft_isnumeric` treats standalone signs as invalid, ensuring only well-formed numeric strings pass validation.

<details>
<summary>Edge-case considerations</summary>

- Current converters do not guard against multiplication overflow; confirm input spans before calling on untrusted data.
- Whitespace helpers return `bool`/`int` according to their prototypes, so prefer them over duplicating ASCII tables.
</details>

## Rendering & Output
> **Highlights:** File-descriptor oriented presentation utilities.
- `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, and `ft_putnbr_fd` centralize writes for stdout/stderr or custom descriptors.```sh
cd .testers/libft
./run_tests.sh
```

- Tester fixtures open temp files to confirm exact byte sequences and clean them post-run.
- `ft_strmapi` and `ft_striteri` support character-by-character transformations, handy before printing formatted strings.
- Combined with `ft_printf` (bundled sibling repo), `libft.a` covers both low-level writes and formatted output pipelines.

## Internal Architecture
> **Highlights:** Simple directory discipline keeps maintenance low.
- `libft.h` declares every public symbol and `t_list` struct, keeping prototypes centralized for IDE assistance.
- Object files live in `obj/` with filenames derived via `$(notdir ...)`, preventing collisions across modules.
- The Makefile defers `lib` compilation until directories exist, ensuring `printf/` and `gnl/` remain in sync without recursive makes.
- Bonus sources share the primary folder; `_bonus` naming is unnecessary because the subject allows this layout for libft.

## Tester Workflow
> **Highlights:** Mirrors evaluator behavior start-to-finish.
- Builds a test binary (`tests`) alongside `libft.a`, keeping artifacts inside `.testers/libft` for easy cleanup.
- Executes every function suite sequentially, writing verdicts to `results.txt` for archival or sharing with peers.
- Highlights failures immediately with expected vs. actual values in the same line for quick debugging.
- Relies on `libbsd` only for reference implementations (`strlcpy`, `strlcat`); macOS users already have them in libc.

<details>
<summary>Extending coverage</summary>

- Add new `.c` files under `.testers/libft/functions/` and declare their prototypes in `tester.h` to include them in the sweep.
- Re-run the script; the `find` command auto-discovers added tests without touching the Makefile.
</details>

## Results & Reporting
> **Highlights:** Actionable logs without noise.
- `results.txt` collects one line per function (SUCCESS/KO with context) so reviewers can skim outcomes quickly.
- `run_tests.sh` streams colored copies of those lines to stdout and ends with a success/total tally.
- Failures display expected vs. actual payloads (buffers, substrings, numeric values) to reduce reproduction time.
- Clean-up step deletes temporary FD fixtures, keeping the tester tree tidy between runs.

```sh
sed -n '1,10p' .testers/libft/results.txt   # quick glance after a run
```

<details>
<summary>Next steps after a failure</summary>

- Re-run the relevant test file directly under `cc` with `-g` if you need to attach `lldb` or `gdb`.
- Compare against glibc/bsd behavior using the inline references already present inside each tester function.
</details>
