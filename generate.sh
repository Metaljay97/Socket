#!/bin/bash
# generates test executable Makefile

# prints usage
usage() {
	cat <<EOF
generate.sh - generates an test executable makefile

Usage: $0 [-c|-d|-r|-h]

-c| --coverage       Generates a coverage makefile in test/buid/coverage
-d| --debug          Generates a debug makefile in test/build/debug.
-r| --release        Generates a release makefile in test/build/release.
-h| --help           Displays this help menu.
EOF
}

# if no arguments are provided, return usage function
if [ $# -eq 0 ]; then
	usage # run usage function
	exit 1
fi

# run submodule update
git submodule update --init

release=false
debug=false
coverage=false

# iterate through args.
for arg in "$@"; do
	case $arg in
	-c | --coverage)
		shift
		coverage=true
		;;
	-d | --debug)
		shift
		debug=true
		;;
	-r | --release)
		shift
		release=true
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

# generate coverage
if $coverage; then
	echo "Generating coverage"
	mkdir -p test/build/coverage
	pushd test/build/coverage
	cmake -DCMAKE_BUILD_TYPE=COVERAGE ../..
	popd
fi

# generate debug
if $debug; then
	echo "Generating debug"
	mkdir -p test/build/debug
	pushd test/build/debug
	cmake -DCMAKE_BUILD_TYPE=DEBUG ../..
	popd
fi

# generate release
if $release; then
	echo "Generating release"
	mkdir -p test/build/release
	pushd test/build/release
	cmake -DCMAKE_BUILD_TYPE=RELEASE ../..
	popd
fi

exit 0
