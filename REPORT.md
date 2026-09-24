# Operating Systems — Assignment 01 Report
**Student Roll No:** BSDSF24M017  
**Module:** Core C Utilities Library (`libmyutils`)

---

## Part 2: Multi-file Project using Make Utility

### 1. Explain the linking rule `$(TARGET): $(OBJECTS)`. How does it differ from linking against a library?
* **Direct Object Linking (`$(TARGET): $(OBJECTS)`):** The linker (`ld` via `gcc`) consumes all precompiled translation units (`.o` files) together and combines their symbol tables and text segments into a single executable binary. Every object explicitly passed is incorporated.
* **Linking Against a Library (`-L$(DIR) -lmyutils`):** The linker searches an archive (`.a`) or shared object (`.so`) only to resolve outstanding unresolved symbol references. In static archives, only object members providing needed symbols are extracted. In dynamic linking, the library is not copied into the executable at all; instead, references and import tables are created for resolution at runtime.

### 2. What is a git tag and why is it useful? Difference between simple and annotated tags?
* **Purpose:** A git tag is a fixed reference pointing to a specific commit in repository history, commonly used to mark release milestones (e.g., `v1.0.0`).
* **Lightweight vs. Annotated:**
  * **Lightweight Tag:** Simply a pointer (like an immutable branch reference) to a specific commit hash. It contains no extra metadata.
  * **Annotated Tag:** Stored as a complete Git object in the database. It stores the tagger's name, email, timestamp, an explicit tagging message, and supports GPG cryptographic signing.

### 3. Purpose of a GitHub "Release" and significance of attaching binaries?
* **Purpose:** A GitHub Release packages software iterations for end-users, providing structured release notes, changelogs, and download links tied directly to a git tag.
* **Significance of Binary Assets:** Standard users often lack development environments, specific toolchains, or dependency headers. Distributing precompiled binaries (`client`, `.a`, `.so`) lets users install and execute programs immediately without needing to invoke `gcc` or `make`.

---

## Part 3: Static Library Build

### 1. Key differences in Makefile variables and rules between Part 2 and Part 3?
* **Part 2:** Compiled all source files directly into individual objects and linked them simultaneously using standard object rules: `$(CC) $(OBJ) -o $(TARGET)`.
* **Part 3:** 
  * Introduced archive tool definitions: `AR = ar` and flags `ARFLAGS = rcs`.
  * Added an intermediate target rule to construct the archive `$(LIB_DIR)/libmyutils.a` from the library utility object files.
  * Modified the target executable linking recipe to consume linker search flags: `-L$(LIB_DIR) -lmyutils`.

### 2. Purpose of `ar` and why `ranlib` is often used after it?
* **`ar` (Archiver):** Bundles collections of independent object files (`.o`) into a single archive file (`.a`), preserving individual member headers.
* **`ranlib`:** Generates an index/symbol table mapping symbol names to the respective member object containing them inside the archive, accelerating symbol lookup during linking. Modern GNU `ar` executes this step automatically when invoked with the `s` flag (`ar rcs`).

### 3. Symbol inspection via `nm` on `client_static`:
* **Observation:** Running `nm bin/client_static | grep mystrlen` reveals that `mystrlen` is defined with a symbol type `T` (Text section) in the executable.
* **Implication:** In static linking, the linker physically copies the machine code of the referenced functions from `libmyutils.a` directly into the final executable image. The binary contains its own independent copy of the library code.

---

## Part 4: Dynamic Library Build

### 1. Position-Independent Code (`-fPIC`) and why it is required for shared libraries:
* **Explanation:** Position-Independent Code generates machine instructions using relative addressing offsets (e.g., Program Counter-relative addressing and Global Offset Tables) instead of hardcoded absolute virtual memory addresses.
* **Requirement:** Shared libraries (`.so`) are loaded into arbitrary, non-predetermined addresses across the address spaces of different running processes. `-fPIC` allows the OS kernel to share a single read-only copy of the code section in physical RAM among multiple processes.

### 2. Difference in file size between `client_static` and `client_dynamic`:
* **Explanation:** `client_static` is larger because the linker copies the compiled byte code of all referenced utility functions directly into the binary's `.text` section. `client_dynamic` is significantly smaller because it contains only a `.dynamic` section, Procedure Linkage Table (PLT), Global Offset Table (GOT), and symbol reference strings; the actual logic resides in the external `libmyutils.so` file.

### 3. `LD_LIBRARY_PATH` and Dynamic Loader Responsibilities:
* **`LD_LIBRARY_PATH`:** An environment variable providing an ordered list of custom directories for the system dynamic linker (`ld.so`/`ld-linux.so`) to inspect prior to searching standard system directories (`/lib`, `/usr/lib`).
* **Why required:** Custom libraries residing in local directories (such as `./lib`) are not within the kernel's default library cache (`/etc/ld.so.cache`). The loader refuses execution with an unresolved object error unless explicitly told where to discover `libmyutils.so`. This demonstrates that the dynamic loader operates at execution time, decoupling binary distribution from internal library implementation.
