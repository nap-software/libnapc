<?php

return function($keys) {
	echo '<div class="logo-wrapper">';
	echo napcdoc::renderFile("header/logo", $keys);
	echo '</div>';

	echo '<div class="title-and-description-wrapper">';
	echo napcdoc::renderFile("header/title-and-description", $keys);
	echo '</div>';
};
