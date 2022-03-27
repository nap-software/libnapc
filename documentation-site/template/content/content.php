<?php

return function($keys) {
	$build_constants = napcdoc::documentation_get()["build_constants"];
?>
	<div id="napcdoc-content">
		<?php echo $keys["content"] ?? "No content available"; ?>

		<div id="popover_padding_div"></div>
	</div>
<?php
};
