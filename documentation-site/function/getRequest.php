<?php

return function() {
	$request = napcdoc::getRequestPath();
	$parts = explode("/", $request);
	$parts = array_filter($parts, "strlen");

	$static_routes = [
		"index.html",
		"install.html",
		"downloads.html",
		"style.css",
		"script.js"
	];

	if (sizeof($parts) === 1 && in_array($parts[0], $static_routes)) {
		return [
			"module" => NULL,
			"definition" => NULL
		];
	} else if (!sizeof($parts)) {
		return [
			"module" => NULL,
			"definition" => NULL
		];
	}

	if (sizeof($parts) === 1) {
		return [
			"module" => substr($parts[0], 0, strlen($parts[0]) - 5),
			"definition" => NULL
		];
	} else if (sizeof($parts) === 2 && $parts[1] === "index.html") {
		return [
			"module" => $parts[0],
			"definition" => NULL
		];
	}

	return [
		"module" => $parts[0],
		"definition" => substr($parts[1], 0, strlen($parts[1]) - 5)
	];
};
