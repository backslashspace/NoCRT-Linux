### Requirements
```bash
apt install g++ gdb gdbserver libc6 libc6-dev libstdc++6 libstdc++-14-dev lld
```

### GDB Intel Syntax Disassembly
```bash
echo "set disassembly-flavor intel" > ~/.gdbinit
```

### Build Debug
```bash
gcc \
  -std=gnu17 \
  -fPIE -static-pie \
  -fverbose-asm -save-temps=obj -masm=intel \
  -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -nolibc \
  -Og -g3 -ggdb -gdwarf-5 -mtune=native -march=native -fomit-frame-pointer \
  -Wall -Wextra -Wshadow -Wcast-qual -Wconversion -Wuseless-cast -Wuninitialized -Wduplicated-cond -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wduplicated-branches \
  -fuse-ld=lld \
  -Wl,-z,now \
  -Wl,--entry=Start \
  -Wl,-z,noexecstack \
  -Wl,--no-undefined \
  *.c \
  -o out/x64/Optimized-Debug/intermediate/optimized_debug.elf

mv out/x64/Optimized-Debug/intermediate/optimized_debug.elf out/x64/Optimized-Debug/linux_bases_test.elf
```