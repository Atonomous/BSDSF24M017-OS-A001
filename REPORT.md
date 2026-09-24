# Assignment 01 Report

## Feature 2 Questions
1. **Linking Rule Comparison**: In `$(TARGET): $(OBJECTS)`, the linker directly binds compiled object files (`.o`) into a single executable binary. When linking against a library (`-L$(LIB_DIR) -lmyutils`), the linker searches the specified archive/shared file for unresolved symbols instead of combining all raw objects directly.
2. **Git Tags**: A git tag points to a specific commit to mark release checkpoints. A lightweight tag is merely a bookmark to a commit, while an annotated tag stores metadata (creator, timestamp, message, and GPG signature).
3. **GitHub Releases & Assets**: GitHub Releases provide end users packaged deployment artifacts. Attaching binary executables allows users to run the program without needing a local compiler or dependencies.

## Feature 3 Questions
1. **Makefile Differences**: Feature 3 separates compilation into archive building using the `ar` utility (`libmyutils.a`) and introduces library path flags (`-L`, `-l`) during the final linking stage.
2. **`ar` and `ranlib`**: The `ar` utility archives individual `.o` files into a single static library. `ranlib` generates an index to the contents inside the archive for faster symbol lookup during linking (handled automatically by modern `ar rcs`).
3. **`nm` Analysis**: Symbols like `mystrlen` appear in `client_static` because static linking physically extracts the compiled object code from the library and embeds it directly into the final executable.

## Feature 4 Questions
1. **Position-Independent Code (-fPIC)**: `-fPIC` emits machine code that uses relative address calculations rather than absolute memory addresses, allowing the dynamic library to be mapped to arbitrary virtual memory locations across multiple processes.
2. **File Size Comparison**: `client_static` contains the embedded binary code of the functions, whereas `client_dynamic` only contains reference stubs to resolve symbols at runtime, resulting in a smaller executable.
3. **LD_LIBRARY_PATH**: Informs dynamic linkers (`ld.so`) where to search for shared objects at runtime outside standard directories (`/usr/lib`).

