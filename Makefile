all:
	clang -O3 --target=wasm32 -fno-builtin -nostdinc -emit-llvm -c -S fire.c rand.c engine.c
	llc -march=wasm32 -filetype=obj fire.ll
	llc -march=wasm32 -filetype=obj engine.ll
	llc -march=wasm32 -filetype=obj rand.ll
	wasm-ld --lto-O3 --no-entry --export=getDisplay --export=getScreenWidth --export=getScreenHeight --export=setup --export=update -o fire.wasm -z stack-size=8000000 fire.o rand.o engine.o
