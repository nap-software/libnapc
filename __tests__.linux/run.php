#!/usr/bin/env php
<?php

chdir(__DIR__);

require_once __DIR__."/../x-php-utils/load.php";

function compile($test) {
	XPHPUtils::shell_assertSystemCall("rm -f tmp/$test.out");

	$command = "gcc -Wall -Wextra -Wpedantic ".escapeshellarg("$test.c")." -I../build/ -L../build/lib -lnapc-local -o tmp/$test.out";

	XPHPUtils::shell_assertSystemCall($command);
}

function startsWith($str, $needle) {
	return substr($str, 0, strlen($needle)) === $needle;
}

compile("file_root_path");

function file_root_path($env = "") {
	$used_root_path = "";
	$contents_of_file = "";

	$lines = XPHPUtils::shell_assertExecCall("$env ./tmp/file_root_path.out 2>&1");

	foreach ($lines as $line) {
		if (startsWith($line, "HAL_napc_initFileSystem (linux) root path = ")) {
			$used_root_path = substr($line, strlen("HAL_napc_initFileSystem (linux) root path = "));
		} else if (startsWith($line, "contents_of_file:") && !strlen($contents_of_file)) {
			$contents_of_file = substr($line, strlen("contents_of_file:"));
		}
	}

	return [
		substr($used_root_path, 1, -1), $contents_of_file
	];
}

$tests = [
	// root_path = CWD
	[
		file_root_path(), __DIR__, "cwd"
	],
	[
		file_root_path("NAPC_FILE_NO_RESOLVE_ROOT_PATH=1"), ".", "cwd"
	],
	// root_path = mock
	[
		file_root_path("NAPC_FILE_ROOT_PATH=mockfs/path/subpath"), __DIR__."/mockfs/path/subpath", "nested"
	],
	[
		file_root_path("NAPC_FILE_ROOT_PATH=mockfs/path/subpath NAPC_FILE_NO_RESOLVE_ROOT_PATH=1"), "mockfs/path/subpath", "nested"
	]
];

foreach ($tests as $test) {
	list($result, $expected_root_path, $expected_file_contents) = $test;

	if ($result[0] !== $expected_root_path) {
		fwrite(STDERR, "Unexpected root path: ".$result[0]."\n");
		exit(1);
	} else if ($result[1] !== $expected_file_contents) {
		fwrite(STDERR, "Unexpected file_contents: ".$result[1]."\n");
		exit(1);
	} else {
		echo "pass\n";
	}
}

compile("writer_fail_mode");

function writer_fail_mode() {
	$has_crashed = false;

	exec("./tmp/writer_fail_mode.out 2>&1", $lines, $exit_code);

	foreach ($lines as $line) {
		if (strpos($line, "Write operation failed and no_fail_mode is set to true") !== false) {
			$has_crashed = true;
		}
	}

	if ($exit_code === 0) {
		$has_crashed = false;
	}

	return $has_crashed;
}

if (!writer_fail_mode()) {
	fwrite(STDERR, "Expected program to crash\n");
	exit(1);
} else {
	echo "pass\n";
}
