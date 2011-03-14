(function ($) {
  Drupal.behaviors.cumulus = {
    attach: function(context, settings) {
      var cumulus = Drupal.settings.cumulus || {};
      for (var i in cumulus)
      {
        var param = cumulus[i];        
        var rnumber = Math.floor(Math.random()*9999999);
        var widget = new SWFObject(param['path_to_flash'] + "?r=" + rnumber, "cumulus-flash-" + i, param['width'], param['height'], 9, param['background']);
        if (param['transparency'] == 'true') {
          widget.addParam("wmode", "transparent");
        }
        widget.addParam("allowScriptAccess", "always");
        widget.addVariable("tcolor", param['color']);
        widget.addVariable("tcolor2", param['color2']);
        widget.addVariable("hicolor", param['hicolor']);
        widget.addVariable("tspeed", param['speed']);
        widget.addVariable("distr", param['distribute']);
        widget.addVariable("mode", "tags");
        widget.addVariable("tagcloud", param['flash_tags']);
        widget.write('cumulus-' + i);
      }
    }
  };
})(jQuery);