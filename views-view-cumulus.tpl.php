<?php
// $Id$
/**
 * @file
 * Displays the items of the cloud.
 *
 * @ingroup views_templates
 */
?>
<div id="tags">
  <?php print $tags_formatted_alt; ?>
  <script type="text/javascript">
    var rnumber = Math.floor(Math.random()*9999999);
    var widget_so = new SWFObject("<?php print $params['path_to_flash']; ?>?r="+rnumber, "cumulusflash", "<?php print $params['width']; ?>", "<?php print $params['height']; ?>", "9", "<?php print $params['background']; ?>");
    <?php print $params['transparency']; ?>
    widget_so.addParam("allowScriptAccess", "always");
    widget_so.addVariable("tcolor", "<?php print $params['color']; ?>");
    widget_so.addVariable("tcolor2", "<?php print $params['color2']; ?>");
    widget_so.addVariable("hicolor", "<?php print $params['hicolor']; ?>");
    widget_so.addVariable("tspeed", "<?php print $params['speed']; ?>");
    widget_so.addVariable("distr", "<?php print $params['distribute']; ?>");
    widget_so.addVariable("mode", "tags");
    widget_so.addVariable("tagcloud", "<?php print $tags_formatted_flash; ?>");
    widget_so.write("tags");
  </script>
</div>
