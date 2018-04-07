#!/usr/bin/env bash

readonly SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE); pwd)
readonly LLVM_REPO=${LLVM_REPO:-https://git.llvm.org/git/llvm.git/}
readonly CLANG_REPO=${CLANG_REPO:-https://git.llvm.org/git/clang.git/}

readonly LLVM_REVISION="5539442a8f84ed62ecc28cc5e3ab81ce7ec2d4f3"
readonly CLANG_REVISION="2844a309ef2c40f9e5d5961948e110a8a46d1533"

function clone {
	local destination="$1"
	local repo="$2"
	local revision="$3"
	
	cd "$(dirname "$location")"
	git clone $repo $(basename "$location")
	cd "$(basename "$location")"
	git checkout $revision
}

function build_libclang {
	local llvm_directory="$1"
	local prefix="$2"
	local build_dir="$3"
	
	mkdir -p "$build_dir"
	cd "$build_dir"
	cmake -G "Unix Makefiles" \
		-DLIBCLANG_BUILD_STATIC="ON" \
		-DCMAKE_INSTALL_PREFIX="$prefix" \
		"$llvm_directory"
	make && make install
	cp lib/libclang.a "${prefix}/lib/"
}

function main {
	local extdir=$(cd "${SCRIPT_DIR}/../ext"; pwd)
	mkdir -p "$extdir"
	
	cd "$extdir"
	
	local llvm_dir="${extdir}/llvm"
	local build_dir="${extdir}/llvm_build"
	clone "$llvm_dir" $LLVM_REPO $LLVM_REVISION
	clone "${llvm_dir}/tools/clang}" $CLANG_REPO $CLANG_REVISION
	build_libclang  "$llvm_dir" "$extdir" "${build_dir}"
	
	if [[ -e "${ext_dir}/lib/libclang.a" ]]; then
		echo "Clang has been built.  You can now delete ${build_dir}"
	else
		echo "There appears to have been a problem building clang."
	fi
}

main "$@"