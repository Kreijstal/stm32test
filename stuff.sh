cbindgen --config cbindgen.toml --crate hellowrold --output header.h

cargo build --lib --target thumbv7em-none-eabihf
gcc -o ../target/h h.c ../target/debug/libhellowrold.a
