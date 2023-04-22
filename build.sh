#!/bin/bash
# builds the test executable

# prints usage
usage() {
	cat <<EOF
generate.sh - generates an test executable

Usage: $0 [-c|-d|-r|-h]

-c| --coverage	     Generates a coverage test executable to test/build/coverage
-d| --debug          Generates a debug test executable to test/build/debug.
-r| --release        Generates a release test executable to test/build/release.
-h| --help           Displays this help menu.
EOF
}

# if no arguments are provided, return usage function
if [ $# -eq 0 ]; then
	usage # run usage function
	exit 1
fi

release=false
debug=false
coverage=false

# iterate through args.
for arg in "$@"; do
	case $arg in
	-d | --debug)
		shift
		debug=true
		;;
	-r | --release)
		shift
		release=true
		;;
	-c | --coverage)
		shift
		coverage=true
		;;
	-h | --help)
		usage
		;;
	*)
		usage
		exit 1
		;;
	esac
done

if $debug; then
	echo "Building debug"
	pushd test/build/debug
	cmake --build . --parallel
	popd
fi

if $coverage; then
	echo "Building Coverage"
	pushd test/build/coverage
	cmake --build . --parallel
	popd
fi

if $release; then
	echo "Building release"
	pushd test/build/release
	cmake --build . --parallel
	popd
fi
