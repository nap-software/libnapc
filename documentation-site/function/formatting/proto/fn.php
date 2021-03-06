<?php

return function($fn_name) {
	$napc = napcdoc::documentation_get();

	$fn = $napc["definitions"][$fn_name];

	$fn_params = $fn["params"];
	$fn_param_count = sizeof($fn_params);

	$ret  = '<pre class="code">';

	$ret .= napcdoc::createHTMLElement("span",
		["class" => "c-type"],
		napcdoc::formatting_createLinkForCType($fn["return"]["type"])
	);

	$ret .= " ";
	$ret .= napcdoc::createHTMLElement("span",
		["class" => "c-function"],
		$fn_name
	);
	$ret .= "(";

	if ($fn_param_count >= 1) {
		$ret .= "\n";
	}

	/** padding to align param types **/
	$longest_param_type = "";

	foreach ($fn_params as $i => $param) {
		if (strlen($param["type"]) > strlen($longest_param_type)) {
			$longest_param_type = $param["type"];
		}
	}
	/** padding to align param types **/

	foreach ($fn_params as $i => $param) {
		$is_last_param = !array_key_exists($i + 1, $fn_params);

		// indent parameter 
		$ret .= "    ";

		if ($param["type"] === "...") {
			$ret .= "...";
		} else {
			$ret .= napcdoc::createHTMLElement("span",
				["class" => "c-type"],
				napcdoc::formatting_createLinkForCType($param["type"])
			);

			/** add padding to align param types **/
			$delta = strlen($longest_param_type) - strlen($param["type"]);
			$ret .= str_repeat(" ", $delta);
			/** add padding to align param types **/

			$ret .= " ";
		}

		if ($param["type"] !== "...") {
			$ret .= napcdoc::createHTMLElement("span",
				["class" => "c-identifier"],
				$param["name"]
			);
		}

		if (!$is_last_param) {
			$ret .= ",\n";
		}
	}

	if ($fn_param_count >= 1) {
		$ret .= "\n";
	} else if (!$fn_param_count) {
		$ret .= napcdoc::createHTMLElement("span", ["class" => "c-type"], "void");
	}

	$ret .= ");</pre>";

	return $ret;
};
