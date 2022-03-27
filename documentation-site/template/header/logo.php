<?php

return function($keys) {
	$git_branch = $keys["_build_constants"]["GIT_BRANCH"];
	$logo_src = "image/libnapc-logo-min.png";

	if (in_array($git_branch, ["nightly", "dev"])) {
		$logo_src = "image/libnapc-logo-".$git_branch."-min.png";
	}

	echo napcdoc::createHTMLElement("a", [
		"class" => "logo",
		"href" => napcdoc::documentation_fixLink("index.html")
	], napcdoc::createHTMLElement("img", [
		"src" => napcdoc::imageToBase64URI($logo_src),
		"alt" => "NAPC Software Documentation Logo",
		"height" => 50
	]));
};
