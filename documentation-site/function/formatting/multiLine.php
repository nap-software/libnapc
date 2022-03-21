<?php

return function($text) {
	$text = htmlspecialchars($text);

	$ret = "";

	foreach (explode("\n", $text) as $line) {
		$ret .= "<p>".napcdoc::formatting_replaceBackticks($line)."</p>";
	}

	return $ret;
};
