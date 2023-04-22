#!/bin/bash
# tests the test executable

# prints usage
usage() {
	cat <<EOF
generate.sh - generates an test executable

Usage: $0 [-c|-d|-r|-h]

-c| --coverage       Tests a code coverage test executable and writes the report to the current directory.
-d| --debug          Tests a debug test executable.
-r| --release        Tests a release executable.
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
        ./socketTests
	popd
fi

if $coverage; then
	pushd test/build/coverage
	./socketTests
	lcov --directory . --capture --output-file ./code_coverage.info -rc lcov_branch_coverage=1
	genhtml code_coverage.info --branch-coverage --output-directory ./../../../code_coverage_report/
	popd
fi

if $release; then
	echo "Building release"
	pushd test/build/release
        ./socketTests
	popd
fi

exit 0
